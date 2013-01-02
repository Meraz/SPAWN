#include "OverlordExplorer.h"

OverlordExplorer::OverlordExplorer()
{

}

OverlordExplorer::~OverlordExplorer()
{ 

}

void OverlordExplorer::computeActions(UnitAgent* lAgent)
{
	TilePosition nGoal;
	nGoal = ExplorationManager::getInstance()->getNextToExplore(lAgent);
	//nGoal = TilePosition(-1,-1);
	lAgent->setGoal(nGoal);
}