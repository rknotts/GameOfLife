// GameOfLife.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Grid.h"
#include "GridInputParser.h"
#include "GenerationManager.h"

using namespace std;

void showHelp()
{
	cout << "GameOfLife.exe [-h][-f inputFile][-g <iterations>]" << endl;
	cout << "   -h             : show this help text" << endl;
	cout << "   -f <inputFile> : input filename for grid initialization" << endl;
	cout << "   -g <iterations>: specify number of iterations to model, 'c' for continuous" << endl;
	cout << "   -q             : quiet mode - don't print out itermediate grid states (does not" << endl;
	cout << "                                 apply to 'continuous' mode)" << endl;
	cout << endl;
	cout << "   Grid initialization should be one cell per line, format (<col>, <row)." << endl << endl;
	cout << "   If no input file is specified, user will be prompted to enter cells" << endl;
	cout << "   one line at a time. An empty line indicates the end of grid input." << endl << endl;
	cout << "   If no number of iterations is specified in the command line args, " << endl;
	cout << "   the user will be prompted for a number of iterations to proceed." << endl;
	cout << "   The character 'c' may be entered for continuous generations" << endl;
	cout << "   until the program is interrupted." << endl;
}

// class to parse command line arguments
class CommandParser
{
public:
	CommandParser(int argc, char **argv)
	{
		for (int i = 1; i < argc; i++)
		{
			args.push_back(string(argv[i]));
		}
	}

	bool flagSpecified(string flag)
	{
		return find(args.begin(), args.end(), flag) != args.end();
	}

	string getFlaggedArgument(string flag)
	{
		vector<string>::iterator argIterator = find(args.begin(), args.end(), flag);
		if (argIterator != args.end() && (++argIterator) != args.end())
		{
			return *argIterator;
		}

		return "";
	}

private:
	vector<string> args;
};

int main(int argc, char **argv)
{
	CommandParser *cp = new CommandParser(argc, argv);
	// check for help switch
	if (cp->flagSpecified("-h"))
	{
		showHelp();
		return 0;
	}

	Grid *startingGrid = new Grid();
	GridInputParser *gip = new GridInputParser();

	// check for input file switch
	if (cp->flagSpecified("-f"))
	{
		string inputFilename = cp->getFlaggedArgument("-f");
		if (inputFilename == "")
		{
			showHelp();
			return 0;
		}
		cout << "Reading input file: " << inputFilename << endl;
		ParserReturnCode prc = gip->parseInputFile(inputFilename, startingGrid);
	}
	else
	{
		// get grid input from stdin
		cout << "Please enter starting grid live cells in the form '(<col>, <row>)'." << endl;
		cout << "Enter an empty line to indicate grid entry is complete." << endl;
		string inputLine;
		while (cin)
		{
			getline(cin, inputLine);
			if (inputLine.length() == 0)
			{
				cout << "Starting grid input complete" << endl;
				break;
			}
			Cell c;
			ParserReturnCode prc = gip->parseInputLine(inputLine, &c);
			if (prc == ParserError)
			{
				cout << "Invalid cell entry: " << inputLine << endl;
			}
			else
			{
				c.state.isAlive = true;
				c.state.neighborCount = UNKNOWN_NEIGHBOR_COUNT;
				startingGrid->insertCell(c);
			}
		}
	}

	int gens = 0;
	bool continuousGens = false;
	// check for # of generations
	if (cp->flagSpecified("-g"))
	{
		string genString = cp->getFlaggedArgument("-g");
		if (genString == "")
		{
			showHelp();
			return 0;
		}

		if (genString == "c")
		{
			continuousGens = true;
		}
		else
		{

			try
			{
				gens = stoi(genString);
			}
			catch (exception e)
			{
				showHelp();
				return 0;
			}
		}
	}
	else
	{
		// get number of generations from stdin
		while (gens == 0 && continuousGens == false)
		{
			cout << "Please enter the number of generations to simulate ('c' for continuous): ";
			string genString;
			cin >> genString;
			if (genString == "c")
			{
				continuousGens = true;
			}
			else
			{
				try
				{
					gens = stoi(genString);
				}
				catch (exception e)
				{
					cout << "Invalid entry: please enter an integer value" << endl;
				}
			}
		}
	}
	if (continuousGens)
	{
		cout << "Will run continuously until interrupted." << endl;
	}
	else
	{
		cout << "Number of generations: " << gens << endl;
	}

	bool quiet = cp->flagSpecified("-q");
	if (quiet && !continuousGens)
	{
		cout << "Quiet mode - suppressing intermediate grid state printing." << endl;
	}

	cout << endl;

	GenerationManager *gm = new GenerationManager(startingGrid);
	gm->printGeneration();

	if (continuousGens)
	{
		while (true)
		{
			gm->incrementGeneration();
			gm->printGeneration();
		}
	}
	else
	{
		for (int i = 0; i < gens; i++)
		{
			gm->incrementGeneration();
			if (!quiet)
			{
				gm->printGeneration();
			}
		}
		if (quiet) // go ahead and print out final state...
		{
			gm->printGeneration();
		}
	}

    return 0;
}
