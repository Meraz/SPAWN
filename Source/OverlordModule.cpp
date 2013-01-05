#include "OverlordModule.h"

OverlordModule::OverlordModule()
{

}

OverlordModule::~OverlordModule()
{

}

void OverlordModule::UpdateParamter(void* lParamter)
{

}


void OverlordModule::computeActions(UnitAgent* lAgent)
{
	Broodwar->printf("Hej");
	if(lAgent->getUnit()->isUnderAttack())
	{
		//Do something
	}
}