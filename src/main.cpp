#include<vector>
#include<string>
#include <iostream>
#include "graph_search/dfs/dfs.h"
using namespace std;

int main()
{
	vector<vector<int>> map {{ 1, 1, 0, 0, 0 },
							 { 1, 1, 0, 0, 0 },
							 { 0, 0, 0, 1, 1 },
							 { 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0 } };
	DFS dfs;
	dfs.dfs_doit(map);
	return 1;
}