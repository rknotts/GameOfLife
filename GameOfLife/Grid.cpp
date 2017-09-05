#include "stdafx.h"
#include "Grid.h"
#include <iostream>
#include "RuleSet.h"

using namespace std;

Grid::Grid()
{
}


Grid::~Grid()
{
}

void Grid::insertCell(Cell c)
{
	matrix[c.column][c.row] = c.state;
}

bool Grid::cellExists(int64_t column, int64_t row)
{
	// find the column, then the row in the map of maps
	auto colIterator = matrix.find(column);
	if (colIterator != matrix.end())
	{
		if (colIterator->second.find(row) != colIterator->second.end())
		{
			return true;
		}
	}
	return false;
}

bool Grid::isCellLive(int64_t column, int64_t row)
{
	// find the column, then the row in the map of maps
	auto colIterator = matrix.find(column);
	if (colIterator != matrix.end())
	{
		map<int64_t, CellState> &rowMap = colIterator->second;
		auto rowIterator = rowMap.find(row);

		if (rowIterator != rowMap.end())
		{
			// return the 'alive' state of the found cell
			return rowIterator->second.isAlive;
		}
	}
	return false;
}

// turns out this isn't used for now...
void Grid::removeCell(int64_t column, int64_t row)
{
	auto colIterator = matrix.find(column);
	if (colIterator != matrix.end())
	{
		map<int64_t, CellState> &rowMap = colIterator->second;
		auto rowIterator = rowMap.find(row);

		if (rowIterator != rowMap.end())
		{
			if (rowMap.size() <= 1)
			{
				// if this was the only cell in the column, remove the column from the map
				matrix.erase(colIterator);
			}
			else
			{
				// otherwise, just remove the row entry
				rowMap.erase(rowIterator);
			}
		}
	}
}

short Grid::countLiveNeighbors(int64_t column, int64_t row)
{
	short neighborCount = 0;
	int64_t colStart, rowStart, colEnd, rowEnd;
	// set the index initial values and loop maxes
	// this will generally be from c.column-1 to c.column+1 (same for rows),
	// but cells up against the edges of the grid at int min and max will curtail those values
	colStart = (column == numeric_limits<int64_t>::min()) ? numeric_limits<int64_t>::min() : column - 1;
	colEnd = (column == numeric_limits<int64_t>::max()) ? numeric_limits<int64_t>::max() : column + 1;

	rowStart = (row == numeric_limits<int64_t>::min()) ? numeric_limits<int64_t>::min() : row - 1;
	rowEnd = (row == numeric_limits<int64_t>::max()) ? numeric_limits<int64_t>::max() : row + 1;

	// iterate over that 3x3 (or smaller) square of cells
	for (int64_t colIndex = colStart; colIndex >= colStart && colIndex <= colEnd; colIndex++)
	{
		for (int64_t rowIndex = rowStart; rowIndex >= rowStart && rowIndex <= rowEnd; rowIndex++)
		{
			// don't count the cell in the middle
			if (!(colIndex == column && rowIndex == row))
			{
				if (isCellLive(colIndex, rowIndex))
				{
					neighborCount++;
				}
			}
		}
	}
	return neighborCount;
}

void Grid::addNeighborsForCell(int64_t column, int64_t row)
{
	int64_t colStart, rowStart, colEnd, rowEnd;
	colStart = (column == numeric_limits<int64_t>::min()) ? numeric_limits<int64_t>::min() : column - 1;
	colEnd = (column == numeric_limits<int64_t>::max()) ? numeric_limits<int64_t>::max() : column + 1;

	rowStart = (row == numeric_limits<int64_t>::min()) ? numeric_limits<int64_t>::min() : row - 1;
	rowEnd = (row == numeric_limits<int64_t>::max()) ? numeric_limits<int64_t>::max() : row + 1;

	for (int64_t colIndex = colStart; colIndex >= colStart && colIndex <= colEnd; colIndex++)
	{
		for (int64_t rowIndex = rowStart; rowIndex >= rowStart && rowIndex <= rowEnd; rowIndex++)
		{
			// skip the middle cell
			if (!(colIndex == column && rowIndex == row))
			{
				// if there's no cell in the grid, add a dead one
				if (!(this->cellExists(colIndex, rowIndex)))
				{
					Cell c;
					c.column = colIndex;
					c.row = rowIndex;
					c.state.isAlive = false;
					c.state.neighborCount = UNKNOWN_NEIGHBOR_COUNT;
					this->insertCell(c);
				}
			}
		}
	}
}


void Grid::addNeighborCells()
{
	// iterate through the grid, filling out the neighbors for all live cells
	for (auto colIterator = matrix.cbegin(); colIterator != matrix.cend(); colIterator++)
	{
		map<int64_t, CellState> rowMap = colIterator->second;
		for (auto rowIterator = rowMap.cbegin(); rowIterator != rowMap.cend(); rowIterator++)
		{
			const CellState cellState = rowIterator->second;
			if (cellState.isAlive)
			{
				this->addNeighborsForCell(colIterator->first, rowIterator->first);
			}
		}
	}

}

Grid *Grid::generateNextGrid()
{
	RuleSet *rules = new RuleSet();
	Grid *nextGrid = new Grid();

	// iterate through the grid
	for (auto const &colIterator : matrix)
	{
		for (auto const &rowIterator : colIterator.second)
		{
			// for each cell, if it hasn't had its live neighbors counted, count them
			CellState cellstate = rowIterator.second;
			if (cellstate.neighborCount == UNKNOWN_NEIGHBOR_COUNT)
			{
				cellstate.neighborCount = this->countLiveNeighbors(colIterator.first, rowIterator.first);
			}

			// check the rules for that cell:
			// if the cell will be alive in the next generation, add a new live cell to the new grid
			if (rules->newState(cellstate.isAlive, cellstate.neighborCount))
			{
				Cell c;
				c.column = colIterator.first;
				c.row = rowIterator.first;
				c.state.isAlive = true;
				c.state.neighborCount = UNKNOWN_NEIGHBOR_COUNT;
				nextGrid->insertCell(c);
			}
		}
	}
	delete rules;
	return nextGrid;
}

void Grid::printGridState()
{
	uint64_t count = 0;
	cout << "Live cells at:\n";
	for (auto const &col : matrix)
	{
		for (auto const &row : col.second)
		{
			if (row.second.isAlive)
			{
				cout << "  " << col.first << "," << row.first << ": n=" << row.second.neighborCount << "\n";
				count++;
			}
		}
	}
	cout << "Total Live Cells: " << count << "\n";
	cout << "\n";
}
