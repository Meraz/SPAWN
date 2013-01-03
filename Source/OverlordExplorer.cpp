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
	if(lAgent->getUnit()->isUnderAttack())
	{
		//Broodwar->printf("Overlord under attack");
		for(set<Unit*>::const_iterator i=Broodwar->enemy()->getUnits().begin(); i!=Broodwar->enemy()->getUnits().end(); i++)
		{
			if ((*i)->exists())
			{
				if(lAgent->getUnit()->getDistance((*i)) < 9*32)
				{
					//Broodwar->printf("Moving away!");
					TilePosition a = lAgent->getUnit()->getTilePosition();
					TilePosition b = (*i)->getTilePosition();
					b = a - b;
					a = a + b;
					a.x()*10;
					a.y()*10;
					nGoal = a;
					//add timer maybe?
				}
			}
		}
	}
	else
	{
		nGoal = ExplorationManager::getInstance()->getNextToExplore(lAgent);
	}	
	if (nGoal.x() >= 0)
	{
		lAgent->setGoal(nGoal);
	}
}