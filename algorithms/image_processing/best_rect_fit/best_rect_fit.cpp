#include "best_rect_fit.h"
// #include <opencv2\imgproc.hpp>
// #include <opencv2\highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;
using pq = cv::Point;

void best_rect_fit::process(const cv::Mat& image)
{   
    auto contours = get_contour_features(image);
    filter_contour_features(image, contours);   

    for (int i = 0; i < contours.size(); i++)
    {
        auto centroid = get_centroid(contours[i]);
        float major_axis_angle = get_angle_major_axis(centroid, contours[i]);
        
        /* Calculate angle of minor axis with horizon */
        float tmp_angle = major_axis_angle;
        if (major_axis_angle > 1.57)
        {
            tmp_angle = 3.14159 - major_axis_angle;
        }

        /* Minor axis is perpendicular to major axis. */
        float minor_axis_angle = 1.57 + major_axis_angle;
        /* Get the farthest edge points from the minor and major axis*/
        auto edge_pts_major_axis = lower_higer_edge_pts_major_axis(contours[i], major_axis_angle, minor_axis_angle, centroid);
        auto &farthest_edge_pts = edge_pts_major_axis[0];
        
        /* Get the coordinates of the outscribed rectangle of the contour*/
        auto outscribed_pts = get_coord_outscribe_rect(farthest_edge_pts, major_axis_angle);
             
        /* Calculate the coefficients of least square */
        auto coeffK = calc_coeff(edge_pts_major_axis[1], edge_pts_major_axis[2], edge_pts_major_axis[3], edge_pts_major_axis[4], major_axis_angle);

        /* Calculate the coordinates of inscribed rectangle */
        auto inscribed_pts = get_coord_inscribe_rect(coeffK, major_axis_angle);

        /* Draw rectangle line */
        cv::line(image, outscribed_pts[0], outscribed_pts[1], cv::Scalar(255, 0, 0), 3);
        cv::line(image, outscribed_pts[1], outscribed_pts[2], cv::Scalar(255, 0, 0), 3);
        cv::line(image, outscribed_pts[2], outscribed_pts[3], cv::Scalar(255, 0, 0), 3);
        cv::line(image, outscribed_pts[3], outscribed_pts[0], cv::Scalar(255, 0, 0), 3);

        /* Draw rectangle line */
        cv::line(image, inscribed_pts[0], inscribed_pts[1], cv::Scalar(255, 0, 0), 3);
        cv::line(image, inscribed_pts[1], inscribed_pts[2], cv::Scalar(255, 0, 0), 3);
        cv::line(image, inscribed_pts[2], inscribed_pts[3], cv::Scalar(255, 0, 0), 3);
        cv::line(image, inscribed_pts[3], inscribed_pts[0], cv::Scalar(255, 0, 0), 3);

        /* Draw farthest points*/
        cv::circle(image, farthest_edge_pts[0], 2, cv::Scalar(0, 0, 255), 2);
        cv::circle(image, farthest_edge_pts[1], 2, cv::Scalar(0, 0, 255), 2);
        cv::circle(image, farthest_edge_pts[2], 2, cv::Scalar(255, 0, 255), 2);
        cv::circle(image, farthest_edge_pts[3], 2, cv::Scalar(255, 0, 255), 2);

        /* Draw the major axis */
        cv::Point p1;
        cv::Point p2;
        cv::Point p3;
        cv::Point p4;

        p1.x = centroid.x + (100 * cos(major_axis_angle));
        p1.y = centroid.y + (100 * sin(major_axis_angle));
        p2.x = centroid.x - (100 * cos(major_axis_angle));
        p2.y = centroid.y - (100 * sin(major_axis_angle));

        p3.x = centroid.x + (100 * cos(minor_axis_angle));
        p3.y = centroid.y + (100 * sin(minor_axis_angle));
        p4.x = centroid.x - (100 * cos(minor_axis_angle));
        p4.y = centroid.y - (100 * sin(minor_axis_angle));

        cv::line(image, p1, p2, cv::Scalar(255, 0, 0));
        cv::line(image, p3, p4, cv::Scalar(255, 0, 0));

        cv::circle(image, centroid, 2, cv::Scalar(255, 0, 0), 5);

        cv::imshow("Image", image);
        cv::waitKey(0);
        
        /* Process only one contour */
        break;
    }
}

std::vector<std::vector<cv::Point>> best_rect_fit::get_contour_features(const cv::Mat& image)
{
    Mat src_gray;
    Mat canny_output;

    cvtColor(image, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));
    Canny(src_gray, canny_output, 127, 256);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
      
    return contours;
}

void best_rect_fit::filter_contour_features(const cv::Mat& image, std::vector<std::vector<cv::Point>>& contours)
{
    float area_thresh = image.rows * image.cols / 2;
    for (int i = 0; i < contours.size(); i++)
    {
        float area = contourArea(contours[i]);
        if (area >= area_thresh)
        {
            contours.erase(contours.begin() + i);
        }
    }
}

cv::Point best_rect_fit::get_centroid(std::vector<cv::Point> contour)
{
    float mean_x = 0, mean_y = 0;

    for (int i = 0; i < contour.size(); i++)
    {
        cv::Point p = contour[i];
        mean_x += p.x;
        mean_y += p.y;
    }

    mean_x /= contour.size();
    mean_y /= contour.size();

    return cv::Point(mean_x, mean_y);
}

float best_rect_fit::get_angle_major_axis(cv::Point c, std::vector<cv::Point> contour)
{
    float numer = 0;
    float denom = 0;
    for (int i = 0; i < contour.size(); i++)
    {
        numer += (contour[i].x - c.x) * (contour[i].y - c.y);
        denom += powf((contour[i].x - c.x), 2) - powf((contour[i].y - c.y), 2);
    }

    numer = 2 * numer;
    float angle = 0.5f * atan2(numer, denom);

    return angle;
}

std::vector<std::vector<cv::Point>> best_rect_fit::lower_higer_edge_pts_major_axis(const std::vector<cv::Point> &contour, float angle1, float angle2, cv::Point centroid)
{
    std::vector<cv::Point> edge_pts;
    std::vector<cv::Point> major_upper_pts;
    std::vector<cv::Point> major_lower_pts;
    std::vector<cv::Point> minor_upper_pts;
    std::vector<cv::Point> minor_lower_pts;
    edge_pts.resize(4);

    float major_upper_pt_max_dist = 0;
    float major_lower_pt_max_dist = 0;
    float minor_upper_pt_max_dist = 0;
    float minor_lower_pt_max_dist = 0;
    
    cv::Point major_upper_pt;
    cv::Point major_lower_pt;
    cv::Point minor_upper_pt;
    cv::Point minor_lower_pt;
    
    /* Create end points of major axis and minor axis*/
    cv::Point p1(centroid.x + (100 * cos(angle1)), centroid.y + (100 * sin(angle1)));
    cv::Point p2(centroid.x - (100 * cos(angle1)), centroid.y - (100 * sin(angle1)));

    cv::Point p3(centroid.x + (100 * cos(angle2)), centroid.y + (100 * sin(angle2)));
    cv::Point p4(centroid.x - (100 * cos(angle2)), centroid.y - (100 * sin(angle2)));

    for (int i = 0; i < contour.size(); i++)
    {       
        /* Get the farthest point from major axis */
        float perp_dist_major = perp_dist_from_line_to_point(p1, p2, contour[i]);
        float f1 = (contour[i].y - centroid.y) - (tan(angle1) * (contour[i].x - centroid.x));
        if (f1 > 0)
        {
            major_upper_pts.push_back(contour[i]);
            if (perp_dist_major > major_upper_pt_max_dist)
            {
                major_upper_pt_max_dist = perp_dist_major;
                major_upper_pt = contour[i];
            }
        }
        else
        {
            major_lower_pts.push_back(contour[i]);
            if (perp_dist_major > major_lower_pt_max_dist)
            {
                major_lower_pt_max_dist = perp_dist_major;
                major_lower_pt = contour[i];
            }
        }

        /* Get the farthest point from minor axis */
        float perp_dist_minor = perp_dist_from_line_to_point(p3, p4, contour[i]);
        float cotTheta = cos(angle1) / sin(angle1);
        float f2 = (contour[i].y - centroid.y) + (cotTheta * (contour[i].x - centroid.x));
        if (f2 > 0)
        {
            minor_upper_pts.push_back(contour[i]);
            if (perp_dist_minor > minor_upper_pt_max_dist)
            {
                minor_upper_pt_max_dist = perp_dist_minor;
                minor_upper_pt = contour[i];
            }
        }
        else
        {
            minor_lower_pts.push_back(contour[i]);
            if (perp_dist_minor > minor_lower_pt_max_dist)
            {
                minor_lower_pt_max_dist = perp_dist_minor;
                minor_lower_pt = contour[i];
            }
        }
    }

    /* Create an output vector and dump all the values */

    std::vector<std::vector<cv::Point>> o;
    o.resize(5);
    
    edge_pts[1] = major_upper_pt;
    edge_pts[0] = major_lower_pt;
    edge_pts[2] = minor_upper_pt;
    edge_pts[3] = minor_lower_pt;
    
    o[0] = edge_pts;
    o[1] = major_upper_pts;
    o[2] = major_lower_pts;
    o[3] = minor_upper_pts;
    o[4] = minor_lower_pts;

    return o;
}

std::vector<cv::Point> best_rect_fit::get_coord_outscribe_rect(std::vector<cv::Point> e, float angle)
{
    std::vector<cv::Point> pts;
    pts.resize(4);

    cv::Point p1;
    cv::Point p2;
    cv::Point p3;
    cv::Point p4;

    float tanTheta = tan(angle);
    float cotTheta = cos(angle) / sin(angle);
    
    
    /* Top left */
    p1.x = (e[1].x * tanTheta + e[2].x * cotTheta + e[2].y - e[1].y) / (tanTheta + cotTheta);
    p1.y = (e[1].y * cotTheta + e[2].y * tanTheta + e[2].x - e[1].x) / (tanTheta + cotTheta);

    /* Top right */
    p2.x = (e[1].x * tanTheta + e[3].x * cotTheta + e[3].y - e[1].y) / (tanTheta + cotTheta);
    p2.y = (e[1].y * cotTheta + e[3].y * tanTheta + e[3].x - e[1].x) / (tanTheta + cotTheta);

    /* Bottom Left */
    p3.x = (e[0].x * tanTheta + e[2].x * cotTheta + e[2].y - e[0].y) / (tanTheta + cotTheta);
    p3.y = (e[0].y * cotTheta + e[2].y * tanTheta + e[2].x - e[0].x) / (tanTheta + cotTheta);
    
    /* Bottom right */
    p4.x = (e[0].x * tanTheta + e[3].x * cotTheta + e[3].y - e[0].y) / (tanTheta + cotTheta);
    p4.y = (e[0].y * cotTheta + e[3].y * tanTheta + e[3].x - e[0].x) / (tanTheta + cotTheta);

    pts = { p1, p2, p4, p3};

    return pts;
}

std::vector<cv::Point> best_rect_fit::get_coord_inscribe_rect(std::vector<float> k, float angle)
{
    std::vector<cv::Point> pts;
    pts.resize(4);

    cv::Point p1;
    cv::Point p2;
    cv::Point p3;
    cv::Point p4;

    float m = tan(angle);

    /* Top left */
    p1.x = (m * k[0] - k[2]) / (1 + powf(m, 2));
    p1.y = -(k[0] + m * k[2]) / (1 + powf(m, 2));

    /* Top right */
    p2.x = (m * k[0] - k[3]) / (1 + powf(m, 2));
    p2.y = -(k[0] + m * k[3]) / (1 + powf(m, 2));
    
    /* Bottom left */
    p3.x = (m * k[1] - k[2]) / (1 + powf(m, 2));
    p3.y = -(k[1] + m * k[2]) / (1 + powf(m, 2));
    
    /* Bottom Right */
    p4.x = (m * k[1] - k[3]) / (1 + powf(m, 2));
    p4.y = -(k[1] + m * k[3]) / (1 + powf(m, 2));

    return {p1, p2, p4, p3};
}

float best_rect_fit::euclidean_dist(cv::Point p1, cv::Point p2)
{
    float dist = sqrtf(powf((p2.x - p1.x), 2) + powf((p2.y - p1.y), 2));
    return dist;
}

std::vector<float> best_rect_fit::calc_coeff(std::vector<cv::Point> s1, std::vector<cv::Point> s2, std::vector<cv::Point> s3, std::vector<cv::Point> s4, float angle)
{
    float k1, k2, k3, k4;
    float m = tan(angle);

    auto sum1 = sum_contour(s1);
    k1 = (m * sum1.x - sum1.y) / s1.size();
    
    auto sum2 = sum_contour(s2);
    k2 = (m * sum2.x - sum2.y) / s2.size();
    
    auto sum3 = sum_contour(s4);
    k3 = -(sum3.x + m * sum3.y) / (s3.size());

    auto sum4 = sum_contour(s3);
    k4 = -(sum4.x + m * sum4.y) / (s4.size());

    return {k1, k2, k3, k4};
}

float best_rect_fit::perp_dist_from_line_to_point(cv::Point p1, cv::Point p2, cv::Point p0)
{
    float numer = std::abs((p2.x - p1.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p1.y));
    float denom = std::sqrt(powf((p2.x - p1.x), 2) + powf((p2.y - p1.y), 2));
    float dist = numer / denom;
    return dist;
}

cv::Point best_rect_fit::sum_contour(std::vector<cv::Point> v)
{
    float sum_x = 0;
    float sum_y = 0;

    for (int i = 0; i < v.size(); i++)
    {
        sum_x += v[i].x;
        sum_y += v[i].y;
    }

    return cv::Point(sum_x, sum_y);
}
