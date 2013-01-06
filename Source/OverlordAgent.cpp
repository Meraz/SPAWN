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

	goal = Broodwar->self()->getStartLocation();

	mOverlordModule = vector<OverlordModule*>();
	mOverlordModule.push_back(new OverlordExplorer(this));
	mOverlordModule.push_back(new OverlordMonitorPoints(this));
	mOverlordModule.push_back(new OverlordGridSearch(this));
	mCurrentModule = 1;

	updateGoal();
}

void OverlordAgent::updateGoal()
{
	mOverlordModule.at(mCurrentModule)->computeActions();

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

