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
	//Broodwar->printf("OverlordAgent created (%s)", unit->getType().getName().c_str());
	mHasModule = false;
	
	lastUpdateFrame = Broodwar->getFrameCount();

	mOverlordModule = NULL;

	//srand(time(NULL));
	goal = TilePosition(-1,-1);
	goal = Broodwar->self()->getStartLocation();
	//int a,b;	
	//a = Broodwar->mapWidth()*32;
	//b = Broodwar->mapHeight()*32;
	//Broodwar->printf("mapWidth %d", a);
	//Broodwar->printf("mapHeight %d", b);
	//Broodwar->printf("Overlord spawn x: %d", unit->getPosition().x());
	//Broodwar->printf("Overlord spawn y: %d", unit->getPosition().y());
	
	//Broodwar->printf("Overlord spawn x: %d", unit->getTilePosition().x());
	//Broodwar->printf("Overlord spawn y: %d", unit->getTilePosition().y());

	updateGoal();
}

void OverlordAgent::updateGoal()
{
	if(mOverlordModule != NULL)
		mOverlordModule->computeActions(this);
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

	PFManager::getInstance()->computeAttackingUnitActions(this, goal, true);
}

void OverlordAgent::SetOverlordModule(OverlordModule* lOverlordModule)
{
	delete mOverlordModule;
	mOverlordModule = lOverlordModule;
}

OverlordModule* OverlordAgent::GetOverlordModule()
{
	return mOverlordModule;
}