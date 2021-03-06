#ifndef __PROFILEROBJ_H__
#define __PROFILERBJ_H__

#include "BaseAgent.h"

using namespace BWAPI;
using namespace std;

/** Helper class for Profiler. This class represents a profiling of one specific
 * codeblock. Profiling can be done on any number of codeblocks.
 *
 * Author: Johan Hagelback (johan.hagelback@gmail.com)
 */
class ProfilerObj {

private:
	int startTime;
	int endTime;
	string id;
	int maxTime;
	int total;
	int startCalls;
	int endCalls;
	int lastShowFrame;

	int timeouts_short;
	int timeouts_medium;
	int timeouts_long;

public:
	/** Constructor */
	ProfilerObj(string mId);

	/** Destructor */
	~ProfilerObj();

	/** Checks if this object matches the specified id string. */
	bool matches(string mId);

	/** Starts measuring a codeblock. */
	void start();

	/** Stops measuring a codeblock. */
	void end();

	/** Returns the time elapsed between last start and end (in milliseconds). */
	int getElapsed();

	/** Print data to the ingame chat window. */
	void show();

	/** Returns the html string for this profiling object. */
	string getDumpStr();
};

#endif
