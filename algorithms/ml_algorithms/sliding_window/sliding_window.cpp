#include "sliding_window.h"
#include <iostream>

void sliding_window::sliding_window_1d(int arr[], int n, int window_size, int stride)
{
	for (int i = 0; i < (n - window_size +  1); i = i + stride)
	{
		for (int j = 0; j < window_size; j++)
		{
			std::cout << arr[i  + j];
		}
		std::cout << std::endl;
	}
}

void sliding_window::sliding_window_2d(std::vector<std::vector<int>> arr, int window_size, int stride)
{
	for (int i = 0; i < (arr.size() - window_size + 1); i = i + stride)
	{
		for (int j = 0; j < (arr[0].size() - window_size + 1); j = j + stride)
		{
			for (int idx = 0; idx < window_size; idx++)
			{
				for (int idy = 0; idy < window_size; idy++)
				{
					int ix = i + idx;
					int jy = j + idy;
					std::cout << arr[ix][jy];
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;

		}
	}
}

