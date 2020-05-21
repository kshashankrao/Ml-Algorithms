#include "dfs.h"

void DFS::dfs_doit(vector<vector<int>> map)
{
	bool visited[GRID_ROWS][GRID_COLS];
	memset(visited, false, sizeof(visited));

	int total_clusters = 0;
	for (int i = 0; i < GRID_ROWS; i++)
	{
		for (int j = 0; j < GRID_COLS; j++)
		{
			bool flag = true;

			if ((map[i][j] == 1) && (visited[i][j] == false))
			{
				DFS::dfs_run(map, i, j, visited);
				total_clusters++;
			}
			
		}
	}
	cout << total_clusters;
}

void DFS::dfs_run(vector<vector<int>> M, int row, int col,bool visited[GRID_ROWS][GRID_COLS])
{
	// Set the coordinates for the neighbors
	int neighbor_row[TOTAL_NEIGHBORS] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int neighbor_col[TOTAL_NEIGHBORS] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	// Set true for visited cells
	visited[row][col] = true;

	// Check for all ones in the neighboring nodes
	for (int k = 0; k < 8; ++k)
	{
		// Get 2d index of the neighbors
		int x_n = row + neighbor_row[k];
		int y_n = col + neighbor_col[k];

		// For valid nodes (1) check the extended neighbors
		if ((x_n >= 0) && (y_n >= 0) && (x_n < GRID_ROWS) && (y_n < GRID_COLS) && (M[x_n][y_n] == 1) && (visited[x_n][y_n] == false))
		{
			DFS::dfs_run(M, x_n, y_n, visited);
		}
	}
		
}

int dfs_main()
{
	vector<vector<int>> map{ { 1, 1, 0, 0, 0 },
							 { 1, 1, 0, 0, 0 },
							 { 0, 0, 0, 1, 1 },
							 { 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0 } };
	DFS dfs;
	dfs.dfs_doit(map);
	return 1;
}