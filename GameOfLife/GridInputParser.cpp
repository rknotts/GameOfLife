#include "stdafx.h"
#include "GridInputParser.h"
#include <sstream>
#include <iterator>
#include <fstream>


using namespace std;

GridInputParser::GridInputParser()
{
}

GridInputParser::~GridInputParser()
{
}

// Parsing Utils--------------------
string& trimRight(string &s, const string& delimiters = " \f\n\r\t\v")
{
	return s.erase(s.find_last_not_of(delimiters) + 1);
}

string& trimLeft(string &s, const string& delimiters = " \f\n\r\t\v")
{
	return s.erase(0, s.find_first_not_of(delimiters));
}

string& trim(string &s, const string &delimiters = " \f\n\r\t\v")
{
	return trimLeft(trimRight(s, delimiters), delimiters);
}

template<typename Out>
void splitString(const string &s, char delim, Out result) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		*(result++) = item;
	}
}

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	splitString(s, delim, back_inserter(elems));
	return elems;
}

// Primary parsing methods -------------------------
ParserReturnCode GridInputParser::parseInputFile(string fileName, Grid *grid)
{
	if (fileName.length() <= 0)
	{
		return ParserError;
	}
	Cell c;
	c.state.isAlive = true;
	c.state.neighborCount = UNKNOWN_NEIGHBOR_COUNT;
	string inputString;

	ifstream infile;
	infile.open(fileName);
	while (!infile.eof())
	{
		getline(infile, inputString);
		if (this->parseInputLine(inputString, &c) == ParserError) {
			return ParserError;
		}
		grid->insertCell(c);
	}
	infile.close();
	return ParserOK;
}

ParserReturnCode GridInputParser::parseInputLine(string line, Cell *cell)
{
	size_t startIndex = line.find('(');
	size_t midIndex = line.find(',');
	size_t endIndex = line.find(')');
	if (startIndex == string::npos ||
		midIndex == string::npos ||
		endIndex == string::npos)
	{
		return ParserError;
	}
	if (startIndex >= midIndex ||
		midIndex >= endIndex)
	{
		return ParserError;
	}

	// increment startIndex since we don't want to include the opening paren
	startIndex++;
	string colString = line.substr(startIndex, midIndex - startIndex);
	colString = trim(colString);
	char *sEnd;
	cell->column = strtoll(colString.c_str(), &sEnd, 10);

	// increment midIndex since we don't want to include the ','
	midIndex++;
	string rowString = line.substr(midIndex, endIndex - midIndex);
	rowString = trim(rowString);
	cell->row = strtoll(rowString.c_str(), &sEnd, 10);

	return ParserOK;
}

