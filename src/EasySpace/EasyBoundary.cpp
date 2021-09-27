#include "EasyBoundary.h"
#include <opencv2/core/types.hpp>

bool EasyBoundary::reset()
{
    name = "";

    is_outer_boundary = false;
    boundary.reset();

    return true;
}

bool EasyBoundary::setOuterBoundary()
{
    is_outer_boundary = true;

    return true;
}

bool EasyBoundary::addBoundaryPoint(
    const EasyPoint2D &boundary_point)
{
    boundary.addPoint(boundary_point);

    boundary.setAntiClockWise();

    return true;
}

bool EasyBoundary::addBoundaryPoint(
    const float &x,
    const float &y)
{
    EasyPoint2D boundary_point;
    boundary_point.setPosition(x, y);
    
    return addBoundaryPoint(boundary_point);
}

bool EasyBoundary::setBoundaryPointVec(
    const std::vector<EasyPoint2D> &boundary_point_vec)
{
    boundary.point_list.clear();

    if(boundary_point_vec.size() == 0)
    {
        std::cout << "EasyBoundary::setBoundary : " <<
          "boundary_point_vec is empty!" << std::endl;

        return false;
    }

    for(const EasyPoint2D &boundary_point : boundary_point_vec)
    {
        addBoundaryPoint(boundary_point);
    }

    return true;
}

bool EasyBoundary::getVerticalDirection(
    const size_t &boundary_line_idx,
    // const size_t &boundary_line_param,
    EasyPoint2D &vertical_direction)
{
    vertical_direction.setPosition(0, 0);

    if(boundary_line_idx >= boundary.point_list.size())
    {
        std::cout << "EasyBoundary::getVerticalDirection : " <<
          "boundary line idx out of range!" << std::endl;

        return false;
    }

    const EasyPoint2D &boundary_start_point = boundary.point_list[boundary_line_idx];
    const EasyPoint2D &boundary_end_point =
      boundary.point_list[(boundary_line_idx + 1) % boundary.point_list.size()];

    const float x_diff = boundary_end_point.x - boundary_start_point.x;
    const float y_diff = boundary_end_point.y - boundary_start_point.y;

    const float boundary_line_length =
      EasyComputation::pointDist(boundary_start_point, boundary_end_point);

    vertical_direction.setPosition(-y_diff / boundary_line_length, x_diff / boundary_line_length);

    return true;
}

