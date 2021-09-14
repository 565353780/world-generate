#ifndef SPACE_CONTROLLER_H
#define SPACE_CONTROLLER_H

#include <iostream>
#include <string>

#include "BoundaryController.h"

class SpaceController
{
public:
    SpaceController()
    {
    }

    bool createBoundary(
        const std::vector<EasyPoint2D> &boundary_point_vec);

    bool addBoundaryPoint(
        const EasyPoint2D &boundary_point);

    bool showBoundary();

private:
    BoundaryController boundary_controller_;
};

#endif //SPACE_CONTROLLER_H
