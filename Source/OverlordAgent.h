#ifndef __OVERLORDAGENT_H__
#define __OVERLORDAGENT_H__

#include <BWAPI.h>
#include "UnitAgent.h"
#include "OverlordModule.h"
#include "OverlordStructs.h"
#include "OverlordExplorer.h"
#include "OverlordGridSearch.h"
#include "OverlordMonitorPoints.h"
#include <vector>
using namespace BWAPI;
using namespace std;

/** The OverlordAgent handles Zerg Overlord units.
 *
 * Implemented special abilities:
 * - 
 *
 * Author: Johan Hagelback (johan.hagelback@gmail.com)
 */

class OverlordAgent : public UnitAgent {

private:
	int lastUpdateFrame;
	vector<OverlordModule*> mOverlordModule;
	int mCurrentModule;
//	OverlordModule mCurrentModule;
	void updateGoal();


public:
	OverlordAgent(Unit* mUnit);

	/** Called each update to issue orders. */
	void computeActions();

	/**				*/
	void SetOverlordModule(OverlordState lState, void* lParamter);
	
};

#endif
