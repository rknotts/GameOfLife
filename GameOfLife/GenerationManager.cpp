#include "stdafx.h"
#include "GenerationManager.h"
#include <iostream>

using namespace std;

GenerationManager::GenerationManager(Grid *startingGrid)
{
	currentGen = 0;
	grid = startingGrid;
}

GenerationManager::~GenerationManager()
{
	delete grid;
}

void GenerationManager::incrementGeneration()
{
	Grid *temp;
	grid->addNeighborCells();
	temp = grid->generateNextGrid();
	delete grid;
	grid = temp;
	currentGen++;
}

void GenerationManager::incrementMultipleGenerations(unsigned int numGens)
{
	for (unsigned int i = 0; i < numGens; i++)
	{
		this->incrementGeneration();
	}
}

unsigned long GenerationManager::getCurrentGeneration()
{
	return currentGen;
}

void GenerationManager::printGeneration()
{
	cout << "Generation " << currentGen << ":" << endl;
	grid->printGridState();
}
