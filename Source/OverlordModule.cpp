#include "OverlordModule.h"

OverlordModule::OverlordModule()
{

}

OverlordModule::~OverlordModule()
{

}



void OverlordModule::computeActions(UnitAgent* lAgent)
{
	if(lAgent->getUnit()->isUnderAttack())
	{
		//Do something
	}
}