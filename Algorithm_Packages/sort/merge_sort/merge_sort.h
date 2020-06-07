#pragma once
#define N (10)

/*
Algorithm:
Divide the array into pairs (total number of pairs = n/2). Sort the pair, and merge with others. 
The approach is to merge 2 pairs in one pass.
Repeat for all the pairs
*/
int *merge_sort(int arr[], int n);
int *merge(int arr[], int start, int mid, int end);
void removenegative(int a[], int* p, int* q);


