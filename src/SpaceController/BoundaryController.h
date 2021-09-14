#ifndef BOUNDARY_CONTROLLER_H
#define BOUNDARY_CONTROLLER_H

#include <iostream>
#include <string>

#include "EasyShape/EasyShape.h"

#include </home/chli/OpenCV/opencv-3.4.10/build/installed/include/opencv2/opencv.hpp>

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
