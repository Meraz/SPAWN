#include "OverlordExplorer.h"

OverlordExplorer::OverlordExplorer()
{
}

OverlordExplorer::~OverlordExplorer()
{ 

}

void OverlordExplorer::computeActions(UnitAgent* lAgent)
{
//	Broodwar->printf("Overlord Exploring");

	TilePosition nGoal;
	
	if(UnderAttack(lAgent) == false)
	{
		nGoal = ExplorationManager::getInstance()->getNextToExplore(lAgent);
		if (nGoal.x() >= 0)
		{
			lAgent->setGoal(nGoal);
		}
	}
}