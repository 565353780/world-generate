#ifndef BOUNDARY_CONTROLLER_H
#define BOUNDARY_CONTROLLER_H

#include <iostream>
#include <string>

#include "EasyShape/EasyShape.h"

// for test only
#include </home/chli/OpenCV/opencv-3.4.10/build/installed/include/opencv2/opencv.hpp>

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

    // for test only
    bool showBoundary();

    EasyPolygon2D boundary;
};

#endif //BOUNDARY_CONTROLLER_H
