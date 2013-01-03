#include "QueenAgent.h"
#include "PFManager.h"
#include "AgentManager.h"

QueenAgent::QueenAgent(Unit* mUnit)
{
	unit = mUnit;
	type = unit->getType();
	unitID = unit->getID();
	agentType = "QueenAgent";
	//Broodwar->printf("QueenAgent created (%s)", unit->getType().getName().c_str());
	
	goal = TilePosition(-1, -1);
}

void QueenAgent::computeActions()
{
	bool defensive = true;
	PFManager::getInstance()->computeAttackingUnitActions(this, goal, defensive);
	Spell_Spawn_Broodling();	
}

void QueenAgent::Spell_Spawn_Broodling()
{
	if(enemyUnitsWithinRange(9*32))
	{
		for(set<Unit*>::const_iterator i=Broodwar->enemy()->getUnits().begin(); i!=Broodwar->enemy()->getUnits().end(); i++)
		{
			//Enemy seen
			if ((*i)->exists())
			{
				if(unit->getDistance((*i)) < 9*32)
				{
					if( (*i)->getType() == UnitTypes::Terran_Siege_Tank_Tank_Mode ||
						(*i)->getType() == UnitTypes::Terran_Siege_Tank_Siege_Mode ||
						(*i)->getType() == UnitTypes::Protoss_Dark_Templar ||
						(*i)->getType() == UnitTypes::Protoss_High_Templar)
					{
						unit->useTech(TechTypes::Spawn_Broodlings, (*i));	
						return;
					}
					if((*i)->getType().isOrganic())
					{
						unit->useTech(TechTypes::Spawn_Broodlings, (*i));
						return;
					}
				}
			}
		}
	}
}