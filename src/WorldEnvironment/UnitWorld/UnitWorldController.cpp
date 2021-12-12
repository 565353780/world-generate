#include "UnitWorldController.h"
#include <cstddef>

bool UnitWorldController::reset()
{
    if(!unit_tree.reset())
    {
        std::cout << "UnitWorldController::reset :\n" <<
          "reset for unit_tree failed!\n";

        return false;
    }

    if(!unit_node_line_manager.reset())
    {
        std::cout << "UnitWorldController::reset :\n" <<
          "reset for unit_node_line_manager failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldController::createWorld()
{
    if(!unit_tree.createTree())
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
    if(!unit_tree.createNode(wall_name, wall_id, wall_type, 0, NodeType::World))
    {
        std::cout << "UnitWorldController::createWall :\n" <<
          "Input :\n" <<
          "\t wall_name = " << wall_name << std::endl <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "createNode failed!\n";

        return false;
    }

    if(!unit_node_line_manager.createWallLine(wall_id, wall_type))
    {
        std::cout << "UnitWorldController::createWall :\n" <<
          "Input :\n" <<
          "\t wall_name = " << wall_name << std::endl <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "createWallLine failed!\n";

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
    if(!unit_tree.createNode(room_name, room_id, room_type, on_wall_id, on_wall_type))
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

bool UnitWorldController::setWallBoundaryPolygon(
    const size_t& wall_id,
    const NodeType& wall_type,
    const EasyPolygon2D& wall_boundary_polygon)
{
    EasyPolygon2D valid_wall_boundary_polygon = wall_boundary_polygon;

    if(wall_type == NodeType::OuterWall)
    {
        valid_wall_boundary_polygon.setAntiClockWise();
    }
    else
    {
        valid_wall_boundary_polygon.setClockWise();
    }

    if(!unit_tree.setBoundaryPolygon(wall_id, wall_type, valid_wall_boundary_polygon))
    {
        std::cout << "UnitWorldController::setWallBoundaryPolygon :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "setBoundaryPolygon in tree failed!\n";

        return false;
    }

    if(!unit_node_line_manager.setBoundaryPolygon(
          wall_id, wall_type, valid_wall_boundary_polygon))
    {
        std::cout << "UnitWorldController::setWallBoundaryPolygon :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "setBoundaryPolygon in manager failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldController::getNearestWall(
    const EasyPoint2D& point,
    size_t& nearest_wall_id,
    NodeType& nearest_wall_type)
{
    nearest_wall_id = 0;
    nearest_wall_type = NodeType::NodeFree;

    if(unit_node_line_manager.wall_line_vec.size() == 0)
    {
        std::cout << "UnitWorldController::getNearestWall :\n" <<
          "Input :\n" <<
          "\t point = [" << point.x << "," <<
          point.y << "]\n" <<
          "no wall has been saved!\n";

        return false;
    }

    float min_dist2_to_wall = std::numeric_limits<float>::max();

    for(const WallUnitNodeLine& wall_line : unit_node_line_manager.wall_line_vec)
    {
        const EasyPolygon2D& wall_boundary_polygon = wall_line.wall_boundary_polygon;

        if(wall_boundary_polygon.point_list.size() == 0)
        {
            continue;
        }

        for(size_t i = 0; i < wall_boundary_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D& current_point = wall_boundary_polygon.point_list[i];
            const EasyPoint2D& next_point = wall_boundary_polygon.point_list[
              (i + 1) % wall_boundary_polygon.point_list.size()];

            EasyLine2D current_wall_boundary_line;
            current_wall_boundary_line.setPosition(current_point, next_point);

            const EasyPoint2D current_nearest_point_on_line = EasyComputation::getNearestPointOnLine(
                current_wall_boundary_line, point);

            const float current_min_dist2_to_wall_boundary_line =
              EasyComputation::pointDist2(current_nearest_point_on_line, point);

            if(current_min_dist2_to_wall_boundary_line < min_dist2_to_wall)
            {
                min_dist2_to_wall = current_min_dist2_to_wall_boundary_line;
                nearest_wall_id = wall_line.wall_id;
                nearest_wall_type = wall_line.wall_type;
            }
        }
    }

    if(nearest_wall_type == NodeType::NodeFree)
    {
        std::cout << "UnitWorldController::getNearestWall :\n" <<
          "Input :\n" <<
          "\t point = [" << point.x << "," <<
          point.y << "]\n" <<
          "no valid wall found!\n";

        return false;
    }

    return true;
}

bool UnitWorldController::setRoomPositionOnTree(
    const size_t& room_id,
    const NodeType& room_type,
    const size_t& parent_id,
    const NodeType& parent_type,
    const float& room_target_param,
    const float& room_target_width,
    const float& room_target_height)
{
    if(!unit_tree.setNodeParent(room_id, room_type, parent_id, parent_type))
    {
        std::cout << "UnitWorldController::setRoomPositionOnTree :\n" <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t parent_id = " << parent_id << std::endl <<
          "\t parent_type = " << parent_type << std::endl <<
          "\t room_target_param = " << room_target_param << std::endl <<
          "\t room_target_size = [" << room_target_width << "," <<
          room_target_height << "]\n" <<
          "setNodeParent failed!\n";

        return false;
    }

    UnitNode* search_node_parent = unit_tree.findNode(parent_id, parent_type);

    if(search_node_parent == nullptr)
    {
        std::cout << "UnitWorldController::setRoomPositionOnTree :\n" <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t parent_id = " << parent_id << std::endl <<
          "\t parent_type = " << parent_type << std::endl <<
          "\t room_target_param = " << room_target_param << std::endl <<
          "\t room_target_size = [" << room_target_width << "," <<
          room_target_height << "]\n" <<
          "new parent node not exist!\n";

        return false;
    }

    const EasyPolygon2D& parent_boundary_polygon = search_node_parent->boundary_polygon;

    EasyPolygonPoint2D trans_point;

    if(!trans_point.updateByPolygonParam(parent_boundary_polygon, room_target_param))
    {
        std::cout << "UnitWorldController::setRoomPositionOnTree :\n" <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t parent_id = " << parent_id << std::endl <<
          "\t parent_type = " << parent_type << std::endl <<
          "\t room_target_param = " << room_target_param << std::endl <<
          "\t room_target_size = [" << room_target_width << "," <<
          room_target_height << "]\n" <<
          "updateByPolygonParam for trans_point failed!\n";

        return false;
    }

    const float current_param_length = trans_point.length;

    float room_target_left_length = current_param_length - room_target_width / 2.0;
    if(room_target_left_length < 0)
    {
        room_target_left_length += parent_boundary_polygon.perimeter;
    }

    if(!trans_point.updateByLength(parent_boundary_polygon, room_target_left_length))
    {
        std::cout << "UnitWorldController::setRoomPositionOnTree :\n" <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t parent_id = " << parent_id << std::endl <<
          "\t parent_type = " << parent_type << std::endl <<
          "\t room_target_param = " << room_target_param << std::endl <<
          "\t room_target_size = [" << room_target_width << "," <<
          room_target_height << "]\n" <<
          "updateByLength for room left param failed!\n";

        return false;
    }
    const float room_target_left_param = trans_point.param_on_polygon;

    float room_target_right_length = current_param_length + room_target_width / 2.0;
    if(room_target_right_length > parent_boundary_polygon.perimeter)
    {
        room_target_right_length -= parent_boundary_polygon.perimeter;
    }

    if(!trans_point.updateByLength(parent_boundary_polygon, room_target_right_length))
    {
        std::cout << "UnitWorldController::setRoomPositionOnTree :\n" <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t parent_id = " << parent_id << std::endl <<
          "\t parent_type = " << parent_type << std::endl <<
          "\t room_target_param = " << room_target_param << std::endl <<
          "\t room_target_size = [" << room_target_width << "," <<
          room_target_height << "]\n" <<
          "updateByLength for room right param failed!\n";

        return false;
    }
    const float room_target_right_param = trans_point.param_on_polygon;

    UnitNodePosition target_position;
    target_position.node_id = room_id;
    target_position.node_type = room_type;
    target_position.target_left_param = room_target_left_param;
    target_position.target_right_param = room_target_right_param;
    target_position.target_height = room_target_height;

    if(!unit_node_line_manager.insertPosition(parent_id, parent_type, target_position))
    {
        std::cout << "UnitWorldController::setRoomPositionOnTree :\n" <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t parent_id = " << parent_id << std::endl <<
          "\t parent_type = " << parent_type << std::endl <<
          "\t room_target_param = " << room_target_param << std::endl <<
          "\t room_target_size = [" << room_target_width << "," <<
          room_target_height << "]\n" <<
          "insertPosition for room failed!\n";

        return false;
    }

    float valid_param =
      (target_position.real_left_param + target_position.real_right_param) / 2.0;
    if(target_position.real_left_param > target_position.real_right_param)
    {
        if(valid_param > 0.5)
        {
            valid_param -= 0.5;
        }
        else
        {
            valid_param += 0.5;
        }
    }

    float valid_param_diff =
      target_position.real_right_param - target_position.real_left_param;
    if(valid_param_diff < 0)
    {
      valid_param_diff += 1.0;
    }

    const float valid_room_width = valid_param_diff * parent_boundary_polygon.perimeter;

    if(!unit_tree.setNodePositionOnParentPolygonByPolygonParam(
          room_id, room_type,
          valid_param, 0,
          valid_room_width, target_position.target_height,
          PI / 2.0, PI / 2.0))
    {
        std::cout << "UnitWorldController::setRoomPositionOnTree :\n" <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t parent_id = " << parent_id << std::endl <<
          "\t parent_type = " << parent_type << std::endl <<
          "\t room_target_param = " << room_target_param << std::endl <<
          "\t room_target_size = [" << room_target_width << "," <<
          room_target_height << "]\n" <<
          "setNodePositionOnParentPolygonByPolygonParam failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldController::setRoomPositionOnTreeByPosition(
    const size_t& room_id,
    const NodeType& room_type,
    const EasyPoint2D& point)
{
    size_t nearest_wall_id = 0;
    NodeType nearest_wall_type = NodeType::NodeFree;

    if(!getNearestWall(point, nearest_wall_id, nearest_wall_type))
    {
        std::cout << "UnitWorldController::setRoomPositionOnTreeByPosition :\n" <<
          "Input :\n" <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t point = [" << point.x << "," <<
          point.y << "]\n" <<
          "getNearestWall failed!\n";

        return false;
    }

    UnitNode* search_wall_node = unit_tree.findNode(nearest_wall_id, nearest_wall_type);

    if(search_wall_node == nullptr)
    {
        std::cout << "UnitWorldController::setRoomPositionOnTreeByPosition :\n" <<
          "Input :\n" <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t point = [" << point.x << "," <<
          point.y << "]\n" <<
          "this wall node not exist!\n";

        return false;
    }

    const EasyPolygon2D& search_wall_boundary_polygon = search_wall_node->boundary_polygon;

    EasyPolygonPoint2D polygon_point;

    if(!polygon_point.updateByPosition(search_wall_boundary_polygon, point))
    {
        std::cout << "UnitWorldController::setRoomPositionOnTreeByPosition :\n" <<
          "Input :\n" <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t point = [" << point.x << "," <<
          point.y << "]\n" <<
          "updateByPosition failed!\n";

        return false;
    }

    const float point_dist_to_wall_polygon =
      EasyComputation::pointDist(point, polygon_point.position);

    if(!setRoomPositionOnTree(
          room_id, room_type,
          nearest_wall_id, nearest_wall_type,
          polygon_point.param_on_polygon,
          point_dist_to_wall_polygon, point_dist_to_wall_polygon))
    {
        std::cout << "UnitWorldController::setRoomPositionOnTreeByPosition :\n" <<
          "Input :\n" <<
          "\t room_id = " << room_id << std::endl <<
          "\t room_type = " << room_type << std::endl <<
          "\t point = [" << point.x << "," <<
          point.y << "]\n" <<
          "setRoomPositionOnTree failed!\n";

        return false;
    }

    return true;
}

