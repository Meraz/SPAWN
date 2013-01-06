#include "OverlordGridSearch.h"

OverlordGridSearch::OverlordGridSearch()
{
	
}

OverlordGridSearch::OverlordGridSearch(UnitAgent* lAgent)
{
	MovementYdirection = 20;
	xMax = Broodwar->mapWidth();
	yMax = Broodwar->mapHeight();
	TilePosition lTopLeft = TilePosition(5,5);
	TilePosition lBotRight = TilePosition(xMax-5, yMax-5);

	int lDistanceTopLeft = lAgent->getUnit()->getTilePosition().getDistance(lTopLeft);
	int lDistanceRightBot = lAgent->getUnit()->getTilePosition().getDistance(lBotRight);

	if(lDistanceTopLeft < lDistanceRightBot)
	{
		mStartCorner = lTopLeft;
	}
	else
		mStartCorner = lBotRight;
	lAgent->setGoal(mStartCorner);
	Broodwar->printf("Startcorner.x: %d", mStartCorner.x());
	Broodwar->printf("Startcorner.y: %d", mStartCorner.y());

}

OverlordGridSearch::~OverlordGridSearch()
{

}

void OverlordGridSearch::computeActions(UnitAgent* lAgent)
{
	int a = lAgent->getUnit()->getTilePosition().getDistance(lAgent->getGoal());
	
	Broodwar->printf("Pos.x %d ", lAgent->getUnit()->getTilePosition().x());
	Broodwar->printf("Pos.x %d ", lAgent->getUnit()->getTilePosition().y());
	Broodwar->printf("Goal.x %d ", lAgent->getGoal().x());
	Broodwar->printf("Goal.y %d ", lAgent->getGoal().y());
	Broodwar->printf("Came here. a = %d ", a);
	Broodwar->pauseGame();


	if(a < 5)
	{
		Broodwar->printf("Came here. a = %d ", a);
		NextGoal(lAgent);
	}
	
	//if (nGoal.x() >= 0)
	//{
	//	lAgent->setGoal(nGoal);
	//}



}
 
void OverlordGridSearch::NextGoal(UnitAgent* lAgent)
{
	TilePosition nGoal;

	Unit* lUnit = lAgent->getUnit();
	if(lUnit->getTilePosition().y() <  10 || lUnit->getTilePosition().y() > yMax-10)
		MovementYdirection *= -1;
   
	int lY = lUnit->getTilePosition().y() + MovementYdirection;
	if(lY < 5)
		lY = 5;
	if(lY > yMax-5)
		lY = yMax-5;

    if(lUnit->getTilePosition().x() < 10)
    {
		nGoal = TilePosition(5, lY);
		//setgoal(Xmax, currentYpos + MovementYDirection);
    }
   
    else if(lUnit->getTilePosition().x() > xMax-10)
    {		
		nGoal = TilePosition(xMax-5, lY);
		//setgoal(0, currentYpos + MovementYDirection);
    }   

	if (nGoal.x() >= 0)
	{
		lAgent->setGoal(nGoal);
	}
}