# Algorithm

<img src="dijkstra_wiki.gif" width="250" height="200" />

The algorithm starts from the source node and updates the distance (weights) from the source to destination node if (source_node + weight < dest_node). The next neighbor node to be processed is the node with the least distance. A priority queue is used to sort the nodes in descending order of the distance. 

The process repeats untill all the nodes are visited. To keep the track of the path, the parent node of the current node ((i.e prev node of the current node)) is stored.