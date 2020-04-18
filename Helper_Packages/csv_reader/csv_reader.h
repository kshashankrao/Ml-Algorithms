#pragma once
#include <vector>
#include <string>

using namespace std;

class CSVReader
{
	string fileName;
	string delimeter;
public:
	/* Contructor
	   Input - Filename
			   Delimitor - Default "," 
	*/
	CSVReader(string filename, string delm = ",") : fileName(filename), delimeter(delm)
	{ }
	/* Main function to retrieve data */
	vector<vector<string> > getData();
};
