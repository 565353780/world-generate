#ifndef ROOM_CONTROLLER_H
#define ROOM_CONTROLLER_H

#include <iostream>
#include <string>

#include "EasyShape/EasyShape.h"

class EasyRoom
{
public:
    EasyRoom()
    {
        is_on_boundary = false;
    }

    bool reset();

    bool haveThisNeighboor(
        const size_t &neighboor_room_id);

    bool addNeighboorRoomIdx(
        const size_t &room_idx);

    std::string name;
    bool is_on_boundary;
    size_t on_boundary_idx;
    EasyPoint2D position;
    EasyPolygon2D boundary;
    std::vector<size_t> neighboor_room_idx_vec;
};

#endif //ROOM_CONTROLLER_H
