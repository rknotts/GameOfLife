#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\GameOfLife\Grid.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(GridTests)
	{
	public:
		//

		Grid *setupGrid()
		{
			Grid *grid = new Grid();
			Cell c1, c2, c3, c4, c5, c6;
			c1.column = 1;
			c1.row = 1;
			c1.state.isAlive = true;
			c1.state.neighborCount = -1;
			c2.column = 2;
			c2.row = 1;
			c2.state.isAlive = true;
			c2.state.neighborCount = -1;
			c3.column = 3;
			c3.row = 1;
			c3.state.isAlive = true;
			c3.state.neighborCount = -1;
			c4.column = 2;
			c4.row = 2;
			c4.state.isAlive = true;
			c4.state.neighborCount = -1;
			c5.column = -1;
			c5.row = -1;
			c5.state.isAlive = true;
			c5.state.neighborCount = -1;
			c6.column = numeric_limits<int64_t>::min();
			c6.row = 0;
			c6.state.isAlive = true;
			c6.state.neighborCount = -1;

			grid->insertCell(c1);
			grid->insertCell(c2);
			grid->insertCell(c3);
			grid->insertCell(c4);
			grid->insertCell(c5);
			grid->insertCell(c6);

			return grid;
		}

		TEST_METHOD(GridCheckLiveCells)
		{
			Grid *grid = setupGrid();
			Assert::IsTrue(grid->isCellLive(1, 1));
			Assert::IsTrue(grid->isCellLive(2, 1));
			Assert::IsTrue(grid->isCellLive(2, 2));
			Assert::IsTrue(grid->isCellLive(-1, -1));
			Assert::IsTrue(grid->isCellLive(numeric_limits<int64_t>::min(), 0));
		}

		TEST_METHOD(GridCheckDeadCells)
		{
			Grid *grid = setupGrid();
			Assert::IsFalse(grid->isCellLive(4, 3));
			Assert::IsFalse(grid->isCellLive(10000, -200000));
			Assert::IsFalse(grid->isCellLive(-20, 40));
			Assert::IsFalse(grid->isCellLive(-2, -15));
			Assert::IsFalse(grid->isCellLive(numeric_limits<int64_t>::max(), numeric_limits<int64_t>::max()));
		}

		TEST_METHOD(GridCountNeighbors)
		{
			Grid *grid = setupGrid();
			Assert::AreEqual((short)2, grid->countLiveNeighbors(1, 1));
			Assert::AreEqual((short)3, grid->countLiveNeighbors(2, 1));
			Assert::AreEqual((short)0, grid->countLiveNeighbors(-1, -1));
			Assert::AreEqual((short)2, grid->countLiveNeighbors(3, 1));
			Assert::AreEqual((short)3, grid->countLiveNeighbors(3, 2));
			Assert::AreEqual((short)0, grid->countLiveNeighbors(10, 10));
			Assert::AreEqual((short)2, grid->countLiveNeighbors(0, 0));
			Assert::AreEqual((short)1, grid->countLiveNeighbors(numeric_limits<int64_t>::min(), 1));
			Assert::AreEqual((short)0, grid->countLiveNeighbors(numeric_limits<int64_t>::max(), 0));
			Assert::AreEqual((short)0, grid->countLiveNeighbors(numeric_limits<int64_t>::max(), numeric_limits<int64_t>::max()));
		}

		TEST_METHOD(GridCheckCellRemoval)
		{
			Grid *grid = setupGrid();
			grid->removeCell(1, 1);
			grid->removeCell(2, 1);
			grid->removeCell(10, 10);
			grid->removeCell(-1, -1);
			grid->removeCell(numeric_limits<int64_t>::min(), 0);
			Assert::IsFalse(grid->isCellLive(1, 1));
			Assert::IsFalse(grid->isCellLive(2, 1));
			Assert::IsFalse(grid->isCellLive(10, 10));
			Assert::IsFalse(grid->isCellLive(-1, -1));
			Assert::IsFalse(grid->isCellLive(numeric_limits<int64_t>::min(), 0));
		}
	};
}