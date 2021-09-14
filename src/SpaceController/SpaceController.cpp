#include "SpaceController.h"

bool SpaceController::createBoundary(
    const std::vector<EasyPoint2D> &boundary_point_vec)
{
    boundary_controller_.reset();

    if(!boundary_controller_.setBoundaryPointVec(boundary_point_vec))
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
    if(!boundary_controller_.addBoundaryPoint(boundary_point))
    {
        std::cout << "SpaceController::addBoundaryPoint : " <<
          "add Boundary Point failed!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::showBoundary()
{
    if(!boundary_controller_.showBoundary())
    {
        std::cout << "SpaceController::showBoundary : " <<
          "show Boundary failed!" << std::endl;

        return false;
    }

    return true;
}

