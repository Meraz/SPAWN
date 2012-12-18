#include "OverlordAgent.h"
#include "PFManager.h"
#include "Commander.h"
#include "AgentManager.h"
//Added by Bulten
#include <stdlib.h>
#include <time.h>


OverlordAgent::OverlordAgent(Unit* mUnit)
{
	unit = mUnit;
	type = unit->getType();
	unitID = unit->getID();
	agentType = "OverlordAgent";
	Broodwar->printf("OverlordAgent created (%s)", unit->getType().getName().c_str());
	
	lastUpdateFrame = Broodwar->getFrameCount();
	
	srand(time(NULL));
	//goal = TilePosition(rand(), rand());
	goal = TilePosition(-1,-1);

	//Broodwar->printf("Distance!! (%d)", Broodwar->enemy()->getStartLocation().getDistance(unit->getTilePosition()));

	int a,b;	
	a = Broodwar->mapWidth()*32;
	b = Broodwar->mapHeight()*32;
	Broodwar->printf("mapWidth %d", a);
	Broodwar->printf("mapHeight %d", b);
	Broodwar->printf("Overlord spawn tileposition x: %d", unit->getTilePosition().x()*32);
	Broodwar->printf("Overlord spawn tileposition y: %d", unit->getTilePosition().y()*32);	
	Broodwar->printf("Overlord spawn x: %d", unit->getPosition().x());
	Broodwar->printf("Overlord spawn y: %d", unit->getPosition().y());

	updateGoal();
}

void OverlordAgent::updateGoal()
{
	//If the overlord dont have a goal
	if(goal == TilePosition(-1, -1))
	{
		BaseAgent* agent = AgentManager::getInstance()->getClosestBase(unit->getTilePosition());
		if (agent != NULL)
		{
			goal = agent->getUnit()->getTilePosition();
			lastUpdateFrame = Broodwar->getFrameCount();
		}
	}

}

void OverlordAgent::computeActions()
{
	if (squadID == -1)
	{
		if (Broodwar->getFrameCount() - lastUpdateFrame > 100)
		{
			updateGoal();
		}
	}
	if(unit->isUnderAttack())
	{
		//goal = TilePosition(-1, -1);
	}

	PFManager::getInstance()->computeAttackingUnitActions(this, goal, true);
}

void OverlordAgent::SetPointOfInterest(TilePosition lPointOfInterest)
{
	goal = lPointOfInterest;
}