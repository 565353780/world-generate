#ifndef BOUNDARY_CONTROLLER_H
#define BOUNDARY_CONTROLLER_H

#include <iostream>
#include <string>

#include "EasyShape/EasyShape.h"

class BoundaryController
{
public:
    BoundaryController()
    {
    }

    bool setBoundary(
        std::vector<EasyPoint2D> &boundary_point_vec);

    bool showBoundary();

private:
    EasyPolygon2D boundary_;
};

#endif //BOUNDARY_CONTROLLER_H
