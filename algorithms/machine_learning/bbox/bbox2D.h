#ifndef BBOX2D_H
#define BBOX2D_H

#include <vector>
#include <algorithm>

struct Bbox2D
{
    float x_min;
    float y_min;
    float x_max;
    float y_max;
    float confidence;

    inline float area() const
    {
        float w = x_max - x_min;
        float h = y_max - y_min;
        if (w <= 0 || h <= 0) return 0.0f;
        return w * h;
    }
};

class Bbox2DUtils
{
    public:
        static float iou(const Bbox2D &box1, const Bbox2D &box2);
        static std::vector<Bbox2D> non_max_suppression(const std::vector<Bbox2D> &bboxes, float iou_threshold);
};

#endif // BBOX2D_H