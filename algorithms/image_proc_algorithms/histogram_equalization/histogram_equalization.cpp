#include "histogram_equalization.h"
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#define CVPLOT_HEADER_ONLY
#include <CvPlot/cvplot.h>

void Histogram_Equalization::process(cv::Mat& image)
{
	/* Vector to store the histogram*/
	std::vector<int> hist;
	hist.resize(256, 0);

	cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
	
	/* Create the histogram */
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			auto& pixel = image.at<uchar>(i, j);
			hist[int(pixel)]++;
		}
	}

	/* Display */
	auto axes = CvPlot::plot(hist, "-.");
	cv::Mat histDisplay = axes.render(300, 400);
	cv::imshow("Original Histogram", histDisplay);
	cv::waitKey(0);
}
