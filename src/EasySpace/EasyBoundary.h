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
        is_outer_boundary = false;
    }

    bool reset();

    bool setOuterBoundary();

    bool addBoundaryPoint(
        const EasyPoint2D &boundary_point);

    bool addBoundaryPoint(
        const float &x,
        const float &y);

    bool setBoundaryPointVec(
        const std::vector<EasyPoint2D> &boundary_point_vec);

    std::string name;

    bool is_outer_boundary;
    EasyPolygon2D boundary;
};

#endif //BOUNDARY_CONTROLLER_H
