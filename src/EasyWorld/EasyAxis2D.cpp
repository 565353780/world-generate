#include "EasyAxis2D.h"

bool EasyAxis2D::reset()
{
    center_.setPosition(0, 0);

    x_direction_.setPosition(0, 0);
    y_direction_.setPosition(0, 0);

    return true;
}

bool EasyAxis2D::setCenter(
    const float &center_x,
    const float &center_y)
{
    center_.setPosition(center_x, center_y);

    return true;
}

bool EasyAxis2D::setCenter(
    const EasyPoint2D &center)
{
    center_ = center;

    return true;
}

bool EasyAxis2D::setXDirection(
    const float &x_direction_x,
    const float &x_direction_y)
{
    if(x_direction_x == 0 && x_direction_y == 0)
    {
        std::cout << "EasyAxis2D::setXDirection : " <<
          "Input:\n" <<
          "\tx_direction_x = " << x_direction_x << std::endl <<
          "\tx_direction_y = " << x_direction_y << std::endl <<
          "the direction is invalid!" << std::endl;

        return false;
    }

    const float direction_length = sqrt(
        std::pow(x_direction_x, 2) +
        std::pow(x_direction_y, 2));

    return true;
}
