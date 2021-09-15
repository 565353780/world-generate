#ifndef BOUNDARY_CONTROLLER_H
#define BOUNDARY_CONTROLLER_H

#include <iostream>
#include <string>

#include "EasyShape/EasyShape.h"

class EasyBoundary
{
public:
    EasyBoundary()
    {
    }

    bool reset();

    bool addBoundaryPoint(
        const EasyPoint2D &boundary_point);

    bool addBoundaryPoint(
        const float &x,
        const float &y);

    bool setBoundaryPointVec(
        const std::vector<EasyPoint2D> &boundary_point_vec);

    bool haveThisRoomOnBoundary(
        const size_t &room_idx);

    std::string name;
    EasyPolygon2D boundary;
    std::vector<size_t> exist_room_idx_vec;
};

#endif //BOUNDARY_CONTROLLER_H
