#pragma once

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void coutP(T s)
{
	cout << s << endl;
}
/*	Print 1d vector*/
template <typename T>
void print_1d_vector(vector<T> const& input)
{
	for (int i = 0; i < input.size(); i++) {
		cout << input.at(i) << ' ';
	}
}

/* Print 2d vector*/

template <typename T>
void print_2d_vector(vector<vector<T>> const& input)
{
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[i].size(); j++)
		{
			cout << input[i][j] << " ";
		}
		cout << "\n";
	}
}

/* Print 1d array*/

template <typename T>
void print_1d_array(T input[])
{	
	int n = sizeof(input) / sizeof(input[0]);
	for (int i = 0; i < n; i++) {
		cout << input[i] << ' ';
	}
}

