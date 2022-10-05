#include <opencv2/imgcodecs.hpp>
#include "image_processing/best_rect_fit/best_rect_fit.h"
//#include "dummy/"
int main(int argc, char** argv)
{
	best_rect_fit b;
	cv::Mat image = cv::imread("D:\DeepLearning\Algorithms\Machine_Learning\data\blob_11.png");
	b.process(image);
	return 0;
}
