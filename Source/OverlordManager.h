#ifndef __OVERLORDMANAGER_H__
#define __OVERLORDMANAGER_H__

#include "UnitAgent.h"
#include <BWAPI.h>
#include <vector>
#include "OverlordAgent.h"
#include "HatcheryAgent.h"

using namespace BWAPI;
using namespace std;
/** The OverlordAgent handles overlords
 *
 * 
 * - 
 *
 * Author: Rasmus Tilljander (tilljander.rasmus@gmail.com)
 */

enum OverlordState
{
	UnderAttack,
	HoveringBase,
	NoAssignment,
	Exploring
};

struct EnemySpotted
{
	int time;				//Save when last spotted
	TilePosition position;	//Position where it was spotted
};

struct PointOfInterest		//Le bases
{
	vector<UnitAgent*> mHoveringOverlords;
	TilePosition position;
};


class OverlordManager
{
public:	
	static OverlordManager* getInstance();
	void computeActions();

	void UpdateGoal();

	void AddOverlord(OverlordAgent* lOverlord);
	void AddHatchery(HatcheryAgent* lHatchery);

private:
	OverlordManager();
	~OverlordManager();

	vector<OverlordAgent*> mOverlord;
	vector<HatcheryAgent*> mHatchery;
	vector<EnemySpotted> mEnemySpotted;
	unsigned int mMapSizeX, mMapSizeY;

protected:
	 static OverlordManager* instance;	//Can be private
};
#endif