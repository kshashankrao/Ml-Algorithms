#include "minimum_spanning_tree.h"
#include <assert.h> 
#include <iostream>

std::vector<Edge> minimum_spanning_tree::run(const GraphStruct &graph)
{
	GraphStruct sortedGraph = sortSubSet(graph);
	auto edges = get_cyclic(sortedGraph);

	return edges;
}

std::vector<Edge> minimum_spanning_tree::get_cyclic(const GraphStruct &graph)
{
	assert(graph.edge.size() == graph.num_edges);

	std::vector<int> subSet;
	subSet.resize(graph.num_vertices, -1);
	std::vector<Edge> res;

	for (int i = 0; i < graph.num_edges; i++)
	{
		int x1 = findSubSet(subSet, graph.edge[i].src);
		int x2 = findSubSet(subSet, graph.edge[i].dest);
	
		if (x1 != x2)
		{
			res.push_back(graph.edge[i]);
			unionSubSet(subSet, x1, x2);
		}
	}

	return res;
}

int minimum_spanning_tree::findSubSet(const std::vector<int> &s, int i)
{
	if (s[i] == -1)
	{
		return i;
	}

	return findSubSet(s, s[i]);
}

void minimum_spanning_tree::unionSubSet(std::vector<int>& s, int x, int y)
{
	int a = findSubSet(s, x);
	int b = findSubSet(s, y);

	if (a != b)
	{
		s[a] = b;
	}
}

GraphStruct minimum_spanning_tree::sortSubSet(const GraphStruct& graphSort)
{
	GraphStruct gOut = graphSort;
	int n = graphSort.edge.size();
	for (int i = 0; i < n - 1; i++)
	{
		bool is_done = false;
		for (int j = 0; j < n - 1 - i; j++)
		{
			int tmpW, tmpS, tmpD;
			int j1 = j + 1;
			if (gOut.edge[j].weight > gOut.edge[j1].weight)
			{
				tmpW = gOut.edge[j].weight;
				gOut.edge[j].weight = gOut.edge[j1].weight;
				gOut.edge[j1].weight = tmpW;

				tmpS = gOut.edge[j].src;
				gOut.edge[j].src = gOut.edge[j1].src;
				gOut.edge[j1].src = tmpS;

				tmpD = gOut.edge[j].dest;
				gOut.edge[j].dest = gOut.edge[j1].dest;
				gOut.edge[j1].dest= tmpD;
				is_done = true;
			}
			else
			{
				is_done = false;
			}
		}

		if (is_done == false)
		{
			break;
		}
	}
	return gOut;
}
