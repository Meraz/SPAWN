#ifndef __OVERLORDAGENT_H__
#define __OVERLORDAGENT_H__

#include <BWAPI.h>
#include "UnitAgent.h"
#include "OverlordModule.h"
#include "OverlordStructs.h"
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
	OverlordModule* mOverlordModule;
	void updateGoal();
	bool mHasModule;


public:
	OverlordAgent(Unit* mUnit);

	/** Called each update to issue orders. */
	void computeActions();
	void SetOverlordModule(OverlordModule* lOverlordModule);
	OverlordModule* GetOverlordModule();
	
};

#endif
