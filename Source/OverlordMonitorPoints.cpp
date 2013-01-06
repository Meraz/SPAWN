#include "OverlordMonitorPoints.h"

OverlordMonitorPoints::OverlordMonitorPoints(UnitAgent* lAgent) : OverlordModule(lAgent)
{
	mPointOfInterest = NULL;
	mCurrentGoal = -1;
}

OverlordMonitorPoints::~OverlordMonitorPoints()
{ 

}

void OverlordMonitorPoints::UpdateParamter(void* lParamter)
{
	PointOfInterest* lPoint = (PointOfInterest*)lParamter;
	if(lPoint == mPointOfInterest) //Already had this point
		return;
	mPointOfInterest = lPoint;
	TilePosition lPos = mPointOfInterest->mUnit->getTilePosition();

	int offset = 12;
	TilePosition up	=		TilePosition(lPos.x(),			lPos.y()-offset);
	TilePosition right =	TilePosition(lPos.x()+offset,	lPos.y());
	TilePosition down =		TilePosition(lPos.x(),			lPos.y()+offset);
	TilePosition left =		TilePosition(lPos.x()-offset,	lPos.y());
	mSurroundingPlaces.push_back(up);
	mSurroundingPlaces.push_back(right);
	mSurroundingPlaces.push_back(down);
	mSurroundingPlaces.push_back(left);

	mCurrentGoal = 0;
}

void OverlordMonitorPoints::computeActions(UnitAgent* lAgent)
{
	TilePosition nGoal;
	if(mCurrentGoal == -1)
		return;	

	if(lAgent->getUnit()->getTilePosition().getDistance(mSurroundingPlaces.at(mCurrentGoal)) < 5)
		mCurrentGoal++;
	if(mCurrentGoal > mSurroundingPlaces.size()-1)
		mCurrentGoal = 0;
	nGoal = mSurroundingPlaces.at(mCurrentGoal);
	
	if (nGoal.x() >= 0)
	{
		lAgent->setGoal(nGoal);
	}
}

