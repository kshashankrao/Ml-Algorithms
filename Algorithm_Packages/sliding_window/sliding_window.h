#pragma once
#include <vector>
class sliding_window
{
public:
	void sliding_window_1d(int arr[], int n, int window_size, int stride);
	void sliding_window_2d(std::vector < std::vector<int>> arr, int window_size, int stride);
};