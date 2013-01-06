#include "OverlordAgent.h"
#include "PFManager.h"
#include "Commander.h"
#include "AgentManager.h"

OverlordAgent::OverlordAgent(Unit* mUnit)
{
	unit = mUnit;
	type = unit->getType();
	unitID = unit->getID();
	agentType = "OverlordAgent"; 
	//Broodwar->printf("OverlordAgent created (%s)", unit->getType().getName().c_str());
	
	lastUpdateFrame = Broodwar->getFrameCount();
	goal = TilePosition(-1,-1);
	

	mOverlordModule = vector<OverlordModule*>();
	mOverlordModule.push_back(new OverlordExplorer());
	mOverlordModule.push_back(new OverlordMonitorPoints());
	mOverlordModule.push_back(new OverlordGridSearch(this));
	mCurrentModule = 0;

	updateGoal();
}

void OverlordAgent::updateGoal()
{
	mOverlordModule.at(mCurrentModule)->computeActions(this);
}

void OverlordAgent::computeActions()
{
	if (squadID == -1)
	{
		if (Broodwar->getFrameCount() - lastUpdateFrame > 20)
		{
			updateGoal();
		}
	}
	PFManager::getInstance()->computeAttackingUnitActions(this, goal, true, true);
}

void OverlordAgent::SetOverlordModule(OverlordState lState, void* lParamter)
{
	mCurrentModule = (int)lState;
	mOverlordModule.at(mCurrentModule)->UpdateParamter(lParamter);	
}