#include <iostream>
#include "quick_sort.h"
#include "sort/bubble_sort/bubble_sort.h" // To use swap

int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++)
    {  
        if (arr[j] < pivot)
        {
            i++;   
            swap_num(&arr[i], &arr[j]);
        }
    }
    swap_num(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int new_pivot = partition(arr, low, high);

        quick_sort(arr, low, new_pivot - 1);
        quick_sort(arr, new_pivot + 1, high);
    }
}

int quicksort_main()
{
    // Maximum of 10 numbers
    int arr[] = { 51,46,56,20,1 };
    int* ptr;
    int l = sizeof(arr) / sizeof(arr)[0];
    quick_sort(arr, 0, l - 1);
    for (int i = 0; i < l; i++)
    {
        std::cout << arr[i] << std::endl;
    }
    return 0;
}

