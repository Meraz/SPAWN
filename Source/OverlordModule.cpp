#include "OverlordModule.h"

OverlordModule::OverlordModule()
{
	mUnderAttack = false;
}

OverlordModule::~OverlordModule()
{

}

void OverlordModule::UpdateParamter(void* lParamter)
{

}


void OverlordModule::computeActions(UnitAgent* lAgent)
{
	Broodwar->printf("Hej");
	if(lAgent->getUnit()->isUnderAttack())
	{
		//Do something
	}
}

bool OverlordModule::UnderAttack()
{
	int cFrame = Broodwar->getFrameCount();
	TilePosition nGoal;
	if(mUnderAttack == true)
	{
		mLastAttacked += cFrame;

		if(mLastAttacked > 70000)
		{
			Broodwar->printf("Not attacked anymoar");
			return false;
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
					mLastAttacked = 0;
					TilePosition a = lAgent->getUnit()->getTilePosition();
					TilePosition b = (*i)->getTilePosition();
					b = a - b;
					a = a + b;
					TilePosition c = TilePosition((a.x() + b.x()) * 10, (a.y() + b.x()) * 10);
					nGoal = c;
					lAgent->getUnit()->stop();
					lAgent->setGoal(nGoal);
					return true;
				}
			}
		}
	}
	return false;
}