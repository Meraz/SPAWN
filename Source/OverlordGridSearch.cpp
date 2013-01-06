#include "OverlordGridSearch.h"

OverlordGridSearch::OverlordGridSearch(UnitAgent* lAgent) : OverlordModule(lAgent)
{
	MovementYdirection = 15;
	TilePosition lTopLeft = TilePosition(5,2);
	TilePosition lBotRight = TilePosition(xMax-5, yMax-2);
	mFirstTime = true;

	int lDistanceTopLeft = lAgent->getUnit()->getTilePosition().getDistance(lTopLeft);
	int lDistanceRightBot = lAgent->getUnit()->getTilePosition().getDistance(lBotRight);

	if(lDistanceTopLeft < lDistanceRightBot)
	{
		mStartCorner = lTopLeft;
	}
	else
		mStartCorner = lBotRight;
}

OverlordGridSearch::~OverlordGridSearch()
{

}

void OverlordGridSearch::UpdateParamter(void* lParamter)
{
	if(mFirstTime == true)
	{
		mAgent->getUnit()->stop();
		mAgent->setGoal(mStartCorner);
		mFirstTime = false;
	}
}

void OverlordGridSearch::computeActions()
{
	if(StayHome())
	{
		if(mAgent->getUnit()->getTilePosition().getDistance(Broodwar->self()->getStartLocation()) < 10)
		{
			mAgent->getUnit()->stop();
			mAgent->setGoal(Broodwar->self()->getStartLocation());
		}
	}

	if(UnderAttack())
		return;

	int a = mAgent->getUnit()->getTilePosition().getDistance(mAgent->getGoal());
	if(a < 5)
	{
		int cFrame = Broodwar->getFrameCount();
		mLastChangedDir += cFrame;
		NextGoal();
	}
}
 
void OverlordGridSearch::NextGoal()
{
	TilePosition nGoal;
	Unit* lUnit = mAgent->getUnit();	

	if(lUnit->getTilePosition().y() <  7 || lUnit->getTilePosition().y() > yMax-7)	
		MovementYdirection *= -1;
   
	int lY = lUnit->getTilePosition().y() + MovementYdirection;
	if(lY < 5)
		lY = 5;
	if(lY > yMax-5)
		lY = yMax-5;

    if(lUnit->getTilePosition().x() < 10)
    {
		nGoal = TilePosition(xMax-5, lY);
    }   
    else if(lUnit->getTilePosition().x() > xMax-10)
    {		
		nGoal = TilePosition(5, lY);
    }   

	if (nGoal.x() >= 0)
	{
		mAgent->setGoal(nGoal);
		mLastChangedDir = 0;
	}
}