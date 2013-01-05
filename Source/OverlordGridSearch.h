#ifndef __OVERLORDGRIDSEARCH_H__
#define __OVERLORDGRIDSEARCH_H__

#include "OverlordModule.h"
#include "UnitAgent.h"

using namespace BWAPI;

class OverlordGridSearch : public OverlordModule
{
private:
	Position mStartCorner;

public:
	OverlordGridSearch();
	OverlordGridSearch(UnitAgent* lAgent);
	~OverlordGridSearch();

	void computeActions(UnitAgent* lAgent);
};

#endif