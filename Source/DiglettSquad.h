#ifndef __DIGLETTSQUAD_H__
#define __DIGLETTSQUAD_H__

#include "BaseAgent.h"
#include "Squad.h"
#include <list>

using namespace BWAPI;
using namespace std;

/** This class handle squads used to explore the game world. Any unit type
 * can be used as explorer.
 *
 * Author: Johan Hagelback (johan.hagelback@gmail.com)
 */
class DiglettSquad : public Squad {
private:
	bool assignedGoals;
	bool membersBurrowed;
	TilePosition* goals;
	unsigned int  nrBasePositions;
	unsigned int  agentToBurrow;
	bool launch;


private:
	void assignGoals();
	bool isMembersBurrowAble();
	void burrowMembers();
	bool isSquadCloseTo(TilePosition mGoal);
	bool isCurrentAgentBurrowed();
	void nextGoal();

public:
	/** Constructor. See Squad.h for more details. */
	DiglettSquad(int mId, string mName, int mPriority);
	~DiglettSquad();

	/** Returns true if this Squad is active, or false if not.
	 * A Squad is active when it first has been filled with agents.
	 * A Squad with destroyed units are still considered Active. */
	bool isActive();

	/** Called each update to issue orders. */
	void computeActions();

	/** Orders this squad to defend a position. */
	void defend(TilePosition mGoal);

	/** Orders this squad to launch an attack at a position. */
	void attack(TilePosition mGoal);

	/** Orders this squad to assist units at a position. */
	void assist(TilePosition mGoal);

	/** Clears the goal for this Squad, i.e. sets the goal
	 * to TilePosition(-1,-1). */
	void clearGoal();

	/** Returns the current goal of this Squad. */
	TilePosition getGoal();

	/** Returns true if this squad has an assigned goal. */
	bool hasGoal();

	/** Prints some info about the squad. */
	void printInfo();
};

#endif
