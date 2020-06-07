#include "merge_sort.h"
#include <iostream>
#include "print_function.h"
#include<vector>
using namespace std;

int* merge_sort(int arr[], int n)
{
	static int tmp[N];
	vector<int> pos;
	/* Pointers to remove negative values*/
	int* s_ptr, * e_ptr;
	s_ptr = tmp;
	e_ptr = tmp + N - 1;

	memset(tmp, -1, sizeof(int) * N);
	memcpy(tmp, arr, sizeof(int) * n);

	int start;
	int end;
	int mid;

	int* sorted;

	for (int i = 1; i < N - 1; i = 2 * i)
	{
		for (int j = 0; j < N - 1; j += 2 * i)
		{
			start = j;
			end = (start + 2 * i) - 1;
			if (end > (n - 1))
			{
				end = n;
			}
			mid = (start + end) / 2;
			sorted = merge(tmp, start, mid, end);
			memcpy(tmp, sorted, sizeof(int) * N);
		}

	}
	removenegative(tmp, s_ptr, e_ptr);

	return tmp;
}

int* merge(int arr[], int start, int mid, int end)
{
	static int merged[N];
	memset(merged, -1, sizeof(int) * N);
	memcpy(merged, arr, sizeof(int) * N);
	
	int i = start;
	int j = mid + 1;
	int k = start;
	int end1, end2;

	while (i <= mid && j <= end)
	{
		if (*(arr + i) <= *(arr + j))
		{
			merged[k] = *(arr + i);
			i++;
		}
		else
		{
			merged[k] = *(arr + j);
			j++;
		}
		k++;
	}

	while (i <= mid)
	{
		merged[k] = *(arr + i);
		i++;
		k++;
	}

	while (j <= end)
	{
		merged[k] = *(arr + j);
		j++;
		k++;
	}
	
	return merged;
}

void removenegative(int a[], int* p, int* q)
{
	int* x;
	x = &a[0];
	while (p <= q)
	{
		if (*p >= 0)
		{
			*x = *p;
			x++;
		}
		p++;
	}
	for (; x <= q; x++)
	{
		*x = -1;
	}
}