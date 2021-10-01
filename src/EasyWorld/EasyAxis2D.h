#ifndef EASY_AXIS_2D_H
#define EASY_AXIS_2D_H

#include <iostream>
#include <string>

#include "EasyShape/EasyShape.h"

class EasyAxis2D
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
        const EasyPoint2D &y_direction);

public:
    EasyPoint2D center_;

    EasyPoint2D x_direction_;
    EasyPoint2D y_direction_;
};

#endif //EASY_AXIS_2D_H
