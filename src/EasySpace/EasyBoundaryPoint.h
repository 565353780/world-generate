#ifndef EASY_BOUNDARY_POINT_H
#define EASY_BOUNDARY_POINT_H

#include <iostream>
#include <string>

#include "EasyShape/EasyPoint2D.h"
#include "EasySpace/EasyBoundary.h"

class EasyBoundaryPoint
{
public:
    EasyBoundaryPoint()
    {
        reset();
    }

    bool reset();

    bool setPositionParam(
        const size_t &target_boundary_idx,
        const size_t &target_boundary_line_idx,
        const float &target_boundary_line_param);

    bool updatePosition(
        const std::vector<EasyBoundary> &boundary_vec);

    size_t boundary_idx;
    size_t boundary_line_idx;
    float boundary_line_param;
    bool is_valid;

    bool is_position_valid;
    EasyPoint2D position;
};

#endif //EASY_BOUNDARY_POINT_H
