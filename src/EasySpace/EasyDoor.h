#ifndef EASY_DOOR_H
#define EASY_DOOR_H

#include <iostream>
#include <string>

#include "EasyShape/EasyShape.h"

enum DoorType
{
    Free = 0,
    BoundaryDoor = 1,
    RoomDoor = 2
};

class EasyDoor
{
public:
    EasyDoor()
    {
    }

    bool reset();

    bool setTargetWidth(
        const float &width);

    bool setDirection(
        const EasyPoint2D &target_direction);

    std::string name;

    float target_width;
    float real_width;

    DoorType door_type;

    EasyPoint2D position;
    EasyPoint2D direction;

    EasyLine2D boundary_line;

};

#endif //EASY_DOOR_H
