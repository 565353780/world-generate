#include "EasyDoor.h"

bool EasyDoor::reset()
{
    name = "";

    target_width = -1;
    real_width = -1;

    door_type = DoorType::Free;

    position.setPosition(0, 0);
    direction.setPosition(0, 0);

    boundary_line.setPosition(0, 0, 0, 0);

    return true;
}

bool EasyDoor::setTargetWidth(
    const float &width)
{
    if(width <= 0)
    {
        std::cout << "EasyDoor::setTargetWidth : " <<
          "width <= 0!" << std::endl;

        return false;
    }

    target_width = width;

    return true;
}

bool EasyDoor::setDirection(
    const EasyPoint2D &target_direction)
{
    const float direction_length = sqrt(
        std::pow(target_direction.x, 2) +
        std::pow(target_direction.y, 2));

    if(direction_length == 0)
    {
        std::cout << "EasyDoor::setDirection : " <<
          "target direction length = 0!" << std::endl;

        return false;
    }

    direction.setPosition(
        target_direction.x / direction_length,
        target_direction.y / direction_length);

    return true;
}

