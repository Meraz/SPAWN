#include "RefineryAgent.h"
#include "WorkerAgent.h"
#include "AgentManager.h"

RefineryAgent::RefineryAgent(Unit* mUnit)
{
	unit = mUnit;
	type = unit->getType();
	unitID = unit->getID();
	agentType = "RefineryAgent";
}

void RefineryAgent::computeActions()
{
	for (int i = 0; i < (int)assignedWorkers.size(); i++)
	{
		if (!assignedWorkers.at(i)->isAlive())
		{
			assignedWorkers.erase(assignedWorkers.begin() + i);
			return;
		}
		if (!assignedWorkers.at(i)->getUnit()->isGatheringGas())
		{
			assignedWorkers.erase(assignedWorkers.begin() + i);
			return;
		}
	}
	if(ResourceManager::getInstance()->CompareGasMineralRatio(0.5f))
	{
		if ((int)assignedWorkers.size() <= 3)
		{
			if (!unit->isBeingConstructed())
			{
				WorkerAgent* worker = (WorkerAgent*)AgentManager::getInstance()->findClosestFreeWorker(unit->getTilePosition());
				if (worker != NULL)
				{
					worker->getUnit()->rightClick(unit);
					worker->setState(WorkerAgent::GATHER_GAS);
					assignedWorkers.push_back(worker);
					
				}
			}
		}
	}
	/*else
	{
		for(int i = 0; i < (int)assignedWorkers.size(); i++)
		{
			WorkerAgent* worker = (WorkerAgent*)assignedWorkers.at(i);
			worker->reset();
			assignedWorkers.erase(assignedWorkers.begin() + i);
		}
	}*/
}
