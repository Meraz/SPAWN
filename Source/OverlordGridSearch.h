#ifndef __OVERLORDGRIDSEARCH_H__
#define __OVERLORDGRIDSEARCH_H__

#include "OverlordModule.h"
#include "UnitAgent.h"

using namespace BWAPI;

class OverlordGridSearch : public OverlordModule
{
private:
	TilePosition mStartCorner;

	void NextGoal();
	int MovementYdirection; //swap when we reach the top or bot


public:
	OverlordGridSearch(UnitAgent* lAgent);
	~OverlordGridSearch();
	void UpdateParamter(void* lParamter);
	void computeActions();
};

#endif