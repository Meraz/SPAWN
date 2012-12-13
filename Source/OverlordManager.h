#ifndef OVERLORDMANAGER_H
#define OVERLORDMANAGER_H

using namespace BWAPI;
using namespace BWTA;

#include "OverlordAgent.h"
#include "HatcheryAgent.h"
#include "TilePosition.h"
#include <vector>

class OverlordManager
{
public:
	OverlordManager();
	~OverlordManager();
	static OverlordManager* getInstance();
	TilePosition getGoal();

	AddOverlord(OverlordAgent* lOverlord);

private:
	vector<OverlordAgent*> mOverlord;
	vector<HatcheryAgent*> mHatchery

protected:
	static OverlordManager* instance;	//Can be private
};