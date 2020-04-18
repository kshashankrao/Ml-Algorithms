#pragma once

#include <iostream>
#include <vector>

using namespace std;

/*	Print 1d int vector
	input = {}*/
void print_int_1d(vector<int> const& input)
{
	for (int i = 0; i < input.size(); i++) {
		cout << input.at(i) << ' ';
	}
}

/*	Print 1d float vector
	input = {}*/
void print_float_1d(vector<float> const& input)
{
	for (int i = 0; i < input.size(); i++) {
		cout << input.at(i) << ' ';
	}
}

/*	Print 2d float vector
	input = {}*/
void print_float_2d(vector<vector<float>> const& input)
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


