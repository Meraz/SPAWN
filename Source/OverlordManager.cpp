#include "OverlordManager.h"

OverlordManager* OverlordManager::instance = NULL;

OverlordManager::OverlordManager()
{
	mOverlord = vector<OverlordAgent*>();
	
	//mEnemySpotted = new vector<EnemySpotted*>();
	mPointOfInterest = new vector<PointOfInterest*>();
	mTotalDeadOverlord = 0;

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
	mOverlord.push_back(lOverlord);
}

void OverlordManager::AddPointOfInterest(PointOfInterest* lPoint)
{

	if(lPoint->mType == PointOfInterestType::Base)
	{
		for(int i = 0; i < mPointOfInterest->size(); i++)
		{
			if(mPointOfInterest->at(i)->mPosition.getApproxDistance(lPoint->mPosition) < 500)
			{
				//Maco hatchery
				//So instead increase value of the original point and return
				mPointOfInterest->at(i)->mValue += 1;	//Modify this number maybe //Priority is not used at this moment
				return;		
			}
		}
	}
	mPointOfInterest->push_back(lPoint);
}

void OverlordManager::UpdateGoal()
{
	//Broodwar->printf("UpdateGoal");
	int lAmountOfBases = 0;
	for(int i = 0; i < mPointOfInterest->size(); i++)
	{
		if(mPointOfInterest->at(i)->mType == PointOfInterestType::Base)
		{
			lAmountOfBases++;
			if(mPointOfInterest->at(i) == 0)
			{
				mPointOfInterest->erase(mPointOfInterest->begin()+i);
			//	Broodwar->printf("Base removed from manager");
			}
		}
	}

	for(int i = 0; i < mOverlord.size(); i++)
	{
		if(mOverlord.at(i)->getSquadID() != -1 || mOverlord.at(i) == 0)
		{
			mOverlord.erase(mOverlord.begin()+i);
			mTotalDeadOverlord++;
		//	Broodwar->printf("Overlord removed from manager");
		}
	}



	//Broodwar->printf("Before bases");
	if(lAmountOfBases == 0)
		return;
	if(lAmountOfBases == 1)
		UniHatchery();
	if(lAmountOfBases == 2)
		DuHatchery();
	if(lAmountOfBases == 3)
		TriHatchery();
	if(lAmountOfBases > 3)
		TriHatchery();
}

void OverlordManager::UniHatchery()
{
	if(mOverlord.size() >= 1)
	{
		mOverlord.at(0)->SetOverlordModule(OverlordState::GridSearch, (void*)0);
	}
	if(mOverlord.size() >= 2)
	{
		mOverlord.at(1)->SetOverlordModule(OverlordState::Explore, (void*)0);
	}	
	for(int i = 2; i < mOverlord.size(); i++)
	{ 
		mOverlord.at(i)->SetOverlordModule(OverlordState::Monitor, (void*)mPointOfInterest->at(0));
	}
}

void OverlordManager::DuHatchery()
{
	if(mOverlord.size() >= 1)
	{
		mOverlord.at(0)->SetOverlordModule(OverlordState::GridSearch, (void*)0);
	}
	if(mOverlord.size() >= 2)
	{
		mOverlord.at(1)->SetOverlordModule(OverlordState::Explore, (void*)0);
	}	
	for(int i = 2; i < mOverlord.size(); i++)
	{ 
		if(i >= mOverlord.size()/2)
			mOverlord.at(i)->SetOverlordModule(OverlordState::Monitor, (void*)mPointOfInterest->at(0));
		else if(i < mOverlord.size()/2)
			mOverlord.at(i)->SetOverlordModule(OverlordState::Monitor, (void*)mPointOfInterest->at(1));
	}
}

void OverlordManager::TriHatchery()
{
	if(mOverlord.size() >= 1)
	{
		mOverlord.at(0)->SetOverlordModule(OverlordState::GridSearch, (void*)0);
	}
	if(mOverlord.size() >= 2)
	{
		mOverlord.at(1)->SetOverlordModule(OverlordState::Explore, (void*)0);
	}	
	for(int i = 2; i < mOverlord.size(); i++)
	{ 
		if(i >= mOverlord.size()/3)
			mOverlord.at(i)->SetOverlordModule(OverlordState::Monitor, (void*)mPointOfInterest->at(0));
		else if(i < mOverlord.size()/3 && i >= mOverlord.size()/2)
			mOverlord.at(i)->SetOverlordModule(OverlordState::Monitor, (void*)mPointOfInterest->at(1));
		else if(i < mOverlord.size()/3)
			mOverlord.at(i)->SetOverlordModule(OverlordState::Monitor, (void*)mPointOfInterest->at(1));
	}
}

void OverlordManager::MultipleHatchery()
{

}

void OverlordManager::computeActions()
{
	int cFrame = Broodwar->getFrameCount();
	if (cFrame - lastCallFrame < 50)
	{
		return;
	}
	lastCallFrame = cFrame;
	UpdateGoal();
}