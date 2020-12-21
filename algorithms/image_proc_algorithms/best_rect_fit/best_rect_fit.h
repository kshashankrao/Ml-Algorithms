#include <opencv2/core.hpp>
#include <vector>

class best_rect_fit
{
public:
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

	void process(const cv::Mat& image);
private:
	std::vector<std::vector<cv::Point>> get_contour_features(const cv::Mat& image);
	void filter_contour_features(const cv::Mat& image, std::vector<std::vector<cv::Point>>& contours);
	cv::Point get_centroid(std::vector<cv::Point> contour);
	float get_angle_major_axis(cv::Point c, std::vector<cv::Point> contour);
	std::vector<cv::Point> lower_higer_edge_pts_major_axis(const std::vector<cv::Point> &contour, float angle1, float angle2, cv::Point centroid, const cv::Mat& image);
	std::vector<cv::Point> get_coord_outscribe_rect(std::vector<cv::Point> e, float angle);
	float euclidean_dist(cv::Point p1, cv::Point p2);
	float perp_dist_from_line_to_point(cv::Point p1, cv::Point p2, cv::Point p0);

};	