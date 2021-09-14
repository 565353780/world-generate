#include "BoundaryController.h"

bool BoundaryController::setBoundary(
    std::vector<EasyPoint2D> &boundary_point_vec)
{
    boundary_.point_list.clear();

    if(boundary_point_vec.size() == 0)
    {
        std::cout << "BoundaryController::setBoundary : " <<
          "boundary_point_vec is empty!" << std::endl;

        return false;
    }

    for(const EasyPoint2D &boundary_point : boundary_point_vec)
    {
        boundary_.addPoint(boundary_point);
    }

    return true;
}

bool BoundaryController::showBoundary()
{
    const float &x_diff = boundary_.rect.x_diff;
    const float &y_diff = boundary_.rect.y_diff;

    return true;
}
