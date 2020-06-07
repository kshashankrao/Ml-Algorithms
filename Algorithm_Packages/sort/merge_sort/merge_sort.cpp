#include "merge_sort.h"
#include <iostream>

using namespace std;
void merge_sort(int *arr, bool ascending, int n )
{
	int sorted[N];
	int start, end, mid;
	// Initialize the total number of groups 
	for (int i = 1; i < n - 1; i = 2 * i)
	{
		// Split the array into groups
		for (int j = 0; j < n - 1; j += 2 * i)
		{
			start = j;
			end = (j + 2 * i) - 1;
			mid = ((start + end) / 2);
			merge(arr, start, end, mid, sorted);
		}
		// Copy the sorted array to original for next iteration
		memcpy(arr, sorted, sizeof(int) * n);
	}
}

void merge(int* arr, int start1, int end2, int end1, int *sorted)
{
	int start2 = end1 + 1;
	int i = start1;
	int j = start2;
	int k = start1;


	while (i <= end1 && j <= end2)
	{	
		int num1 = *(arr + i);
		int num2 = *(arr + j);
		if (*(arr + i) <= *(arr + j))
		{
			*(sorted + k) = *(arr + i);
			i++;
		}
		else
		{
			*(sorted + k) = *(arr + j);
			j++;
		}
		k++;
	}

	while (i <= end1)
	{
		*(sorted + k) = *(arr + i);
		i++;
		k++;
	}

	while (j <= end2)
	{
		*(sorted + k) = *(arr + j);
		j++;
		k++;
	}
}
