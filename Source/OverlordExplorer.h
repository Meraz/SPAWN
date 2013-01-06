#ifndef __OVERLORDEXPLORER_H__
#define __OVERLORDEXPLORER_H__

#include "OverlordModule.h"
#include "ExplorationManager.h"

using namespace BWAPI;

class OverlordExplorer : public OverlordModule
{
public:
	OverlordExplorer();
	~OverlordExplorer();
	void computeActions(UnitAgent* lAgent);

private:
	int mLastAttacked;
	int mLastCallFrame;
};

#endif