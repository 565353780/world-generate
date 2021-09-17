#ifndef EASY_BOUNDARY_LINE_H
#define EASY_BOUNDARY_LINE_H

#include <iostream>
#include <string>

#include "EasyBoundaryPoint.h"

class EasyBoundaryLine
{
public:
    EasyBoundaryLine()
    {
    }

    bool reset();

    bool setStartPointParam(
        const EasyBoundaryPoint &target_line_start_boundary_point);

    bool setStartPointParam(
        const size_t &target_start_boundary_idx,
        const size_t &target_start_boundary_line_idx,
        const float &target_start_boundary_line_param);

    bool setEndPointParam(
        const EasyBoundaryPoint &target_line_end_boundary_point);

    bool setEndPointParam(
        const size_t &target_end_boundary_idx,
        const size_t &target_end_boundary_line_idx,
        const float &target_end_boundary_line_param);

    bool updatePointPosition(
        const std::vector<EasyBoundary> &boundary_vec);

    bool is_valid;

    bool is_start_point_param_set;
    bool is_end_point_param_set;
    EasyBoundaryPoint line_start_boundary_point;
    EasyBoundaryPoint line_end_boundary_point;

};

#endif //EASY_BOUNDARY_LINE_H
