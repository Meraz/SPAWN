#include "OverlordModule.h"

OverlordModule::OverlordModule()
{

}

OverlordModule::OverlordModule(UnitAgent* lAgent)
{
	mAgent = lAgent;
	mUnderAttack = false;
	xMax = Broodwar->mapWidth();
	yMax = Broodwar->mapHeight();
	mAgent->setGoal(Broodwar->self()->getStartLocation());
}

OverlordModule::~OverlordModule()
{

}

void OverlordModule::UpdateParamter(void* lParamter)
{

}


void OverlordModule::computeActions()
{

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
		//	Broodwar->printf("Not attacked anymoar");
			mUnderAttack = false;
			return false;
		}
	}	
	
	if(mUnderAttack == false && mAgent->getUnit()->isUnderAttack())
	{
		for(set<Unit*>::const_iterator i=Broodwar->enemy()->getUnits().begin(); i!=Broodwar->enemy()->getUnits().end(); i++)
		{
			if ((*i)->exists())
			{
				if(mAgent->getUnit()->getDistance((*i)) < 9*32)
				{					
					mLastAttacked = 0;
					TilePosition a = mAgent->getUnit()->getTilePosition();
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
					mAgent->getUnit()->stop();
					mAgent->setGoal(TilePosition(x,y));
					mUnderAttack = true;
					return true;
				}
			}
		}
	}
	return false;
}