#include "WorldEditor.h"

bool WorldEditor::reset()
{
    world_descriptor_.reset();

    return true;
}

bool WorldEditor::setWallRoomContainerPosition(
    WorldController &world_controller,
    WorldPlaceGenerator &world_place_generator,
    const size_t &wall_roomcontainer_id,
    const float &new_position_x,
    const float &new_position_y,
    const float &mouse_pos_x_direction_delta)
{
    if(!world_descriptor_.readData(world_controller, world_place_generator))
    {
        std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]" << std::endl <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "readData failed!" << std::endl;

        return false;
    }

    EasyNode* wall_roomcontainer_node = world_controller.findNode(
        wall_roomcontainer_id, NodeType::RoomContainer);

    if(wall_roomcontainer_node == nullptr)
    {
        std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]" << std::endl <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "this wall roomcontainer not found!" << std::endl;

        return false;
    }

    EasyNode* wall_roomcontainer_parent_node = wall_roomcontainer_node->getParent();
    if(wall_roomcontainer_parent_node == nullptr)
    {
        std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]" << std::endl <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "this wall roomcontainer's parent not exist!" << std::endl;

        return false;
    }

    EasyNode* wall_node = wall_roomcontainer_parent_node->getParent();
    if(wall_node == nullptr)
    {
        std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]" << std::endl <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "this wall roomcontainer's parent wall node not exist!" << std::endl;

        return false;
    }

    EasyPoint2D new_position_in_world;
    new_position_in_world.setPosition(new_position_x, new_position_y);

    EasyPoint2D new_position_in_wall_node;
    if(!wall_node->getPointInNode(
          new_position_in_world,
          new_position_in_wall_node))
    {
        std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]" << std::endl <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "getPointInNode in parent wall node failed!" << std::endl;

        return false;
    }

    WallRoomContainerData &wall_roomcontainer_data =
      world_descriptor_.wall_roomcontainer_data_vec[wall_roomcontainer_id];

    const size_t &wall_id = wall_roomcontainer_data.wall_id;
    const NodeType &wall_type = wall_roomcontainer_data.wall_type;

    size_t wall_boundary_line_list_idx;
    if(!world_place_generator.boundary_line_manager_.getWallBoundaryLineListIdx(
          wall_id, wall_type, wall_boundary_line_list_idx))
    {
        std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]" << std::endl <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "getWallBoundaryLineListIdx failed!" << std::endl;

        return false;
    }

    const WallBoundaryLineList &wall_boundary_line_list =
      world_place_generator.boundary_line_manager_.wall_boundary_line_list_vec_[wall_boundary_line_list_idx];

    const EasyPolygon2D &wall_boundary_polygon = wall_boundary_line_list.wall_boundary_polygon_;

    if(wall_boundary_polygon.point_list.size() == 0)
    {
        std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]" << std::endl <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "wall_boundary_polygon is empty!" << std::endl;

        return false;
    }

    float min_dist2_to_wall_boundary_line = std::numeric_limits<float>::max();
    size_t min_dist_wall_boundary_idx;
    EasyPoint2D nearest_point_on_line;

    for(size_t i = 0; i < wall_boundary_polygon.point_list.size(); ++i)
    {
        const EasyPoint2D &current_point = wall_boundary_polygon.point_list[i];
        const EasyPoint2D &next_point = wall_boundary_polygon.point_list[
        (i + 1) % wall_boundary_polygon.point_list.size()];

        EasyLine2D current_wall_boundary_line;
        current_wall_boundary_line.setPosition(current_point, next_point);

        const EasyPoint2D current_nearest_point_on_line = EasyComputation::getNearestPointOnLine(
            current_wall_boundary_line, new_position_in_wall_node);

        const float current_dist2_to_wall_boundary_line =
          EasyComputation::pointDist2(new_position_in_wall_node, current_nearest_point_on_line);

        if(current_dist2_to_wall_boundary_line < min_dist2_to_wall_boundary_line)
        {
            min_dist2_to_wall_boundary_line = current_dist2_to_wall_boundary_line;
            min_dist_wall_boundary_idx = i;
            nearest_point_on_line = current_nearest_point_on_line;
        }
    }

    wall_roomcontainer_data.on_wall_boundary_idx = min_dist_wall_boundary_idx;

    const float nearest_point_on_line_dist_to_boundary_line_start_point =
      EasyComputation::pointDist(nearest_point_on_line, wall_boundary_polygon.point_list[min_dist_wall_boundary_idx]);

    wall_roomcontainer_data.on_wall_boundary_start_position =
      nearest_point_on_line_dist_to_boundary_line_start_point - mouse_pos_x_direction_delta;

    if(!world_descriptor_.loadData(world_controller, world_place_generator))
    {
        std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]" << std::endl <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "loadData failed!" << std::endl;

        return false;
    }

    return true;
}

