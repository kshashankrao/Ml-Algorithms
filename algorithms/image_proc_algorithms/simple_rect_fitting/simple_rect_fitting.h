#include <opencv2/core.hpp>
#include <vector>

class simple_rect_fitting
{
public:

	enum rect_fit_type
	{
		ALL,
		LARGEST
	};

	struct rect
	{
		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		int y2 = 0;
		int w = 0;
		int h = 0;

		int get_width()
		{
			w = x2 - x1;
			return w;
		}

		int get_height()
		{
			h = y2 - y1;
			return h;
		}

		int area()
		{
			get_height();
			get_width();
			return h * w;
		}
	};

	simple_rect_fitting()
	{

	}

	void process (cv::Mat &image);

private:

	std::vector<rect> fit(const cv::Mat &image, rect_fit_type t);
	std::vector<rect> get_all_rects(const cv::Mat& image);
	void findx2y2(const cv::Mat& image, rect& rectCoord, std::vector<bool>& visited);
	std::vector<rect> get_largest_rect(const cv::Mat& image);

	


};