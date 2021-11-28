#ifndef EASY_POLYGON_POINT_H
#define EASY_POLYGON_POINT_H

#include "export_library_global.h"

#include "EasyPolygon2D.h"
#include "EasyComputation.h"

class LIBRARY_EXPORT EasyPolygonPoint2D
{
public:
    EasyPolygonPoint2D()
    {
        is_valid = false;
    }

    bool reset();

    bool updateByPolygonParam(
        const EasyPolygon2D& polygon,
        const float& point_param_on_polygon);

    bool updateByLineParam(
        const EasyPolygon2D& polygon,
        const size_t& point_line_idx,
        const float& point_param_on_line);

    bool updateByLength(
        const EasyPolygon2D& polygon,
        const float& point_length);

    bool updateByPosition(
        const EasyPolygon2D& polygon,
        const EasyPoint2D& point_position);

    bool is_valid;

    float param_on_polygon;

    size_t line_idx;
    float param_on_line;

    float length;

    EasyPoint2D position;

    EasyPoint2D right_direction;
    EasyPoint2D left_direction;
};

#endif // EASY_POLYGON_POINT_H
