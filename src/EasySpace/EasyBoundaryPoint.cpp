#include "EasyBoundaryPoint.h"

bool EasyBoundaryPoint::reset()
{
    boundary_idx = 0;
    boundary_line_idx = 0;
    boundary_line_param = 0;

    is_position_valid = false;
    position.setPosition(0, 0);

    return true;
}

bool EasyBoundaryPoint::setPositionParam(
    const size_t &target_boundary_idx,
    const size_t &target_boundary_line_idx,
    const float &target_boundary_line_param)
{
    if(target_boundary_line_param < 0 || target_boundary_line_param > 1)
    {
        std::cout << "EasyBoundaryPoint::setPositionParam : " <<
          "target boundary line param out of range! It must in [0, 1]!" << std::endl;

        return false;
    }

    boundary_idx = target_boundary_idx;
    boundary_line_idx = target_boundary_line_idx;
    boundary_line_param = target_boundary_line_param;

    is_position_valid = false;

    return true;
}

bool EasyBoundaryPoint::updatePosition(
    const std::vector<EasyBoundary> &boundary_vec)
{
    if(boundary_idx >= boundary_vec.size())
    {
        std::cout << "EasyBoundaryPoint::updatePosition : " <<
          "boundary idx out of range!" << std::endl;

        return false;
    }

    const EasyBoundary &boundary = boundary_vec[boundary_idx];

    if(boundary_line_idx >= boundary.boundary.point_list.size())
    {
        std::cout << "EasyBoundaryPoint::updatePosition : " <<
          "boundary line idx out of range!" << std::endl;

        return false;
    }

    const EasyPoint2D &line_start_point = boundary.boundary.point_list[boundary_line_idx];
    const EasyPoint2D &line_end_point = boundary.boundary.point_list[
      (boundary_line_idx + 1) % boundary.boundary.point_list.size()];

    const float boundary_point_x =
      line_start_point.x + boundary_line_param * (line_end_point.x - line_start_point.x);
    const float boundary_point_y =
      line_start_point.y + boundary_line_param * (line_end_point.y - line_start_point.y);

    position.setPosition(boundary_point_x, boundary_point_y);
    is_position_valid = true;

    return true;
}

