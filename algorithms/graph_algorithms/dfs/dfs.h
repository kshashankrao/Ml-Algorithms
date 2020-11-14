#pragma once
#include <vector>
#include <iostream>

#define GRID_ROWS 5
#define GRID_COLS 5
#define TOTAL_NEIGHBORS 8

using namespace std;

class DFS
{

public:
	void dfs_doit(vector<vector<int>> map);
	void dfs_run(vector<vector<int>> map, int row, int col, bool visited[GRID_ROWS][GRID_COLS]);
};