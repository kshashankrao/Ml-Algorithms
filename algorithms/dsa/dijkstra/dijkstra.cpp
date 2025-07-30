#include <opencv2/opencv.hpp>
#include <cmath>

#include "dijkstra.h"



std::vector<std::vector<std::pair<int, int>>> Dijkstra::prepare_data()
{
    std::vector<std::vector<std::pair<int, int>>> data(N);

    data[0].push_back({1, 10});
    data[0].push_back({4, 5});
    
    data[1].push_back({2, 1});
    data[1].push_back({4, 2});
    
    data[2].push_back({3, 4});
    
    data[3].push_back({0, 7});
    data[3].push_back({2, 6});
    
    data[4].push_back({1, 3});
    data[4].push_back({2, 9});
    data[4].push_back({3, 2});

    for (int u = 0; u < N; ++u) 
    {
        std::cout << "Node " << u << " -> ";
        for (auto &edge : data[u]) 
        {
            std::cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        std::cout << std::endl;
    }
    return data;
}

void Dijkstra::visualizeGraph(std::vector<std::vector<std::pair<int,int>>>& data) 
{
    int width = 800, height = 800;
    cv::Mat img = cv::Mat::zeros(height, width, CV_8UC3);
    img = cv::Scalar(255, 255, 255); // White background

    // Compute positions in a circular layout
    std::vector<cv::Point> positions(N);
    cv::Point center(width / 2, height / 2);
    int radius = std::min(width, height) / 3;

    for (int i = 0; i < N; ++i) {
        double angle = (2 * CV_PI * i) / N;
        int x = center.x + radius * cos(angle);
        int y = center.y + radius * sin(angle);
        positions[i] = cv::Point(x, y);
    }

    // Draw edges
    for (int u = 0; u < N; ++u) {
        for (auto &edge : data[u]) {
            int v = edge.first;
            int w = edge.second;

            // Draw line for edge
            line(img, positions[u], positions[v], cv::Scalar(0, 0, 0), 2);

            // Draw weight at midpoint
            cv::Point mid = (positions[u] + positions[v]) * 0.5;
            putText(img, std::to_string(w), mid, cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 0, 0), 2);
        }
    }

    // Draw nodes
    for (int i = 0; i < N; ++i) {
        circle(img, positions[i], 25, cv::Scalar(0, 0, 255), cv::FILLED);
        putText(img, std::to_string(i), positions[i] + cv::Point(-10, 10),
                cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);
    }

    // Show image
    cv::imshow("Graph Visualization", img);
    cv::waitKey(0);
}

void Dijkstra::process()
{
    // Input data structure = data[source] = [{dest, weight}, ...]
    auto data = this->prepare_data();
    visualizeGraph(data);

    // To store the distance of each node from source
    std::vector<int> distance(N, INFINITY); 
    
    // Track the parent of the nodes
    std::vector<int> parent(N, -1); 

    /*
    The data is pushed to the priority queue only when the distance between the 
    current node and dest node is lesser than the existing distance of the dest node.
    Priority queue sorts the neighboring nodes in ascending node, so the top node can 
    be popped and processed to update the next following nodes. 
    */
    std::priority_queue<std::pair<int,int>, 
                        std::vector<std::pair<int,int>>, 
                        std::greater<std::pair<int,int>>> q;

    q.push({0, 0});
    distance[0] = 0;

    while(!q.empty())
    {
        int idx = q.top().first;
        int dist = q.top().second;
        q.pop();
        
        // Get all the neighbors of the element with lowest distance
        for (auto edge : data[idx])
        {
            if( distance[idx] + edge.second < distance[edge.first])
            {
                parent[edge.first] = idx;
                distance[edge.first] = distance[idx] + edge.second;
                q.push({edge.first, distance[edge.first]});
            }
        }
    }

    std::cout << "Minimum distance from the source node" << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << "0 -> " << i << ": " << distance[i] << std::endl;
    }

    std::cout << "Shortest path from source node to all other nodes" << std::endl;
    for (int i = 0; i < N; i++)
    {
        auto node = i;
        std:: cout << i;
        while (parent[node] != -1)
        {
            std::cout << " --> " << parent[node];
            node = parent[node];
        }
        std::cout  << std::endl;
    }
}