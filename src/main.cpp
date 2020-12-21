#include "image_proc_algorithms/best_rect_fit/best_rect_fit.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <memory>

int main()
{
	best_rect_fit b;
	cv::Mat image = cv::imread("D:\\DeepLearning\\Algorithms\\Machine_Learning\\data\\blob.png");
	b.process(image);
	return 0;
}
