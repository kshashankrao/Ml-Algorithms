#include "best_rect_fit.h"
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
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
        auto edge_pts_major_axis = lower_higer_edge_pts_major_axis(contours[i], major_axis_angle, minor_axis_angle, centroid, image);
        
        /* Get the coordinates of the outscribed rectangle of the contour*/
        auto outscribed_pts = get_coord_outscribe_rect(edge_pts_major_axis, major_axis_angle);
             
        /* Draw rectangle line */
        cv::line(image, outscribed_pts[0], outscribed_pts[1], cv::Scalar(255, 0, 0), 3);
        cv::line(image, outscribed_pts[1], outscribed_pts[2], cv::Scalar(255, 0, 0), 3);
        cv::line(image, outscribed_pts[2], outscribed_pts[3], cv::Scalar(255, 0, 0), 3);
        cv::line(image, outscribed_pts[3], outscribed_pts[0], cv::Scalar(255, 0, 0), 3);

        /* Draw farthest points*/
        cv::circle(image, edge_pts_major_axis[0], 2, cv::Scalar(0, 0, 255), 2);
        cv::circle(image, edge_pts_major_axis[1], 2, cv::Scalar(0, 0, 255), 2);
        cv::circle(image, edge_pts_major_axis[2], 2, cv::Scalar(255, 0, 255), 2);
        cv::circle(image, edge_pts_major_axis[3], 2, cv::Scalar(255, 0, 255), 2);

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

std::vector<cv::Point> best_rect_fit::lower_higer_edge_pts_major_axis(const std::vector<cv::Point> &contour, float angle1, float angle2, cv::Point centroid)
{
    std::vector<cv::Point> edge_pts;
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
            if (perp_dist_major > major_upper_pt_max_dist)
            {
                major_upper_pt_max_dist = perp_dist_major;
                major_upper_pt = contour[i];
            }
        }
        else
        {
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
            if (perp_dist_minor > minor_upper_pt_max_dist)
            {
                minor_upper_pt_max_dist = perp_dist_minor;
                minor_upper_pt = contour[i];
            }
        }
        else
        {
            if (perp_dist_minor > minor_lower_pt_max_dist)
            {
                minor_lower_pt_max_dist = perp_dist_minor;
                minor_lower_pt = contour[i];
            }
        }
    }

    edge_pts[1] = major_upper_pt;
    edge_pts[0] = major_lower_pt;
    edge_pts[2] = minor_upper_pt;
    edge_pts[3] = minor_lower_pt;

    return edge_pts;
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

float best_rect_fit::euclidean_dist(cv::Point p1, cv::Point p2)
{
    float dist = sqrtf(powf((p2.x - p1.x), 2) + powf((p2.y - p1.y), 2));
    return dist;
}

float best_rect_fit::perp_dist_from_line_to_point(cv::Point p1, cv::Point p2, cv::Point p0)
{
    float numer = std::abs((p2.x - p1.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p1.y));
    float denom = std::sqrtf(powf((p2.x - p1.x), 2) + powf((p2.y - p1.y), 2));
    float dist = numer / denom;
    return dist;
}
