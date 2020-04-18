#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "csv_reader.h"

using namespace std;

vector<std::vector<std::string>> CSVReader::getData()
{
	std::ifstream file(fileName);
	std::vector<std::vector<std::string> > dataList;
	std::string line = "";
	while (getline(file, line))
	{
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		dataList.push_back(vec);
	}
	file.close();
	return dataList;
}

/* Example to run the CSV Reader*/
int csv_reader_main()
{
	CSVReader reader("example.csv");
	vector<vector<string> > dataList = reader.getData();
	for (vector<string> vec : dataList)
	{
		for (string data : vec)
		{
			cout << data << " , ";
		}
		cout << std::endl;
	}
	return 0;
}