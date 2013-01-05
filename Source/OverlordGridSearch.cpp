#include "OverlordGridSearch.h"

OverlordGridSearch::OverlordGridSearch()
{
	
}

OverlordGridSearch::OverlordGridSearch(UnitAgent* lAgent)
{
	int x = Broodwar->mapWidth();
	int y = Broodwar->mapHeight();
	Position lTopLeft = Position(0,0);
	Position lBotRight = Position(x, y);

	int lDistanceTopLeft = lAgent->getUnit()->getPosition().getApproxDistance(lTopLeft);
	int lDistanceRightBot = lAgent->getUnit()->getPosition().getApproxDistance(lBotRight);

	if(lDistanceTopLeft < lDistanceRightBot)
	{
		mStartCorner = lTopLeft;
	}
	else
		mStartCorner = lBotRight;
	lAgent->setGoal(TilePosition(mStartCorner));
}

OverlordGridSearch::~OverlordGridSearch()
{

}

void OverlordGridSearch::computeActions(UnitAgent* lAgent)
{
	
}