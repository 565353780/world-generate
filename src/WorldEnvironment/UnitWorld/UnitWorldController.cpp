#include "UnitWorldController.h"

bool UnitWorldController::reset()
{
    if(!unit_tree_.reset())
    {
        std::cout << "UnitWorldController::reset :\n" <<
          "reset for unit_tree_ failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldController::createWorld()
{
    if(!unit_tree_.createTree())
    {
        std::cout << "UnitWorldController::createWorld :\n" <<
          "createTree failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldController::createWall(
    const std::string& wall_name,
    const size_t& wall_id,
    const NodeType& wall_type)
{
    if(!unit_tree_.createNode(wall_name, wall_id, wall_type, 0, NodeType::World))
    {
        std::cout << "UnitWorldController::createWall :\n" <<
          "Input :\n" <<
          "\t wall_name = " << wall_name << std::endl <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "createNode failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldController::createRoom(
    const std::string& room_name,
    const size_t& room_id,
    const NodeType& room_type,
    const size_t& on_wall_id,
    const NodeType& on_wall_type)
{
    if(!unit_tree_.createNode(room_name, room_id, room_type, on_wall_id, on_wall_type))
    {
        std::cout << "UnitWorldController::createRoom :\n" <<
          "Input :\n" <<
          "\t room_name = " << room_name << std::endl <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t on_wall_id = " << on_wall_id << std::endl <<
          "\t on_wall_type = " << on_wall_type << std::endl <<
          "createNode failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldController::setBoundaryPolygon(
    const size_t& node_id,
    const NodeType& node_type,
    const EasyPolygon2D& boundary_polygon)
{
    if(!unit_tree_.setBoundaryPolygon(node_id, node_type, boundary_polygon))
    {
        std::cout << "UnitWorldController::setBoundaryPolygon :\n" <<
          "Input :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "setBoundaryPolygon failed!\n";

        return false;
    }

    return true;
}

