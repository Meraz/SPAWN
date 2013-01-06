#ifndef __OVERLORDMODULE_H__
#define __OVERLORDMODULE_H__

#include <BWAPI.h>
#include <vector>
#include "OverlordStructs.h"

using namespace BWAPI;



class OverlordModule
{
public:
	/** Defaualt contructor, not used */
	OverlordModule();
	OverlordModule(UnitAgent* lAgent);
	~OverlordModule();
	//UnitAgent* mAgent;
	virtual void UpdateParamter(void* lParamter);
	virtual void computeActions();

protected:
	UnitAgent* mAgent;
	int xMax;
	int yMax;
	bool mUnderAttack;
	bool UnderAttack();
	bool StayHome();
	int mLastAttacked;
	int mLastCallFrame;
	//vector<EnemySpotted*>* mEnemySpotted;
	//vector<PointOfInterest*>* mPointOfInterest;


};

#endif