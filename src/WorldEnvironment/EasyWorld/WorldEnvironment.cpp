#include "WorldEnvironment.h"

bool WorldEnvironment::reset()
{
    if(!world_controller_.reset())
    {
        std::cout << "WorldEnvironment::reset :\n" <<
          "reset world_controller_ failed!\n";

        return false;
    }

    world_place_generator_.reset();
    world_editor_.reset();
    return true;
}

bool WorldEnvironment::resetButRemainWall()
{
    if(!world_place_generator_.resetButRemainWall(
          world_controller_))
    {
        std::cout << "WorldEnvironment::resetButRemainWall :\n" <<
          "resetButRemainWall failed!\n";

        return false;
    }

    return true;
}

bool WorldEnvironment::createNewWorld(
    const float& world_center_x,
    const float& world_center_y)
{
    if(!world_place_generator_.createNewWorld(
          world_controller_,
          world_center_x,
          world_center_y))
    {
        std::cout << "WorldEnvironment::createNewWorld :\n" <<
          "Input :\n" <<
          "world_center = [" << world_center_x << "," <<
          world_center_y << "]\n" <<
          "createNewWorld failed!\n";

        return false;
    }

    return true;
}

bool WorldEnvironment::createOuterWall()
{
    if(!wall_generator_.createWall(NodeType::OuterWall))
    {
        std::cout << "WorldEnvironment::createOuterWall :\n" <<
          "createWall failed!\n";

        return false;
    }

    return true;
}

bool WorldEnvironment::createInnerWall()
{
    if(!wall_generator_.createWall(NodeType::InnerWall))
    {
        std::cout << "WorldEnvironment::createInnerWall:\n" <<
          "createWall failed!\n";

        return false;
    }

    return true;
}

bool WorldEnvironment::addPointForOuterWall(
    const size_t& outerwall_idx,
    const float& point_x,
    const float& point_y)
{
    if(!wall_generator_.addPointForWall(
          NodeType::OuterWall,
          outerwall_idx,
          point_x,
          point_y))
    {
        std::cout << "WorldEnvironment::addPointForOuterWall :\n" <<
          "Input :\n" <<
          "\t outerwall_idx = " << outerwall_idx << std::endl <<
          "\t point = [" << point_x << "," <<
          point_y << "]\n" <<
          "addPointForWall failed!\n";

        return false;
    }

    return true;
}

bool WorldEnvironment::addPointForInnerWall(
    const size_t& innerwall_idx,
    const float& point_x,
    const float& point_y)
{
    if(!wall_generator_.addPointForWall(
          NodeType::InnerWall,
          innerwall_idx,
          point_x,
          point_y))
    {
        std::cout << "WorldEnvironment::addPointForInnerWall :\n" <<
          "Input :\n" <<
          "\t innerwall_idx = " << innerwall_idx << std::endl <<
          "\t point = [" << point_x << "," <<
          point_y << "]\n" <<
          "addPointForWall failed!\n";

        return false;
    }

    return true;
}

bool WorldEnvironment::generateWall()
{
    for(const EasyPolygon2D& outerwall_boundary_polygon : wall_generator_.outerwall_vec_)
    {
        if(!world_place_generator_.generateOuterWall(
              world_controller_,
              "Auto Generate OuterWall",
              outerwall_boundary_polygon))
        {
            std::cout << "WorldEnvironment::generateWall :\n" <<
              "generateOuterWall failed!\n";

            return false;
        }
    }

    for(const EasyPolygon2D& innerwall_boundary_polygon : wall_generator_.innerwall_vec_)
    {
        if(!world_place_generator_.generateInnerWall(
              world_controller_,
              "Auto Generate InnerWall",
              innerwall_boundary_polygon))
        {
            std::cout << "WorldEnvironment::generateWall :\n" <<
              "generateInnerWall failed!\n";

            return false;
        }
    }

    return true;
}

bool WorldEnvironment::placeOuterWallRoomContainer(
    const size_t &wall_id,
    const size_t &boundary_idx,
    const float &roomcontainer_start_position,
    const float &roomcontainer_width,
    const float &roomcontainer_height,
    const size_t &room_num)
{
    std::vector<std::string> room_name_vec(room_num, "Auto Generate Room");

    if(!world_place_generator_.placeWallRoomContainer(
          world_controller_,
          wall_id,
          NodeType::OuterWall,
          boundary_idx,
          roomcontainer_start_position,
          roomcontainer_width,
          roomcontainer_height,
          room_num,
          room_name_vec))
    {
        std::cout << "WorldEnvironment::placeOuterWallRoomContainer :\n" <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]\n" <<
          "\troom_num = " << room_num << std::endl <<
          "placeWallRoomContainer failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldEnvironment::placeInnerWallRoomContainer(
    const size_t &wall_id,
    const size_t &boundary_idx,
    const float &roomcontainer_start_position,
    const float &roomcontainer_width,
    const float &roomcontainer_height,
    const size_t &room_num)
{
    std::vector<std::string> room_name_vec(room_num, "Auto Generate Room");

    if(!world_place_generator_.placeWallRoomContainer(
          world_controller_,
          wall_id,
          NodeType::InnerWall,
          boundary_idx,
          roomcontainer_start_position,
          roomcontainer_width,
          roomcontainer_height,
          room_num,
          room_name_vec))
    {
        std::cout << "WorldEnvironment::placeInnerWallRoomContainer :\n" <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]\n" <<
          "\troom_num = " << room_num << std::endl <<
          "placeWallRoomContainer failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldEnvironment::generateFreeRoomContainer(
    const size_t &team_x_direction_person_num,
    const size_t &team_y_direction_person_num,
    const float &team_dist,
    const float &person_edge)
{
    if(!world_place_generator_.generateFreeRoomContainer(
          world_controller_,
          team_x_direction_person_num,
          team_y_direction_person_num,
          team_dist,
          person_edge))
    {
        std::cout << "WorldEnvironment::generateFreeRoomContainer :\n" <<
          "Input :\n" <<
          "\t team_person_num_size = [" << team_x_direction_person_num << "," <<
          team_y_direction_person_num << "]\n" <<
          "\t team_dist = " << team_dist << std::endl <<
          "\t person_edge = " << person_edge << std::endl <<
          "generateFreeRoomContainer failed!\n";

        return false;
    }

    return true;
}

bool WorldEnvironment::setWallRoomContainerPosition(
    const size_t &wall_roomcontainer_id,
    const float &new_position_x,
    const float &new_position_y,
    const float &mouse_pos_x_direction_delta)
{
    if(!world_editor_.setWallRoomContainerPosition(
          world_controller_,
          world_place_generator_,
          wall_roomcontainer_id,
          new_position_x,
          new_position_y,
          mouse_pos_x_direction_delta))
    {
        std::cout << "WorldEnvironment::setWallRoomContainerPosition :\n" <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]\n" <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "setWallRoomContainerPosition failed!" << std::endl;

        return false;
    }

    return true;
}

