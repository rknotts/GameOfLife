#pragma once
#include "Grid.h"

class GenerationManager
{
public:
	GenerationManager(Grid *startingGrid);
	~GenerationManager();
	
	void incrementGeneration();
	void incrementMultipleGenerations(unsigned int numGens);
	unsigned long getCurrentGeneration();

	void printGeneration();

private:
	unsigned long currentGen;
	Grid *grid;
};

