#pragma once
#include <stdint.h>
#include <map>

const short UNKNOWN_NEIGHBOR_COUNT = -1;

struct CellState
{
	bool isAlive;
	short neighborCount;
};

struct Cell
{
	int64_t column;
	int64_t row;
	CellState state;
};

class Grid
{
public:
	Grid();
	~Grid();
	void insertCell(Cell c);
	bool isCellLive(int64_t column, int64_t row);
	void removeCell(int64_t column, int64_t row);
	short countLiveNeighbors(int64_t column, int64_t row);
	
	void addNeighborCells();
	Grid *generateNextGrid();

	void printGridState();

private:
	std::map<int64_t, std::map<int64_t, CellState> > matrix;
	void addNeighborsForCell(int64_t col, int64_t row);
	bool cellExists(int64_t column, int64_t row);
};

