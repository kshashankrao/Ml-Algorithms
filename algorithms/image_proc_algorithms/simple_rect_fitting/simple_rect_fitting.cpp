#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "simple_rect_fitting.h"
#include <vector>
#include <iostream>

void simple_rect_fitting::process(cv::Mat &image)
{
    cv::resize(image, image, cv::Size(360, 480));
    cv::Mat orig = image.clone();
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::threshold(image, image, 128, 255, cv::THRESH_BINARY);
    std::vector<rect> coords = fit(image);
    cv::cvtColor(image, image, cv::COLOR_GRAY2BGR);

    std::cout << coords.size();
    for (int i = 0; i < coords.size(); i++)
    {
        cv::Rect rec(cv::Point(coords[i].x1, coords[i].y1), cv::Point(coords[i].x2, coords[i].y2));
        cv::rectangle(image, rec, cv::Scalar(0, 255, 0), 2);
    }
    cv::imshow("orig", orig);
    cv::imshow("Image", image);
    cv::waitKey(0);
 }

std::vector<simple_rect_fitting::rect> simple_rect_fitting::fit(const cv::Mat& image)
{
    /* Algorithm
       1. The first detected white pixel will be x1,y1.
       2. Traverse along row until black pixel is found -> y2
       3. Traverse along col until black pixel is found -> x2 */
    std::vector<bool> visited;
    visited.resize(image.rows * image.cols);
    std::vector<rect> rectCoords;

    int rectIndex = 0;
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            uchar p = image.at<uchar>(i, j);
            if ((p > 127) && (visited[image.cols * i + j] == false))
            {
                rect rectCoord; 
                rectCoord.x1 = j;
                rectCoord.y1 = i;
                findx2y2(image, rectCoord, visited);
                if ((rectCoord.get_height() > 200) && (rectCoord.get_width() > 50))
                {
                    rectCoords.push_back(rectCoord);
                }
                
            }
        }
    }
    return rectCoords;
}

void simple_rect_fitting::findx2y2(const cv::Mat& image, rect &rectCoord, std::vector<bool>& visited)
{
    for (int i = rectCoord.y1; i < image.rows; i++)
    {
        if (image.at<uchar>(i, rectCoord.x1) < 127)
        {
            rectCoord.y2 = i;
            break;
        }

        for (int j = rectCoord.x1; j < image.cols; j++)
        {
            if (image.at<uchar>(rectCoord.y1, j) < 127)
            {
                rectCoord.x2 = j;
                break;
            }
            visited[image.cols * i + j] = true;
        }
    }
}
