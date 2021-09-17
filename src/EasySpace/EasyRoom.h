#ifndef ROOM_CONTROLLER_H
#define ROOM_CONTROLLER_H

#include <iostream>
#include <string>

#include "EasyShape/EasyShape.h"

enum BoundaryState
{
    Free = 0,
    NearRoom = 1,
    NearWall = 2
};

class EasyRoom
{
public:
    EasyRoom()
    {
    }

    bool reset();

    bool setTargetSize(
        const float &width,
        const float &height);

    bool haveThisNeighboor(
        const size_t &neighboor_room_id);

    bool addNeighboorRoomIdx(
        const size_t &room_idx);

    std::string name;

    float target_area;
    float real_area;
    float target_width;
    float real_width;
    float target_height;
    float real_height;

    EasyPoint2D position;

    EasyPolygon2D boundary;
    std::vector<BoundaryState> boundary_near_vec;

    std::vector<size_t> neighboor_room_idx_vec;
};

#endif //ROOM_CONTROLLER_H
