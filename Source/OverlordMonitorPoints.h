#ifndef __OVERLORDMONITORPOINTS_H__
#define __OVERLORDMONITORPOINTS_H__

#include "OverlordModule.h"
#include "OverlordStructs.h"

using namespace BWAPI;

class OverlordMonitorPoints : public OverlordModule
{
public:
	OverlordMonitorPoints();
	~OverlordMonitorPoints();
	void computeActions(UnitAgent* lAgent);

	void SetPointOfInterest(PointOfInterest lPointOfInterest);

private:
	//PointOfInterest mPointOfInterest;
};

#endif