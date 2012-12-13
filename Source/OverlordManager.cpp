#include "OverlordManager.h"

OverlordManager::OverlordManager()
{

}

OverlordManager::~OverlordManager()
{

}

OverlordManager* OverlordManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new OverlordManager();
	}
	return instance;
}

OverlordManager::AddOverlord(OverlordAgent* lOverlord)
{
	mOverlord.Add(lOverlord);
}

OverlordManager::AddHatchery(HatcheryAgent* lHatchery)
{
	mHatchery.Add(lHatchery);
}

OverlordManager: