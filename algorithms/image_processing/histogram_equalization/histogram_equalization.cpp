#include "histogram_equalization.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#define CVPLOT_HEADER_ONLY
#include <CvPlot/cvplot.h>

void Histogram_Equalization::process(const cv::Mat& im)
{
	/* Output image */
	cv::Mat image = im.clone();
	cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
	
	auto hist = get_hist(image);
	auto normalized_hist = normalize_hist(image, hist);
	auto cumulative_hist = get_CDF(normalized_hist);
	apply_equalization(image, cumulative_hist);
	
	/* TODO: Denormalize the histogram :)*/
	auto equalized_hist = get_hist(image);

	/* Display */
	auto axes = CvPlot::plot(hist, "-.");
	cv::Mat histDisplay = axes.render(300, 400);

	auto Naxes = CvPlot::plot(normalized_hist, "-.");
	cv::Mat NhistDisplay = Naxes.render(300, 400);
	
	auto Caxes = CvPlot::plot(cumulative_hist, "-.");
	cv::Mat ChistDisplay = Caxes.render(300, 400);

	auto Eaxes = CvPlot::plot(equalized_hist, "-.");
	cv::Mat EhistDisplay = Eaxes.render(300, 400);
	
	cv::imshow("Original Image", im);
	cv::imshow("Hist Equalized Image", image);
	cv::imshow("Original Histogram", histDisplay);
	//cv::imshow("Normalized Histogram", NhistDisplay);
	//cv::imshow("Cumulative Histogram", ChistDisplay);
	cv::imshow("Equalized Histogram", EhistDisplay);
	cv::waitKey(0);
}

std::vector<int> Histogram_Equalization::get_hist(const cv::Mat& image)
{
	/* Vector to store the histogram*/
	std::vector<int> hist;
	hist.resize(256, 0);

	/* Create the histogram */
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			auto& pixel = image.at<uchar>(i, j);
			hist[int(pixel)]++;
		}
	}
	return hist;
}

std::vector<float> Histogram_Equalization::normalize_hist(const cv::Mat& image, const std::vector<int> &hist)
{
	std::vector<float> norm_hist;
	norm_hist.resize(hist.size());

	float total_pixels = image.total();

	for (int i = 0; i < hist.size(); i++)
	{
		norm_hist[i] = hist[i] / total_pixels;
	}
	return norm_hist;
}

std::vector<float> Histogram_Equalization::get_CDF(const std::vector<float> &norm_hist)
{
	std::vector<float> cdf_hist;
	cdf_hist.resize(norm_hist.size());
	cdf_hist[0] = norm_hist[0];

	for (int i = 1; i < norm_hist.size(); i++)
	{
		cdf_hist[i] = norm_hist[i] + cdf_hist[i - 1];
	}
	return cdf_hist;
}

void Histogram_Equalization::apply_equalization(cv::Mat& image, const std::vector<float>& cumulative_hist)
{
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			image.at<uchar>(i, j) = std::floor(255 * cumulative_hist[image.at<uchar>(i, j)]) ;
		}
	}
}
