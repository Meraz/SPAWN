#include "OverlordGridSearch.h"

OverlordGridSearch::OverlordGridSearch(UnitAgent* lAgent) : OverlordModule(lAgent)
{
	MovementYdirection = 20;
	TilePosition lTopLeft = TilePosition(5,10);
	TilePosition lBotRight = TilePosition(xMax-5, yMax-10);

	int lDistanceTopLeft = lAgent->getUnit()->getTilePosition().getDistance(lTopLeft);
	int lDistanceRightBot = lAgent->getUnit()->getTilePosition().getDistance(lBotRight);

	if(lDistanceTopLeft < lDistanceRightBot)
	{
		mStartCorner = lTopLeft;
	}
	else
		mStartCorner = lBotRight;
}

OverlordGridSearch::~OverlordGridSearch()
{

}

void OverlordGridSearch::UpdateParamter(void* lParamter)
{
	mAgent->setGoal(mStartCorner);
}

void OverlordGridSearch::computeActions()
{
	int a = mAgent->getUnit()->getTilePosition().getDistance(mAgent->getGoal());
	
	//Broodwar->printf("Pos.x %d ", lAgent->getUnit()->getTilePosition().x());
	//Broodwar->printf("Pos.x %d ", lAgent->getUnit()->getTilePosition().y());
	//Broodwar->printf("Goal.x %d ", lAgent->getGoal().x());
	//Broodwar->printf("Goal.y %d ", lAgent->getGoal().y());
	//Broodwar->printf("Came here. a = %d ", a);
	//Broodwar->pauseGame();


	if(a < 5)
	{
		NextGoal();
	}
}
 
void OverlordGridSearch::NextGoal()
{
	TilePosition nGoal;
	Unit* lUnit = mAgent->getUnit();
	TilePosition lPos = lUnit->getTilePosition();
	

	if(lUnit->getTilePosition().y() <  10 || lUnit->getTilePosition().y() > yMax-10)
		MovementYdirection *= -1;
   
	int lY = lUnit->getTilePosition().y() + MovementYdirection;
	if(lY < 10)
		lY = 10;
	if(lY > yMax-10)
		lY = yMax-10;

    if(lUnit->getTilePosition().x() < 5)
    {
		nGoal = TilePosition(xMax-5, lY);
		//setgoal(Xmax, currentYpos + MovementYDirection);
    }   
    else if(lUnit->getTilePosition().x() > xMax-5)
    {		
		nGoal = TilePosition(5, lY);
		//setgoal(0, currentYpos + MovementYDirection);
    }   

	if (nGoal.x() >= 0)
	{
		mAgent->setGoal(nGoal);
	}
}