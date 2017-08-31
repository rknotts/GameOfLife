#include "stdafx.h"
#include "RuleSet.h"
#include <algorithm>

using namespace std;

RuleSet::RuleSet()
{
	maxNeighbors = 8;
	liveToLive = { 2, 3 };
	//liveToDead[] = { 0, 1, 4, 5, 6, 7, 8 }; // (can be assumed from above)
	deadToLive = { 3 };
	//deadToDead[] = { 0, 1, 2, 4, 5, 6, 7, 8 }; // (can be assumed from above)
}


RuleSet::~RuleSet()
{
}

bool RuleSet::newState(bool startState, unsigned short liveNeighbors)
{
	if (liveNeighbors > maxNeighbors) {
		return false;
	}
	if (startState) { // if starting with a live cell
		return find(begin(liveToLive), end(liveToLive), liveNeighbors) != end(liveToLive);
	}
	else { // if starting with a dead cell
		return find(begin(deadToLive), end(deadToLive), liveNeighbors) != end(deadToLive);
	}

	return false; // shouldn't get here, but kick out if we do
}
