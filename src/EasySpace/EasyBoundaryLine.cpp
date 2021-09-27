#include "EasyBoundaryLine.h"

bool EasyBoundaryLine::reset()
{
    is_valid = false;

    is_start_point_param_set = false;
    is_end_point_param_set = false;

    line_start_boundary_point.reset();
    line_end_boundary_point.reset();

    return true;
}

bool EasyBoundaryLine::setStartPointParam(
    const EasyBoundaryPoint &target_line_start_boundary_point)
{
    line_start_boundary_point = target_line_start_boundary_point;

    is_start_point_param_set = true;

    return true;
}

bool EasyBoundaryLine::setStartPointParam(
    const size_t &target_start_boundary_idx,
    const size_t &target_start_boundary_line_idx,
    const float &target_start_boundary_line_param)
{
    if(!line_start_boundary_point.setPositionParam(
          target_start_boundary_idx,
          target_start_boundary_line_idx,
          target_start_boundary_line_param))
    {
        std::cout << "EasyBoundaryLine::setStartPointParam : " <<
          "setPositionParam for start point failed!" << std::endl;

        return false;
    }

    is_start_point_param_set = true;

    return true;
}

bool EasyBoundaryLine::setEndPointParam(
    const EasyBoundaryPoint &target_line_end_boundary_point)
{
    line_end_boundary_point = target_line_end_boundary_point;

    is_end_point_param_set = true;

    return true;
}

bool EasyBoundaryLine::setEndPointParam(
    const size_t &target_end_boundary_idx,
    const size_t &target_end_boundary_line_idx,
    const float &target_end_boundary_line_param)
{
    if(!line_end_boundary_point.setPositionParam(
          target_end_boundary_idx,
          target_end_boundary_line_idx,
          target_end_boundary_line_param))
    {
        std::cout << "EasyBoundaryLine::setStartPointParam : " <<
          "setPositionParam for end point failed!" << std::endl;

        return false;
    }

    is_end_point_param_set = true;

    return true;
}

bool EasyBoundaryLine::updatePointPosition(
    const std::vector<EasyBoundary> &boundary_vec)
{
    is_valid = false;

    if(is_start_point_param_set)
    {
        if(!line_start_boundary_point.updatePosition(boundary_vec))
        {
            std::cout << "EasyBoundaryLine::updatePointPosition : " <<
              "updatePosition for start point failed!" << std::endl;

            return false;
        }
    }

    if(is_end_point_param_set)
    {
        if(!line_end_boundary_point.updatePosition(boundary_vec))
        {
            std::cout << "EasyBoundaryLine::updatePointPosition : " <<
              "updatePosition for end point failed!" << std::endl;

            return false;
        }
    }

    is_valid = true;

    return true;
}

