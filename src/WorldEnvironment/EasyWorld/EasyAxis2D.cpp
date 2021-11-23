#include "EasyAxis2D.h"

bool EasyAxis2D::reset()
{
    is_valid_ = false;

    center_.setPosition(0, 0);

    x_direction_.setPosition(0, 0);
    y_direction_.setPosition(0, 0);

    is_center_valid_ = false;
    is_direction_valid_ = false;

    return true;
}

bool EasyAxis2D::setCenter(
    const float &center_x,
    const float &center_y)
{
    is_valid_ = false;
    is_center_valid_ = false;

    center_.setPosition(center_x, center_y);

    is_center_valid_ = true;

    if(is_direction_valid_)
    {
        is_valid_ = true;
    }

    return true;
}

bool EasyAxis2D::setXDirection(
    const float &x_direction_x,
    const float &x_direction_y)
{
    is_valid_ = false;
    is_direction_valid_ = false;

    if(x_direction_x == 0 && x_direction_y == 0)
    {
        std::cout << "EasyAxis2D::setXDirection : " << std::endl <<
          "Input:\n" <<
          "\tx_direction_x = " << x_direction_x << std::endl <<
          "\tx_direction_y = " << x_direction_y << std::endl <<
          "the direction is invalid!" << std::endl;

        return false;
    }

    const float direction_length = sqrt(
        x_direction_x * x_direction_x +
        x_direction_y * x_direction_y);

    const float unit_x_direction_x = x_direction_x / direction_length;
    const float unit_x_direction_y = x_direction_y / direction_length;

    x_direction_.setPosition(
        unit_x_direction_x,
        unit_x_direction_y);

    y_direction_.setPosition(
        -unit_x_direction_y,
        unit_x_direction_x);

    is_direction_valid_ = true;

    if(is_center_valid_)
    {
        is_valid_ = true;
    }

    return true;
}

bool EasyAxis2D::setYDirection(
    const float &y_direction_x,
    const float &y_direction_y)
{
    is_valid_ = false;
    is_direction_valid_ = false;

    if(y_direction_x == 0 && y_direction_y == 0)
    {
        std::cout << "EasyAxis2D::setYDirection : " << std::endl <<
          "Input:\n" <<
          "\ty_direction_x = " << y_direction_x << std::endl <<
          "\ty_direction_y = " << y_direction_y << std::endl <<
          "the direction is invalid!" << std::endl;

        return false;
    }

    const float direction_length = sqrt(
        y_direction_x * y_direction_x +
        y_direction_y * y_direction_y);

    const float unit_y_direction_x = y_direction_x / direction_length;
    const float unit_y_direction_y = y_direction_y / direction_length;

    y_direction_.setPosition(
        unit_y_direction_x,
        unit_y_direction_y);

    x_direction_.setPosition(
        unit_y_direction_y,
        -unit_y_direction_x);

    is_direction_valid_ = true;

    if(is_center_valid_)
    {
        is_valid_ = true;
    }

    return true;
}

bool EasyAxis2D::isValid() const
{
    return is_valid_;
}

bool EasyAxis2D::outputInfo(
    const size_t &info_level) const
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "EasyAxis2D :" << std::endl <<
      line_start << "\tcenter = [" << center_.x << "," << center_.y << "]" << std::endl <<
      line_start << "\tx_direction = [" << x_direction_.x << "," <<
      x_direction_.y << "]" << std::endl <<
      line_start << "\tis_valid = " << is_valid_ << std::endl;

    return true;
}

