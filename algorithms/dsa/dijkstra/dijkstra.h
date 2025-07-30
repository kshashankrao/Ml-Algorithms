/*
Algorithm explaination:

The algorithm is used to find the shortest path between 2 nodes in a graph with weighted edges.
The algorithm starts from the source node and explores all the neighboring  nodes. 
For each node, the shortest distance to the neighbor node is updated if the current distance is less than previous 
distance. 

*/
#include <bits/stdc++.h>
#include <queue>

class Dijkstra
{   
    private:
        int N;

    public:
        Dijkstra()
        {
            N = 5;
        }

        void process();
        std::vector<std::vector<std::pair<int, int>>> prepare_data();
        void visualizeGraph(std::vector<std::vector<std::pair<int,int>>>& data);
        void printPath(int node, std::vector<int>& parent);
};

