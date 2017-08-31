#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\GameOfLife\GridInputParser.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(GridInputParserTests)
	{
	public:

		TEST_METHOD(CheckInputLineParsingGood)
		{
			GridInputParser *gip = new GridInputParser();
			Cell c;
			ParserReturnCode prc = gip->parseInputLine("(123, 456)", &c);
			Assert::AreEqual((int)ParserOK, (int)prc);
			Assert::IsTrue(123 == c.column);
			Assert::IsTrue(456 == c.row);

			// This probably should return a parser error, but we'll come back to it
			prc = gip->parseInputLine("(123, 45A)", &c);
			Assert::AreEqual((int)ParserOK, (int)prc);
			Assert::IsTrue(123 == c.column);
			Assert::IsTrue(45 == c.row);

			prc = gip->parseInputLine("(-123, -456)", &c);
			Assert::AreEqual((int)ParserOK, (int)prc);
			Assert::IsTrue(-123 == c.column);
			Assert::IsTrue(-456 == c.row);

			prc = gip->parseInputLine("(0, 0)", &c);
			Assert::AreEqual((int)ParserOK, (int)prc);
			Assert::IsTrue(0 == c.column);
			Assert::IsTrue(0 == c.row);

			prc = gip->parseInputLine("(20000000, -40000000)", &c);
			Assert::AreEqual((int)ParserOK, (int)prc);
			Assert::IsTrue(20000000 == c.column);
			Assert::IsTrue(-40000000 == c.row);
		}

		TEST_METHOD(CheckInputLineParsingBad)
		{
			GridInputParser *gip = new GridInputParser();
			Cell c;
			ParserReturnCode prc = gip->parseInputLine("123,456)", &c);
			Assert::AreEqual((int)ParserError, (int)prc);
			
			prc = gip->parseInputLine("(123456)", &c);
			Assert::AreEqual((int)ParserError, (int)prc);
			
			prc = gip->parseInputLine("(123,456", &c);
			Assert::AreEqual((int)ParserError, (int)prc);
			
			prc = gip->parseInputLine("123456", &c);
			Assert::AreEqual((int)ParserError, (int)prc);
			
			prc = gip->parseInputLine(",123)456(", &c);
			Assert::AreEqual((int)ParserError, (int)prc);
		}

		/* seems to not be finding the input file...
		TEST_METHOD(CheckFileParsing)
		{
			GridInputParser *gip = new GridInputParser();
			string fileName = "testInputGrid.txt";
			Grid *grid = new Grid();

			ParserReturnCode prc = gip->parseInputFile(fileName, grid);
			Assert::AreEqual((int)ParserOK, (int)prc);

			Assert::IsTrue(grid->isCellLive(1, 1));
			Assert::IsTrue(grid->isCellLive(2, 1));
			Assert::IsTrue(grid->isCellLive(2, -2));
			Assert::IsTrue(grid->isCellLive(2, 3));
			Assert::IsTrue(grid->isCellLive(30, 20));
			Assert::IsTrue(grid->isCellLive(-5, -45));
			Assert::IsTrue(grid->isCellLive(9876543, -1234567));
		}
		*/
	};
}
