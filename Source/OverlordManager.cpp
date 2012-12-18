#include "OverlordManager.h"

OverlordManager* OverlordManager::instance = NULL;

OverlordManager::OverlordManager()
{
	mOverlord = vector<OverlordAgent*>();
	mHatchery = vector<HatcheryAgent*>();
	mMapSizeX = Broodwar->mapWidth()*32;
	mMapSizeY = Broodwar->mapHeight()*32;
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

void OverlordManager::AddOverlord(OverlordAgent* lOverlord)
{	
	if(lOverlord->getSquadID() != -1)
		return;

	Broodwar->printf("Overlord added in manager");
	mOverlord.push_back(lOverlord);
}

void OverlordManager::AddHatchery(HatcheryAgent* lHatchery)
{
	Broodwar->printf("Hatchery added in manager");
	mHatchery.push_back(lHatchery);
}

void OverlordManager::UpdateGoal()
{
	UINT j = 0;
	if(mHatchery.size() <  mOverlord.size()*3)
	{
		for(UINT i = 0; i < mHatchery.size(); i++)
		{
			mOverlord.at(i)->SetPointOfInterest(mHatchery.at(i)->getUnit()->getTilePosition());
			mOverlord.at(i+1)->SetPointOfInterest(mHatchery.at(i)->getUnit()->getTilePosition());
			mOverlord.at(i+2)->SetPointOfInterest(mHatchery.at(i)->getUnit()->getTilePosition());
		}
	}
}

void OverlordManager::computeActions()
{
	//UpdateGoal();
}