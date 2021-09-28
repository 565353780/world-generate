#include "EasyFixture.h"

bool EasyFixture::reset()
{
    is_size_valid = false;
    width = -1;
    height = -1;

    is_direction_valid = false;
    direction.setPosition(0, 0);

    return true;
}

bool EasyFixture::setSize(
    const float &target_width,
    const float &target_height)
{
    is_size_valid = false;

    if(target_width <= 0)
    {
        std::cout << "EasyFixture::setSize : " <<
          "target width <= 0!" << std::endl;

        return false;
    }

    if(target_height <= 0)
    {
        std::cout << "EasyFixture::setSize : " <<
          "target height <= 0!" << std::endl;

        return false;
    }

    width = target_width;
    height = target_height;

    is_size_valid = true;

    return true;
}

bool EasyFixture::setDirection(
    const EasyPoint2D &target_direction)
{
    is_direction_valid = false;

    const float direction_length = sqrt(
        std::pow(target_direction.x, 2) + std::pow(target_direction.y, 2));

    if(direction_length == 0)
    {
        std::cout << "EasyFixture::setDirection : " <<
          "target direction length is 0!" << std::endl;

        return false;
    }

    direction.setPosition(
        target_direction.x / direction_length,
        target_direction.y / direction_length);

    is_direction_valid = true;

    return true;
}

