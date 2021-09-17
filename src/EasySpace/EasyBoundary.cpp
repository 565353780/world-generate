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

