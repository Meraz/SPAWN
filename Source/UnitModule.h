#ifndef __UNITMODULE_H__
#define __UNITMODULE_H__

#include <BWAPI.h>
#include <vector>
#include "OverlordStructs.h"
using namespace BWAPI;

class UnitModule
{
public:
	UnitModule();
	~UnitModule();

protected:
	vector<EnemySpotted*>* mEnemySpotted;
	vector<PointOfInterest*>* mPointOfInterest;
};


#endif