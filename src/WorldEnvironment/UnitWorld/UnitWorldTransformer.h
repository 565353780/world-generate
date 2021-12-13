#ifndef UNIT_WORLD_TRANSFORMER_H
#define UNIT_WORLD_TRANSFORMER_H

#include "export_library_global.h"

#include <iostream>
#include <limits>
#include <cmath>

class LIBRARY_EXPORT UnitWorldTransformer
{
public:
    UnitWorldTransformer()
    {
    }

    bool reset();
    bool resetImageSize();
    bool resetTransform();

    bool setImageSize(
        const size_t& image_width,
        const size_t& image_height,
        const size_t& free_area_width);

    bool expandArea(
        const float& position_x,
        const float& position_y);

    bool updateTransform();

    bool transPointToImage(
        const float& point_x_in_world,
        const float& point_y_in_world,
        size_t& point_x_in_image,
        size_t& point_y_in_image);
    bool transPointToWorld(
        const size_t& point_x_in_image,
        const size_t& point_y_in_image,
        float& point_x_in_world,
        float& point_y_in_world);

private:
    size_t image_width_;
    size_t image_height_;
    size_t free_area_width_;

    float x_min_;
    float y_min_;
    float x_max_;
    float y_max_;

    float zoom_;
    float offset_x_;
    float offset_y_;
};

#endif // UNIT_WORLD_TRANSFORMER_H
