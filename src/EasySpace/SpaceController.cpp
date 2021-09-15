#include "SpaceController.h"

bool SpaceController::setBoundaryPointVec(
    const std::vector<EasyPoint2D> &boundary_point_vec)
{
    boundary_.reset();

    if(!boundary_.setBoundaryPointVec(boundary_point_vec))
    {
        std::cout << "SpaceController::createBoundary : " <<
          "set Boundary Point Vec failed!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::addBoundaryPoint(
    const EasyPoint2D &boundary_point)
{
    if(!boundary_.addBoundaryPoint(boundary_point))
    {
        std::cout << "SpaceController::addBoundaryPoint : " <<
          "add Boundary Point failed!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::addBoundaryPoint(
    const float &x,
    const float &y)
{
    if(!boundary_.addBoundaryPoint(x, y))
    {
        std::cout << "SpaceController::addBoundaryPoint : " <<
          "add Boundary Point failed!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::showBoundary()
{
    if(!boundary_.showBoundary())
    {
        std::cout << "SpaceController::showBoundary : " <<
          "show Boundary failed!" << std::endl;

        return false;
    }

    return true;
}

