#include "bbox2D.h"
#include <algorithm>

float Bbox2DUtils::iou(const Bbox2D &box1, const Bbox2D &box2)
{
    float inter_x1 = std::max(box1.x_min, box2.x_min);
    float inter_y1 = std::max(box1.y_min, box2.y_min);
    float inter_x2 = std::min(box1.x_max, box2.x_max);
    float inter_y2 = std::min(box1.y_max, box2.y_max);

    float inter_w = std::max(0.0f, inter_x2 - inter_x1);
    float inter_h = std::max(0.0f, inter_y2 - inter_y1);

    float intersection_area = inter_w * inter_h;
    if (intersection_area <= 0) return 0.0f;

    float union_area = box1.area() + box2.area() - intersection_area;
    return (union_area > 0) ? (intersection_area / union_area) : 0.0f;
}

std::vector<Bbox2D> Bbox2DUtils::non_max_suppression(const std::vector<Bbox2D> &bboxes, float iou_threshold)
{
    if (bboxes.empty()) return {};

    std::vector<bool> removed(bboxes.size(), false);    
    std::vector<Bbox2D> keep;
    keep.reserve(bboxes.size());
    auto bboxes_ = bboxes;
    
    std::sort(bboxes_.begin(), bboxes_.end(), [](const Bbox2D &a, const Bbox2D &b) {
        return a.confidence > b.confidence;
    });

    for(size_t i = 0; i < bboxes_.size(); ++i)
    {
        if (removed[i])
        {
            continue;
        }

        keep.push_back(bboxes_[i]);
        
        for(size_t j = i + 1; j < bboxes_.size(); ++j)
        {
            if (removed[j])
            {
                continue;
            }

            if(iou(bboxes_[i], bboxes_[j]) > iou_threshold)
            {
                removed[j] = true;
            }
        }
    }

    return keep;
}