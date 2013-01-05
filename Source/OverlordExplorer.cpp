#include "OverlordExplorer.h"

OverlordExplorer::OverlordExplorer()
{
	mUnderAttack = false;	
}

OverlordExplorer::~OverlordExplorer()
{ 

}

void OverlordExplorer::computeActions(UnitAgent* lAgent)
{
//	Broodwar->printf("Overlord Exploring");

	TilePosition nGoal;
	int cFrame = Broodwar->getFrameCount();
	//if (cFrame - lastCallFrame < 50)
	//{
	//	return;
	//}
	

	if(mUnderAttack == true)
	{
		mLastAttacked += cFrame;

		if(mLastAttacked > 70000)
		{
			Broodwar->printf("Not attacked anymoar");
			mUnderAttack = false;			
		}
	}	
	
	if(mUnderAttack == false && lAgent->getUnit()->isUnderAttack())
	{
		for(set<Unit*>::const_iterator i=Broodwar->enemy()->getUnits().begin(); i!=Broodwar->enemy()->getUnits().end(); i++)
		{
			if ((*i)->exists())
			{
				if(lAgent->getUnit()->getDistance((*i)) < 9*32)
				{
					mUnderAttack = true;
					mLastAttacked = 0;
					TilePosition a = lAgent->getUnit()->getTilePosition();
					TilePosition b = (*i)->getTilePosition();
					b = a - b;
					a = a + b;
					TilePosition c = TilePosition((a.x() + b.x()) * 10, (a.y() + b.x()) * 10);
					nGoal = c;
					lAgent->getUnit()->stop();
					lAgent->setGoal(nGoal);
				}
			}
		}
	}
	else if(mUnderAttack == false)
	{
		nGoal = ExplorationManager::getInstance()->getNextToExplore(lAgent);
		if (nGoal.x() >= 0)
		{
			lAgent->setGoal(nGoal);
		}
	}
}