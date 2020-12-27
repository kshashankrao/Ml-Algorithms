#include <opencv2/core.hpp>
#include <vector>

class Histogram_Equalization
{
public:
	/*
	* Brief: Main function to trigger
	* Input: Image
	* Output: Displays intensity equalized image
	*/
	void process(const cv::Mat& im);

private:
	/*
	* Brief: Computes the histogram based on the intensity of the grayscale image
	* Input: Image
	* Output: Vector of Histogram
	*/
	std::vector<int> get_hist(const cv::Mat& image);

	/*
	* Brief: Calculates the normalized histogram
	* Input: Image, histogra
	* Output: Vector of normalized hist
	*/
	std::vector<float> normalize_hist(const cv::Mat& image, const std::vector<int> &hist);

	/*
	* Brief: Computes the cdf of the histogram
	* Input: Normalized histogram
	* Output: Vector of cdf
	*/
	std::vector<float> get_CDF(const std::vector<float> &norm_hist);
	
	/*
	* Brief: Replaces the image pixels with newly calculated values
	* Input: Image, cdf histogram
	*/
	void apply_equalization(cv::Mat &image, const std::vector<float>& cumulative_hist);
};