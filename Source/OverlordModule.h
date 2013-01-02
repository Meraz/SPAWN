#ifndef __OVERLORDMODULE_H__
#define __OVERLORDMODULE_H__

#include <BWAPI.h>
#include <vector>
#include "OverlordStructs.h"

using namespace BWAPI;



class OverlordModule
{
public:
	OverlordModule();
	~OverlordModule();
	//UnitAgent* mAgent;
	virtual void computeActions(UnitAgent* lAgent);

protected:
	vector<EnemySpotted*>* mEnemySpotted;
	vector<PointOfInterest*>* mPointOfInterest;


};
	/*
		"Defend" base
		Explore
		Expand base
		Looking for terran
		Sweep mapX
		Sweep mapY
	*/

#endif