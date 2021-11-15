#ifndef EASY_AXIS_2D_H
#define EASY_AXIS_2D_H

#include "export_library_global.h"

#include "EasyShape/EasyShape.h"

class LIBRARY_EXPORT EasyAxis2D
{
public:
    EasyAxis2D(){}

    bool reset();

    bool setCenter(
        const float &center_x,
        const float &center_y);

    bool setXDirection(
        const float &x_direction_x,
        const float &x_direction_y);

    bool setYDirection(
        const float &y_direction_x,
        const float &y_direction_y);

    bool isValid() const;

    bool outputInfo(
        const size_t &info_level) const;

public:
    bool is_valid_;

    EasyPoint2D center_;

    EasyPoint2D x_direction_;
    EasyPoint2D y_direction_;

private:
    bool is_center_valid_;
    bool is_direction_valid_;
};

#endif //EASY_AXIS_2D_H
