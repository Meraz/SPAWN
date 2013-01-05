#ifndef __OVERLORDMANAGER_H__
#define __OVERLORDMANAGER_H__

#include "UnitAgent.h"
#include <BWAPI.h>
#include <vector>
#include "OverlordAgent.h"
#include "OverlordExplorer.h"
#include "OverlordMonitorPoints.h"

using namespace BWAPI;
using namespace std;
/** The OverlordAgent handles overlords
 *
 * 
 * - 
 *
 * Author: Rasmus Tilljander (tilljander.rasmus@gmail.com)
 */

class OverlordManager
{
public:	
	bool a;
	static OverlordManager* getInstance();
	void computeActions();

	void UpdateGoal();

	void AddOverlord(OverlordAgent* lOverlord);
	void AddPointOfInterest(PointOfInterest* lPoint);

private:
	OverlordManager();
	~OverlordManager();
	void UniHatchery();
	void DuHatchery();
	void TriHatchery();
	void MultipleHatchery();

	vector<OverlordAgent*> mOverlord;
	//vector<EnemySpotted*>* mEnemySpotted;
	vector<PointOfInterest*>* mPointOfInterest;
	unsigned int mMapSizeX, mMapSizeY;
	int lastCallFrame;

protected:
	 static OverlordManager* instance;	//Can be private
};
#endif