#include "image_proc_algorithms/simple_rect_fitting/simple_rect_fitting.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <memory>

int main()
{
	simple_rect_fitting rect_fitting;
	cv::Mat image = cv::imread("D:/DeepLearning/Algorithms/Machine_Learning/data/blob.png");
	rect_fitting.process(image);
	return 0;
}