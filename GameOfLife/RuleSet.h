#pragma once
#include <vector>

class RuleSet
{
public:
	RuleSet();
	~RuleSet();
	bool newState(bool startState, unsigned short liveNeighbors);

private:
	std::vector<unsigned short> liveToLive;
	std::vector<unsigned short> deadToLive;
	unsigned short maxNeighbors;
};

