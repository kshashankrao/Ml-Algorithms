#pragma once
#define N (5)

void merge(int* arr, int start, int end, int mid, int *sorted);

/*
Algorithm:
Divide the array into pairs (total number of pairs = n/2). Sort the pair, and merge with others. 
The approach is to merge 2 pairs in one pass.
Repeat for all the pairs
*/
void merge_sort(int* arr, bool ascending, int n);