#include <iostream>
#include "bubble_sort.h"
using namespace std;

void bubble_sort(int *arr, int n, bool ascending)
{
	// Take pair of number, compare the largest and push to last. Repeat till there is no swapping.
	for (int i = 0; i < n - 1; i++)
	{
		bool is_swapped = false;
		
		// The largest number in one pass will pushed to the last index, and can be ignored in the next pass.
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (ascending == true)
			{
				is_swapped = swap_num((arr + j), (arr + j+ 1));
			}

			else
			{
				is_swapped = swap_num(&arr[j + 1], &arr[j]);
			}
		}
		
		if (is_swapped == false)
		{
			break;
		}
	}
}

bool swap_num(int* x, int* y)
{
	int tmp;
	if (*x > *y)
	{
		tmp = *x;
		*x = *y;
		*y = tmp;
		return true;
	}
	return false;
}

void bubble_sort_main()
{
	int arr[] = { 0, 7, 1,6 };
	int* ptr = arr;
	int l = sizeof(arr) / sizeof(arr)[0];
	bubble_sort(ptr, l, false);
}