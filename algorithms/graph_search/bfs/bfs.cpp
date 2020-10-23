#include "bfs.h"
#include "print_function/print_function.h"
#include <vector>
#include <queue>
#include <utility>

using namespace std;

void BFS::set_grid(vector<vector<int>> map)
{
	this->grid = map;
}

void BFS::bfs_doit()
{
	print_2d_vector(this->grid);
	bool visited[GRID_ROWS][GRID_COLS];
	int total_clusters = 0;

	memset(visited, false, sizeof(visited));

	// Set the coordinates for the neighbors
	int neighbor_row[TOTAL_NEIGHBORS] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int neighbor_col[TOTAL_NEIGHBORS] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	
	vector<vector<pair<int, int>>> cluster_pts;
	
	for (int i = 0; i < GRID_ROWS; i++)
	{
		for (int j = 0; j < GRID_COLS; j++)
		{
			if ((this->grid[i][j] == 1) && (visited[i][j] == false))
			{				
				vector<pair<int, int>> cluster_pt;
				queue<pair<int, int>> q;
				q.push(make_pair(i, j));
				visited[i][j] = true;
				cluster_pt.push_back(make_pair(i,j));

				while (!q.empty())
				{
					int x = q.front().first;
					int y = q.front().second;

					q.pop();

					for (int k = 0; k < TOTAL_NEIGHBORS; k++)
					{
						int x_n = x + neighbor_row[k];
						int y_n = y + neighbor_col[k];

						if ((x_n >= 0) && (y_n >= 0) && (x_n < GRID_ROWS) && (y_n < GRID_COLS) && (this->grid[x_n][y_n] == 1) && (visited[x_n][y_n] == false))
						{
							visited[x_n][y_n] = true;
							q.push(make_pair(x_n, y_n));
							cluster_pt.push_back(make_pair(x_n, y_n));
						}
					}						
				}
				cluster_pts.push_back(cluster_pt);
				total_clusters++;
			}
		}
	}
	for (int i = 0; i < cluster_pts.size(); i++)
	{
		for (int j = 0; j < cluster_pts[i].size(); j++)
		{
			cout << cluster_pts[i][j].first << ',' << cluster_pts[i][j].second << endl;
		}
		cout << "\n";
	}
}

int example_main()
{
	vector<vector<int>> map{ { 1, 1, 0, 0, 0 },
							 { 1, 1, 0, 0, 1 },
							 { 1, 1, 1, 1, 1 },
							 { 1, 0, 0, 0, 0 },
							 { 1, 0, 1, 0, 1 } };
	BFS bfs;
	bfs.set_grid(map);
	bfs.bfs_doit();
	return 1;
}