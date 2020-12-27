#include <opencv2/core.hpp>
#include <vector>

class Histogram_Equalization
{
public:
	void process(const cv::Mat& im);
private:
	std::vector<int> get_hist(const cv::Mat& image);
	std::vector<float> normalize_hist(const cv::Mat& image, const std::vector<int> &hist);
	std::vector<float> get_CDF(const std::vector<float> &norm_hist);
	void apply_equalization(cv::Mat &image, const std::vector<float>& cumulative_hist);
};