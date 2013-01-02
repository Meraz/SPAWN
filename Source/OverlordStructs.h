#ifndef __OVERLORDSTRUCTS_H__
#define __OVERLORDSTRUCTS_H__

#include "UnitAgent.h"
#include <BWAPI.h>
#include <vector>

using namespace BWAPI;


enum OverlordState
{
	UnderAttack,
	HoveringBase,
	NoAssignment,
	Exploring
};

enum PointOfInterestType
{
	Base,
	EnemyBase,
	Other
};

struct PointOfInterest
{
	Unit* mUnit;
	Position mPosition;
	PointOfInterestType mType;
	UINT mValue;					//Lower is better.
	//vector<UnitAgent*> mNearbyUnits;
	vector<TilePosition*> mSurroundingPosition;
	PointOfInterest(Unit* lUnit)
	{
		mUnit = lUnit;
		mPosition = lUnit->getPosition();
	};	
};

struct EnemySpotted
{
	UINT time;					//Save when last spotted
	PointOfInterest* mPoint;
};

struct BeingAttacked
{
	UINT time;					//Save when last spotted
	PointOfInterest* mPoint;
};

#endif