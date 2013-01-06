#ifndef __OVERLORDGRIDSEARCH_H__
#define __OVERLORDGRIDSEARCH_H__

#include "OverlordModule.h"
#include "UnitAgent.h"

using namespace BWAPI;

class OverlordGridSearch : public OverlordModule
{
private:
	TilePosition mStartCorner;
	int xMax;
	int yMax;
	void NextGoal(UnitAgent* lAgent);
	int MovementYdirection; //swap when we reach the top or bot


public:
	OverlordGridSearch();
	OverlordGridSearch(UnitAgent* lAgent);
	~OverlordGridSearch();

	void computeActions(UnitAgent* lAgent);
};

#endif