#include "OverlordExplorer.h"

OverlordExplorer::OverlordExplorer(UnitAgent* lAgent): OverlordModule(lAgent)
{
}

OverlordExplorer::~OverlordExplorer()
{ 

}

void OverlordExplorer::computeActions()
{
//	Broodwar->printf("Overlord Exploring");

	TilePosition nGoal;
	
	if(UnderAttack() == false)
	{
		nGoal = ExplorationManager::getInstance()->getNextToExplore(mAgent);
		if (nGoal.x() >= 0)
		{
			mAgent->setGoal(nGoal);
		}
	}
}