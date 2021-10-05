#include "WorldController.h"

bool WorldController::reset()
{
    if(!world_tree_.reset())
    {
        std::cout << "WorldController::reset : " << std::endl <<
          "reset world_tree_ failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createWorld()
{
    if(!world_tree_.createWorld())
    {
        std::cout << "WorldController::createWorld : " << std::endl <<
          "createWorld failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createWall(
    const size_t &wall_id,
    const NodeType &wall_type)
{
    if(!world_tree_.createWall(wall_id, wall_type))
    {
        std::cout << "WorldController::createWall : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "createWall failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createWallBoundary(
    const size_t &wall_id,
    const NodeType &wall_type,
    const EasyPolygon2D &wall_boundary_polygon)
{
    if(!world_tree_.createWallBoundary(wall_id, wall_type, wall_boundary_polygon))
    {
        std::cout << "WorldController::createWallBoundary : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "createWallBoundary failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::outputInfo()
{
    world_tree_.outputInfo();

    return true;
}

