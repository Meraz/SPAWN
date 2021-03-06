#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <BWAPI.h>

using namespace BWAPI;
using namespace std;

struct ResourceLock {
	UnitType unit;
	int mineralCost;
	int gasCost;

	ResourceLock(UnitType mUnit)
	{
		unit = mUnit;
		mineralCost = mUnit.mineralPrice();
		gasCost = mUnit.gasPrice();
	}
};

/** ResourceManager handles the resources and where to spend them. An agent must ask the ResourceManager for permission to build/upgrade/research
 * before issuing the order.
 *
 * The ResourceManager is implemented as a singleton class. Each class that needs to access ResourceManager can request an instance,
 * and all classes shares the same ResourceManager instance.
 *
 * Author: Johan Hagelback (johan.hagelback@gmail.com)
 */
class ResourceManager {

private:
	static ResourceManager* instance;

	ResourceManager();

	bool hasProductionBuilding();
	
	vector<ResourceLock> locks;

	int calcLockedMinerals();
	int calcLockedGas();

public:
	/** Destructor. */
	~ResourceManager();
	bool CompareGasMineralRatio(float ratio);
	/** Returns the instance to the BuildPlanner that is currently used. */
	static ResourceManager* getInstance();

	/** Checks if we need to construct a new worker. */
	bool needWorker();

	/** Checks if we have enough resources free to build the specified unit. */
	bool hasResources(UnitType type);

	/** Checks if we have enough resources free for the specified upgrade. */
	bool hasResources(UpgradeType type);

	/** Checks if we have enough resources free for the specified research. */
	bool hasResources(TechType type);

	/** Checks if we have enough resources free. */
	bool hasResources(int neededMinerals, int neededGas);

	/** Locks resources for use. */
	void lockResources(UnitType type);

	/** Unlocks resources for use. */
	void unlockResources(UnitType type);

	/** Shows some debug info on screen. */
	void printInfo();
};

#endif
