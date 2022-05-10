#pragma once
#include <vector>
#include <iostream>

#define GRID_ROWS 5
#define GRID_COLS 5
#define TOTAL_NEIGHBORS 8

using namespace std;

class BFS
{
private:
	vector<vector<int>> grid;
	int ref_vertice;

public:
	void set_grid(vector<vector<int>> map);
	void bfs_doit();
};