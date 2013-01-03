#include "OverlordMonitorPoints.h"

OverlordMonitorPoints::OverlordMonitorPoints()
{

}

OverlordMonitorPoints::~OverlordMonitorPoints()
{ 

}

void OverlordMonitorPoints::computeActions(UnitAgent* lAgent)
{
	TilePosition nGoal;
	
	if (nGoal.x() >= 0)
	{
		lAgent->setGoal(nGoal);
	}
}

void OverlordMonitorPoints::SetPointOfInterest(PointOfInterest lPointOfInterest)
{
	
};
