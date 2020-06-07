#include "shell_sort.h"
#include <iostream>

using namespace std;

void shell_sort(int arr[], int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2) 
	{
		for (int i = gap; i < n; i += 1) 
		{
			int temp = arr[i];
			int j = 0;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
			{
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}

int shellsort_main()
{
	// Maximum of 10 numbers
	int arr[] = { 51,46,56,20,1 };
	int* ptr;
	int l = sizeof(arr) / sizeof(arr)[0];
	shell_sort(arr, l);
	for (int i = 0; i < l; i++)
	{
		cout << arr[i] << endl;
	}
}