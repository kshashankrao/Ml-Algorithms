#include "linear_regression.h"
#include "csv_reader/csv_reader.h"
#include <iostream>
#include "print_function/print_function.h"
#include <vector>
#include <assert.h> 
#include <cassert>
#include <fstream>
#include <sstream>

using namespace std;

void linear_regression::fit()
{
	linear_regression::get_data();
	
	if (this->x_data.size() != this->y_data.size())
	{
		throw "Length of Data in CSV is wrong";
	}
	this->N = x_data.size(); /* Length of data size*/
	linear_regression::train();
	linear_regression::save_model("model.txt");
}

void linear_regression::get_data()
{
	CSVReader reader(csv_filename);
	vector<vector<string>> dataList = reader.getData();
	
	for (vector<string> vec : dataList)
	{
		for(int i = 0; i < vec.size(); i++)
		{
			float val = stof(vec[i]);
			if (i == vec.size() - 1)
			{	
				this->y_data.push_back(val);
			}
			else
			{
				this->x_data.push_back(val);
			}
		}
	}
}
void linear_regression::train()
{
	float mse = 0;

	for (int i = 0; i < this->iter + 1; i++)
	{
		gradient_descent(&this->w, &this->b, &mse);
		if (i % 5 == 0)
		{
			cout << "Iter: " << i << " weight: " << w << " bias: " << b << " Error: " << mse << endl;
		} 
	}
}
void linear_regression::gradient_descent(float *weight, float *bias, float *mse)
{
	float error = 0;
	float y_pred = 0;
	float weight_derivative = 0;
	float bias_derivative = 0;
	
	/* Calculate the partial derivative of weight and bias*/
	for (int i = 0; i < this->N; i++)
	{
		weight_derivative += (-2 * this->x_data[i]) * (this->y_data[i] - (*weight * this->x_data[i] + *bias));
		bias_derivative += -2 * (this->y_data[i] - (*weight * this->x_data[i] + *bias));
	}

	/* Update the weights*/
	*weight -= (weight_derivative / this->N) * learning_rate;
	*bias -= (bias_derivative / this->N) * learning_rate;

	/* Cost function is MSE*/
	for (int i = 0; i < this->N; i++)
	{
		y_pred = *weight * this->x_data[i] +*bias;
		error += (this->y_data[i] - y_pred);
		//cout << "y_pred: " << error << endl;
		//cout << "y: " << y_data[i]<< endl;
	}
	*mse = error / this->N;
}

void linear_regression::predict(float input_data)
{
	float pred;
	linear_regression::load_model("model.txt");
	pred = this->w * input_data + this->b;
	cout << pred;
}

void linear_regression::save_model(string file_name)
{
	std::ofstream file;
	file.open(file_name);
	if (!file.is_open()) throw "Model cannot be saved because file cannot be opened to write.Check for permissions and make sure the file is not open!";
	file << this->w << "," << this->b;
	file.close();
}

void linear_regression::load_model(string filename)
{
	std::ifstream file;
	file.open(filename);
	if (!file.is_open()) throw "Model cannot be opened!";
	std::stringstream stream;
	stream << file.rdbuf();
	std::string values = stream.str();
	unsigned int index = values.find(",");
	std::string _w = "";
	std::string _b = "";
	for (unsigned int i = 0; i < index; i++)
	{
		_w += values[i];
	}
	for (unsigned int i = index + 1; i < values.size(); i++)
	{
		_b += values[i];
	}
	this->w = stod(_w);
	this->b = stod(_b);
}
