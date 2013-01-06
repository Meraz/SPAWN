#include "OverlordModule.h"

OverlordModule::OverlordModule()
{
	mUnderAttack = false;
	xMax = Broodwar->mapWidth();
	yMax = Broodwar->mapHeight();
}

OverlordModule::~OverlordModule()
{

}

void OverlordModule::UpdateParamter(void* lParamter)
{

}


void OverlordModule::computeActions(UnitAgent* lAgent)
{

}

bool OverlordModule::UnderAttack(UnitAgent* lAgent)
{
	int cFrame = Broodwar->getFrameCount();
	TilePosition nGoal;
	if(mUnderAttack == true)
	{
		mLastAttacked += cFrame;

		if(mLastAttacked > 70000)
		{
		//	Broodwar->printf("Not attacked anymoar");
			mUnderAttack = false;
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
					//Calculate escape vector director
					b = a - b;
					a = a + b;
					//Increase that by 5
					int x = (a.x() + (b.x()) * 5);
					int y = (a.y() + (b.y()) * 5);

					//Make sure coords does not exceed mapsize
					if(x < 0 )		{ x = 0;}
					if(x > xMax )	{ x = xMax;}
					if(y < 0 )		{ y = 0;}
					if(y > yMax  )	{ y = yMax;}
				
					//Stop overlord and set new goal
					lAgent->getUnit()->stop();
					lAgent->setGoal(TilePosition(x,y));
					mUnderAttack = true;
					return true;
				}
			}
		}
	}
	return false;
}