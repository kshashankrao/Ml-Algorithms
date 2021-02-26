#include "image_proc_algorithms/best_rect_fit/best_rect_fit.h"
#include <opencv2/imgcodecs.hpp>

int main(int argc, char** argv)
{
	best_rect_fit b;
	cv::Mat image = cv::imread(argv[1]);
	b.process(image);
	return 0;
}
