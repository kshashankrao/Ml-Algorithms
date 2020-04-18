#include "linear_regression/linear_regression.h"
#include<vector>
#include<string>
#include <iostream>


using namespace std;
int main()
{
	bool is_train = false;
	linear_regression lr("a.csv", 50, 0.0001, 0, 0);
	if (is_train == true)
	{
		lr.fit();
	}

	else
	{
		string input;
		float input_float;
		while (getline(std::cin, input) && input != "quit")
		{
			input_float = stof(input);
			lr.predict(input_float);
		}
	}
	
	
}