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
    }

    bool reset();

    bool findPositionOnBoundary(
        const EasyPolygon2D &boundary);

    bool haveThisNeighboor(
        const size_t &neighboor_room_id);

    bool addNeighboorRoomID(
        const size_t &room_id);

    size_t id;
    std::string name;
    bool is_on_boundary;
    EasyPoint2D position;
    EasyPolygon2D boundary;
    std::vector<size_t> neighboor_room_id_vec;
};

#endif //ROOM_CONTROLLER_H
