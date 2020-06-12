#include <stdio.h> 
#include <limits.h> 
#include <cstring>
#include "dijkstra_shortest_path.h"

int minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;
	for (int v = 0; v < N; v++)
	{
		if (sptSet[v] == false && dist[v] <= min)
		{
			min = dist[v];
			min_index = v;
		}
	}
	return min_index;
}

void printPath(int parent[], int j)
{

	// Base Case : If j is source 
	if (parent[j] == -1)
		return;

	printPath(parent, parent[j]);

	printf("%d ", j);
}

void printSolution(int dist[], int n,
	int parent[])
{
	int src = 0;
	printf("Vertex\t Distance\tPath");
	for (int i = 1; i < N; i++)
	{
		printf("\n%d -> %d \t\t %d\t\t%d ",
			src, i, dist[i], src);
		printPath(parent, i);
	}
}

void dijkstra(int graph[N][N], int src)
{
	/* To store the distance of each vertice from the source*/
	int dist[N];
	/* To check if a vertice has been visited*/
	bool check_set[N];
	/* Store the path*/
	int path[N];

	for (int i = 0; i < N; i++)
	{
		memset(&dist, -1, sizeof(int));
		path[0] = -1;
		dist[i] = INT_MAX;
		check_set[i] = false;
	}

	dist[src] = 0;
	for (int count = 0; count < N - 1; count++)
	{
		int u = minDistance(dist, check_set);
		check_set[u] = true;
		for (int v = 0; v < N; v++)
		{
			if (!check_set[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
			{
				path[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}
		}
	}
	printSolution(dist, N, path);
}

int dijkstra_main()
{
	int graph[N][N] = { {0, 4, 0, 0, 0, 0, 0, 8, 0},
					    {4, 0, 8, 0, 0, 0, 0, 11, 0},
						{0, 8, 0, 7, 0, 4, 0, 0, 2},
						{0, 0, 7, 0, 9, 14, 0, 0, 0},
						{0, 0, 0, 9, 0, 10, 0, 0, 0},
						{0, 0, 4, 0, 10, 0, 2, 0, 0},
						{0, 0, 0, 14, 0, 2, 0, 1, 6},
						{8, 11, 0, 0, 0, 0, 1, 0, 7},
						{0, 0, 2, 0, 0, 0, 6, 7, 0}
	};

	dijkstra(graph, 0);
	return 0;
}