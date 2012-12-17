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
	goal = TilePosition(0,0);

	//Broodwar->printf("Distance!! (%d)", Broodwar->enemy()->getStartLocation().getDistance(unit->getTilePosition()));

	int a,b;	
	a = Broodwar->mapWidth()*32;
	b = Broodwar->mapHeight()*32;
	Broodwar->printf("mapWidth %d", a);
	Broodwar->printf("mapHeight %d", b);
	Broodwar->printf("Overlord spawn x: %d", unit->getTilePosition().x()*32);
	Broodwar->printf("Overlord spawn y: %d", unit->getTilePosition().y()*32);
	Broodwar->printf("Enemy start loc x: %d", Broodwar->enemy()->getStartLocation().x());
	Broodwar->printf("Enemy start location y: %d", Broodwar->enemy()->getStartLocation().y());
	Broodwar->pingMinimap(1000,1002);

	updateGoal();
}

void OverlordAgent::updateGoal()
{
	BaseAgent* agent = AgentManager::getInstance()->getClosestBase(unit->getTilePosition());
	if (agent != NULL)
	{
		//goal = agent->getUnit()->getTilePosition();
		lastUpdateFrame = Broodwar->getFrameCount();
	}
	//Broodwar->printf("Distance!! (%d)", unit->getDistance(Position(0,0)));
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
		goal = TilePosition(-1, -1);
	}


	PFManager::getInstance()->computeAttackingUnitActions(this, goal, true);
}
