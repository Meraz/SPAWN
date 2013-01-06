#ifndef __OVERLORDMONITORPOINTS_H__
#define __OVERLORDMONITORPOINTS_H__

#include "OverlordModule.h"
#include "OverlordStructs.h"
#include <vector>

using namespace BWAPI;

class OverlordMonitorPoints : public OverlordModule
{
public:
	OverlordMonitorPoints(UnitAgent* lAgent);
	~OverlordMonitorPoints();
	void UpdateParamter(void* lParamter);
	void computeActions(UnitAgent* lAgent);

	void SetPointOfInterest(PointOfInterest lPointOfInterest);

private:
	PointOfInterest* mPointOfInterest;
	vector<TilePosition> mSurroundingPlaces;
	int mCurrentGoal;
};

#endif