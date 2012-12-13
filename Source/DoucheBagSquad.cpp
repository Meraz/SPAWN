#include "DouchebagSquad.h"
#include "UnitAgent.h"
#include "ExplorationManager.h"
#include "PFManager.h"

DoucheBagSquad::DoucheBagSquad(int mId, string mName, int mPriority)
{
	this->id = mId;
	this->type = DOUCHEBAG;
	this->moveType = GROUND;
	this->name = mName;
	this->priority = mPriority;
	activePriority = priority;
	active = false;
	required = false;
	goal = Broodwar->self()->getStartLocation();
	goalSetFrame = 0;
	currentState = STATE_NOT_SET;

	assignedGoals = false;
	membersBurrowed = false;
	launch = false;

	nrBasePositions = 0;
	agentToBurrow = 0;
}

DoucheBagSquad::~DoucheBagSquad()
{
	delete[] goals;
}

bool DoucheBagSquad::isActive()
{
	return active;
}

void DoucheBagSquad::defend(TilePosition mGoal)
{

}

void DoucheBagSquad::attack(TilePosition mGoal)
{

}

void DoucheBagSquad::assist(TilePosition mGoal)
{

}

void DoucheBagSquad::computeActions()
{
	if (!active)
	{
		if (isFull())
		{
			active = true;
		}
		return;
	}

	//First, remove dead agents
	for(int i = 0; i < (int)agents.size(); i++)
	{
		if(!agents.at(i)->isAlive())
		{
			agents.erase(agents.begin() + i);
			i--;
		}
	}
	if(agentToBurrow >= agents.size())
		if(agents.size() > 1)
			agentToBurrow = agents.size()-1;
		else
		{
			active = launch = false;
			return;
		}


	//All units dead, go back to inactive
	if ((int)agents.size() == 0)
	{
		active = false;
		return;
	}

	if (active)
	{
		//printInfo();
		if (activePriority != priority)
		{
			priority = activePriority;
		}
		
		//check if assigned base locations
		if(!assignedGoals)
		{
			if(isMembersBurrowAble())
				assignGoals();
		}
		if(launch)
		{
			if(agentToBurrow < agents.size())
			{
				int eCnt = ExplorationManager::getInstance()->spottedBuildingsWithinRange(
								agents.at(agentToBurrow)->getUnit()->getTilePosition(), 40); //Turn around at first sight
				if (eCnt > 0)
				{
					//Broodwar->printf("[Found %d Enemy Buildings]", eCnt);
					agentToBurrow++;
					nextGoal();
					setMemberGoals(goal);
					return;
				}
			}
			
			if(isSquadCloseTo(goal))
			{
				//Broodwar->printf("[DOUCHEBAG Is CLOSE");
				if(!isCurrentAgentBurrowed())
				{
					//Broodwar->printf("[Burrow %d]", agentToBurrow);
					agents.at(agentToBurrow)->getUnit()->burrow();
					agentToBurrow++;
					nextGoal();
				}
			}
		}

		if (launch && goal.x() >= 0)
		{
			setMemberGoals(goal);
		}
	}
}

void DoucheBagSquad::nextGoal()
{
	if(agentToBurrow >= agents.size())
	{
		active = launch = false;
		return;
	}


	if(agentToBurrow < nrBasePositions)
	{
		//agentToBurrow++;
		goal = goals[agentToBurrow];
	}
	else
	{
		//Broodwar->printf("[Burry everyone!]");
		burrowMembers();
		launch = false;
	}
}
bool DoucheBagSquad::isCurrentAgentBurrowed()
{
	return agents.at(agentToBurrow)->getUnit()->isBurrowed();
}

bool DoucheBagSquad::isSquadCloseTo(TilePosition mGoal)
{
	int offset = 4;
	Unit* unit = agents.at(agentToBurrow)->getUnit();
	/*Broodwar->printf("[AgentPos(%d,%d) GoalPos(%d,%d) Diff(%d,%d)", unit->getTilePosition().x(),
														unit->getTilePosition().y(),
														mGoal.x(), mGoal.y(), unit->getTilePosition().x() - mGoal.x(),
														unit->getTilePosition().y() - mGoal.y());
														*/
	if((unit->getTilePosition().x() - mGoal.x() < offset &&
		unit->getTilePosition().x() - mGoal.x() > -offset) &&
		(unit->getTilePosition().y() - mGoal.y() < offset &&
		unit->getTilePosition().y() - mGoal.y() > -offset))
		return true;
	else
		return false;
}

void DoucheBagSquad::burrowMembers()
{
	bool burrowed = true;
	for( unsigned int i = 0; i < agents.size(); i++ )
	{
		if(!agents.at(i)->getUnit()->isBurrowed())
		{
			if(agents.at(i)->getUnit()->getTilePosition().getDistance(agents.at(i)->getGoal()) <= 3 )
				agents.at(i)->getUnit()->burrow();
			burrowed = false;
		}
	}
	membersBurrowed =  burrowed;
	launch = false;
}

bool DoucheBagSquad::isMembersBurrowAble()
{
	bool burrowAble = true;
	for( unsigned int i = 0; i < agents.size(); i++ )
	{
		//Check if agens is burrowable and have researched Burrow
		if(!agents.at(i)->getUnit()->getType().isBurrowable() || !Broodwar->self()->hasResearched(TechTypes::Burrowing) )
		{
			burrowAble = false;
			break;
		}
	}
	return burrowAble;
}

void DoucheBagSquad::assignGoals()
{
		//Iterate through all base locations that is reachable
		TilePosition home = Broodwar->self()->getStartLocation();
		//Broodwar->printf("[Home is at (%d,%d)", home.x(), home.y());
		for(set<BWTA::BaseLocation*>::const_iterator i=BWTA::getBaseLocations().begin(); i!= BWTA::getBaseLocations().end(); i++)
		{
			//Broodwar->printf("[Location is at (%d,%d)", (*i)->getTilePosition().x(), (*i)->getTilePosition().y());
			if( agents.at(agentToBurrow)->getUnit()->hasPath((*i)->getPosition()) && (*i)->getTilePosition() != home)
				nrBasePositions++;
		}
		if(nrBasePositions == 0)
			return;

		//Broodwar->printf("[nrBasePositions %d]", nrBasePositions);
		goals = new TilePosition[nrBasePositions];
		int index = 0;
		//Store rachable base locations
		for(set<BWTA::BaseLocation*>::const_iterator i=BWTA::getBaseLocations().begin(); i!= BWTA::getBaseLocations().end(); i++)
		{
			if( agents.at(agentToBurrow)->getUnit()->hasPath((*i)->getPosition()) && (*i)->getTilePosition() != home)
			{
				goals[index++] = (*i)->getTilePosition();
				//Broodwar->printf("[Base %d, loc(%d,%d)]", index - 1, goals[index - 1].x(), goals[index - 1].y());
			}
		}
		//Set first goal
		goal = goals[agentToBurrow];

		launch = true;
		assignedGoals = true;
}

void DoucheBagSquad::printInfo()
{
	string f = "NotFull";
	if (isFull())
	{
		f = "Full";
	}
	string a = "Inactive";
	if (isActive())
	{
		a = "Active";
	}

	Broodwar->printf("[ExplorationSquad %d] (%s, %s) Goal: (%d,%d) prio: %d", id, f.c_str(), a.c_str(), goal.x(), goal.y(), priority);
}

void DoucheBagSquad::clearGoal()
{
	
}

TilePosition DoucheBagSquad::getGoal()
{
	return goal;
}

bool DoucheBagSquad::hasGoal()
{
	if (goal.x() < 0 || goal.y() < 0)
	{
		return true;
	}
	return false;
}
