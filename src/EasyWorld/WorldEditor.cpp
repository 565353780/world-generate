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

    EasyPoint2D new_position_in_world;
    new_position_in_world.setPosition(new_position_x, new_position_y);

    float min_dist2_to_wall_boundary_line = std::numeric_limits<float>::max();
    size_t min_dist_wall_id;
    NodeType min_dist_wall_type;
    size_t min_dist_wall_boundary_idx;
    EasyPoint2D min_dist_wall_boundary_start_point;
    EasyPoint2D nearest_point_on_line;

    for(size_t i = 0; i < world_place_generator.boundary_line_manager_.wall_boundary_line_list_vec_.size(); ++i)
    {
        const WallBoundaryLineList &current_wall_boundary_line_list =
          world_place_generator.boundary_line_manager_.wall_boundary_line_list_vec_[i];

        const size_t &current_wall_id = current_wall_boundary_line_list.wall_id_;
        const NodeType &current_wall_type = current_wall_boundary_line_list.wall_type_;
        const EasyPolygon2D &current_wall_boundary_polygon =
          current_wall_boundary_line_list.wall_boundary_polygon_;

        if(current_wall_boundary_polygon.point_list.size() == 0)
        {
            std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
              "Input :\n" <<
              "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
              "\tnew_position = [" << new_position_x << "," <<
              new_position_y << "]" << std::endl <<
              "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
              "current wall boundary polygon is empty!" << std::endl;

            return false;
        }

        EasyNode* current_wall_node = world_controller.findNode(current_wall_id, current_wall_type);
        if(current_wall_node == nullptr)
        {
            std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
              "Input :\n" <<
              "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
              "\tnew_position = [" << new_position_x << "," <<
              new_position_y << "]" << std::endl <<
              "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
              "findNode for current wall node failed!" << std::endl;

            return false;
        }

        EasyPoint2D new_position_in_current_wall_node;
        if(!current_wall_node->getPointInNode(
              new_position_in_world,
              new_position_in_current_wall_node))
        {
            std::cout << "WorldEditor::setWallRoomContainerPosition : " << std::endl <<
              "Input :\n" <<
              "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
              "\tnew_position = [" << new_position_x << "," <<
              new_position_y << "]" << std::endl <<
              "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
              "getPointInNode in wall node failed!" << std::endl;

            return false;
        }

        for(size_t j = 0; j < current_wall_boundary_polygon.point_list.size(); ++j)
        {
            const EasyPoint2D &current_point = current_wall_boundary_polygon.point_list[j];
            const EasyPoint2D &next_point = current_wall_boundary_polygon.point_list[
            (j + 1) % current_wall_boundary_polygon.point_list.size()];

            EasyLine2D current_wall_boundary_line;
            current_wall_boundary_line.setPosition(current_point, next_point);

            const EasyPoint2D current_nearest_point_on_line = EasyComputation::getNearestPointOnLine(
                current_wall_boundary_line, new_position_in_current_wall_node);

            const float current_dist2_to_wall_boundary_line =
              EasyComputation::pointDist2(new_position_in_current_wall_node, current_nearest_point_on_line);

            if(current_dist2_to_wall_boundary_line < min_dist2_to_wall_boundary_line)
            {
                min_dist2_to_wall_boundary_line = current_dist2_to_wall_boundary_line;
                min_dist_wall_id = current_wall_id;
                min_dist_wall_type = current_wall_type;
                min_dist_wall_boundary_idx = j;
                min_dist_wall_boundary_start_point = current_point;
                nearest_point_on_line = current_nearest_point_on_line;
            }
        }
    }

    WallRoomContainerData &wall_roomcontainer_data =
      world_descriptor_.wall_roomcontainer_data_vec[wall_roomcontainer_id];

    wall_roomcontainer_data.wall_id = min_dist_wall_id;
    wall_roomcontainer_data.wall_type = min_dist_wall_type;
    wall_roomcontainer_data.on_wall_boundary_idx = min_dist_wall_boundary_idx;

    const float nearest_point_on_line_dist_to_boundary_line_start_point =
      EasyComputation::pointDist(nearest_point_on_line, min_dist_wall_boundary_start_point);

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

