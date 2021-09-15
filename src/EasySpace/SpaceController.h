#ifndef SPACE_CONTROLLER_H
#define SPACE_CONTROLLER_H

#include <iostream>
#include <string>

#include "EasyShape/EasyShape.h"
#include "EasySpace.h"

class SpaceController
{
public:
    SpaceController()
    {
    }

    bool setBoundaryPointVec(
        const std::vector<EasyPoint2D> &boundary_point_vec);

    bool addBoundaryPoint(
        const EasyPoint2D &boundary_point);

    bool addBoundaryPoint(
        const float &x,
        const float &y);

    bool showBoundary();

private:
    EasyBoundary boundary_;
};

#endif //SPACE_CONTROLLER_H
