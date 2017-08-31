#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Grid.h"

using namespace std;

enum ParserReturnCode
{
	ParserOK = 0,
	ParserError = -1
};

class GridInputParser
{
public:
	GridInputParser();
	~GridInputParser();

	ParserReturnCode parseInputFile(string fileName, Grid *grid);
	ParserReturnCode parseInputLine(string line, Cell *cell);

private:

};

