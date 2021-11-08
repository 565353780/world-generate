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
    const float start_change_edge_error = 1.0;

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

    EasyPoint2D new_position_in_world;
    EasyPoint2D new_position_in_parent;

    new_position_in_world.setPosition(new_position_x, new_position_y);

    if(!wall_roomcontainer_parent_node->getPointInNode(
          new_position_in_world,
          new_position_in_parent))
    {
        std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]" << std::endl <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "getPointInNode failed!" << std::endl;

        return false;
    }

    WallRoomContainerData &wall_roomcontainer_data =
      world_descriptor_.wall_roomcontainer_data_vec[wall_roomcontainer_id];

    const size_t &wall_id = wall_roomcontainer_data.wall_id;
    const NodeType &wall_type = wall_roomcontainer_data.wall_type;
    const size_t &on_wall_boundary_idx = wall_roomcontainer_data.on_wall_boundary_idx;

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

    const BoundaryLineList &boundary_line_list =
      wall_boundary_line_list.boundary_line_list_vec_[on_wall_boundary_idx];

    const float &wall_length =
      boundary_line_list.boundary_length_;

    if(wall_roomcontainer_data.on_wall_boundary_start_position < start_change_edge_error &&
        new_position_in_parent.y > wall_roomcontainer_data.real_height / 2.0)
    {
        wall_roomcontainer_data.on_wall_boundary_idx =
          (wall_roomcontainer_data.on_wall_boundary_idx - 1 +
           wall_boundary_line_list.boundary_line_list_vec_.size()) %
          wall_boundary_line_list.boundary_line_list_vec_.size();

        const BoundaryLineList &last_boundary_line_list =
          wall_boundary_line_list.boundary_line_list_vec_[
          (on_wall_boundary_idx - 1 + wall_boundary_line_list.boundary_line_list_vec_.size()) %
          wall_boundary_line_list.boundary_line_list_vec_.size()];

        const float last_wall_length = last_boundary_line_list.boundary_length_;

        wall_roomcontainer_data.on_wall_boundary_start_position =
          last_wall_length - wall_roomcontainer_data.target_width;
    }
    else if(wall_roomcontainer_data.on_wall_boundary_start_position + wall_roomcontainer_data.real_width >
        wall_length - start_change_edge_error &&
        new_position_in_parent.y > wall_roomcontainer_data.real_height)
    {
        wall_roomcontainer_data.on_wall_boundary_idx =
          (wall_roomcontainer_data.on_wall_boundary_idx + 1) %
          wall_boundary_line_list.boundary_line_list_vec_.size();

        wall_roomcontainer_data.on_wall_boundary_start_position = 0;
    }
    else
    {
        wall_roomcontainer_data.on_wall_boundary_start_position =
          new_position_in_parent.x - mouse_pos_x_direction_delta;
    }

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

