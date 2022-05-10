//#pragma once
//#include<string>
//#include<vector>
//using namespace std;
//class linear_regression
//{
//private:
//	unsigned int N = 0;
//	int iter = 0;
//	float w;
//	float b;
//	vector<float> y_data = {}; 
//	vector<float> x_data = {};
//	string csv_filename;
//	float learning_rate;
//
//public:
//
//	linear_regression(string filename, int iterations, float lr, float weight_initial, float bias_intial)
//	{
//		csv_filename = filename;
//		iter = iterations;
//		learning_rate = lr;
//		w = weight_initial;
//		b = bias_intial;
//	}
//	void fit();
//	void get_data();
//	void train();
//	void gradient_descent(float *weight, float *bias, float *mse);
//	void predict(float input_data);
//	void save_model(string file_name);
//	void load_model(string filename);
//
//};