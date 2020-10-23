#include <vector>

struct Edge
{
	int src;
	int dest;
	int weight;
};

struct GraphStruct
{
	int num_vertices;
	int num_edges;
	std::vector<Edge> edge;

	GraphStruct(int V, int E):
		num_vertices(V), 
		num_edges(E)
	{
		edge.resize(E);
	}
};

class minimum_spanning_tree
{
public:

	/* Brief: Main function to initiate the calculation of minimum spanning tree
	   Input: Graph structure with edges, vertices and weights
	   Output: Returns edges that is part of minimum spanning tree*/
	std::vector<Edge> run(const GraphStruct &graph);


private:

	std::vector<Edge> get_cyclic(const GraphStruct& graph);

	/* Brief: Functions to perform Union find algo*/
	int findSubSet(const std::vector<int>& s, int i);
	void unionSubSet(std::vector<int>& s, int x, int y);

	/* Brief: Perform quick sort of edges based on the weights*/
	GraphStruct sortSubSet(const GraphStruct& graphSort);	
};