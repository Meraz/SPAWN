#include "DefilerAgent.h"
#include "PFManager.h"
#include "AgentManager.h"
#include "TargetingAgent.h"

DefilerAgent::DefilerAgent(Unit* mUnit)
{
	unit = mUnit;
	type = unit->getType();
	unitID = unit->getID();
	agentType = "DefilerAgent";
	//Broodwar->printf("DefilerAgent created (%s)", unit->getType().getName().c_str());
	
	goal = TilePosition(-1, -1);
}

void DefilerAgent::computeActions()
{
	bool defensive = true;
	PFManager::getInstance()->computeAttackingUnitActions(this, goal, defensive);

	if(unit->isUnderAttack())
	{
		unit->useTech(TechTypes::Dark_Swarm, unit);
	}

	if(enemyUnitsWithinRange(9*32))
	{
		Unit* lUnit = 0;
		for(set<Unit*>::const_iterator i=Broodwar->enemy()->getUnits().begin(); i!=Broodwar->enemy()->getUnits().end(); i++)
		{
			//Enemy seen
			if ((*i)->exists())
			{
				if(lUnit)
				if(unit->getDistance((*i)) < 9*32)
				{
						unit->useTech(TechTypes::Plague, (*i));	
						return;
				}
			}
		}
	}
}
