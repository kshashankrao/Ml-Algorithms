#include <opencv2/core.hpp>
#include <vector>

class best_rect_fit
{
public:
	/*
	* Brief: Main function to process the rectangle fitting
	* Input: Image
	* Output: Displays image with overlays
	*/
	void process(const cv::Mat& image);

private:
	/*
	* Brief: Find all the contours in a given image
	* Input: Image
	* Output: Vector of contours
	*/
	std::vector<std::vector<cv::Point>> get_contour_features(const cv::Mat& image);
	
	/*
	* Brief: Remove very large contours
	* Input: Image, vector of contours
	*/
	void filter_contour_features(const cv::Mat& image, std::vector<std::vector<cv::Point>>& contours);
	
	/*
	* Brief: Calculate the centroid of the contour
	* Input: Contour
	* Output: Centroid of the contour
	*/
	cv::Point get_centroid(std::vector<cv::Point> contour);

	/*
	* Brief: Calculates the angle of major axis at x axis
	* Input: Centroid, contour
	* Output: Angle 
	*/
	float get_angle_major_axis(cv::Point c, std::vector<cv::Point> contour);
	
	/*
	* Brief: Find the points farthest from major and minor axis
	* Input: Contour points, major axis angle, minor axis angle, centroid point
	* Output: Vector containing the four points
	*/
	std::vector<std::vector<cv::Point>> lower_higer_edge_pts_major_axis(const std::vector<cv::Point> &contour, float angle1, float angle2, cv::Point centroid);
	
	/*
	* Brief: Calculate the coordinates of the outscribed rectangle
	* Input: Farthest points from major and minor axis, major axis angle
	* Output: Rectangle coordinates
	*/
	std::vector<cv::Point> get_coord_outscribe_rect(std::vector<cv::Point> e, float angle);
	
	/*
	* Brief: Calculate the coordinates of the inscribed rectangle
	* Input: 4 coefficients of least square equation, major axis angle
	* Output: Rectangle coordinates
	*/
	std::vector<cv::Point> get_coord_inscribe_rect(std::vector<float> k, float angle);
	/*
	* Brief: Calculate the euclidean distance
	* Input: Point 1, Poin 2
	* Output: Distance between 2 points
	*/
	float euclidean_dist(cv::Point p1, cv::Point p2);

	/*
	* Brief: Calculate the coefficients of the least square equation
	* Input: 4 vectors containing the points
	* Output: Vector of coeff
	*/
	std::vector<float> calc_coeff(std::vector<cv::Point> s1, std::vector<cv::Point> s2, std::vector<cv::Point> s3, std::vector<cv::Point> s4, float angle);
	
	/*
	* Brief: Calculates the perpendicular distance between the line and a given point
	* Input: The two end coordinates of line, point from which distance is to be found
	* Output: Perpendicular distance
	*/
	float perp_dist_from_line_to_point(cv::Point p1, cv::Point p2, cv::Point p0);

	/*
	* Brief: Calculate the sum of points
	* Input: Vector of points
	* Output: Value of sum
	*/
	cv::Point sum_contour(std::vector<cv::Point> v);
};	