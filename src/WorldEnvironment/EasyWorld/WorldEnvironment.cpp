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

std::vector<std::vector<float>> WorldEnvironment::getOuterWallBoundaryXYDataVec()
{
    std::vector<std::vector<float>> outerwall_boundary_xy_data_vec;

    if(!world_observation_.getOuterWallBoundaryPolygon(world_controller_))
    {
        std::cout << "WorldEnvironment::getOuterWallBoundaryXYData :\n" <<
          "getOuterWallBoundaryPolygon failed!\n";

        return outerwall_boundary_xy_data_vec;
    }

    const std::vector<EasyPolygon2D>& outerwall_boundary_polygon_vec =
      world_observation_.outerwall_boundary_polygon_vec_;

    if(outerwall_boundary_polygon_vec.size() == 0)
    {
        return outerwall_boundary_xy_data_vec;
    }

    outerwall_boundary_xy_data_vec.resize(outerwall_boundary_polygon_vec.size());

    for(size_t i = 0; i < outerwall_boundary_polygon_vec.size(); ++i)
    {
        std::vector<float>& outerwall_boundary_xy_data = outerwall_boundary_xy_data_vec[i];
        const EasyPolygon2D& outerwall_boundary_polygon = outerwall_boundary_polygon_vec[i];

        if(outerwall_boundary_polygon.point_list.size() == 0)
        {
            std::cout << "WorldEnvironment::getOuterWallBoundaryXYData :\n" <<
              "outerwall boundary polygon is empty!\n";

            continue;
        }

        outerwall_boundary_xy_data.resize(2 * outerwall_boundary_polygon.point_list.size(), 0);

        for(size_t j = 0; j < outerwall_boundary_polygon.point_list.size(); ++j)
        {
            const EasyPoint2D& outerwall_boundary_point = outerwall_boundary_polygon.point_list[j];

            outerwall_boundary_xy_data[2 * j] = outerwall_boundary_point.x;
            outerwall_boundary_xy_data[2 * j + 1] = outerwall_boundary_point.y;
        }
    }

    return outerwall_boundary_xy_data_vec;
}

std::vector<std::vector<float>> WorldEnvironment::getInnerWallBoundaryXYDataVec()
{
    std::vector<std::vector<float>> innerwall_boundary_xy_data_vec;

    if(!world_observation_.getInnerWallBoundaryPolygon(world_controller_))
    {
        std::cout << "WorldEnvironment::getInnerWallBoundaryXYData :\n" <<
          "getInnerWallBoundaryPolygon failed!\n";

        return innerwall_boundary_xy_data_vec;
    }

    const std::vector<EasyPolygon2D>& innerwall_boundary_polygon_vec =
      world_observation_.innerwall_boundary_polygon_vec_;

    if(innerwall_boundary_polygon_vec.size() == 0)
    {
        return innerwall_boundary_xy_data_vec;
    }

    innerwall_boundary_xy_data_vec.resize(innerwall_boundary_polygon_vec.size());

    for(size_t i = 0; i < innerwall_boundary_polygon_vec.size(); ++i)
    {
        std::vector<float>& innerwall_boundary_xy_data = innerwall_boundary_xy_data_vec[i];
        const EasyPolygon2D& innerwall_boundary_polygon = innerwall_boundary_polygon_vec[i];

        if(innerwall_boundary_polygon.point_list.size() == 0)
        {
            std::cout << "WorldEnvironment::getInnerWallBoundaryXYData :\n" <<
              "innerwall boundary polygon is empty!\n";

            continue;
        }

        innerwall_boundary_xy_data.resize(2 * innerwall_boundary_polygon.point_list.size(), 0);

        for(size_t j = 0; j < innerwall_boundary_polygon.point_list.size(); ++j)
        {
            const EasyPoint2D& innerwall_boundary_point = innerwall_boundary_polygon.point_list[j];

            innerwall_boundary_xy_data[2 * j] = innerwall_boundary_point.x;
            innerwall_boundary_xy_data[2 * j + 1] = innerwall_boundary_point.y;
        }
    }

    return innerwall_boundary_xy_data_vec;
}

std::vector<std::vector<float>> WorldEnvironment::getRoomContainerBoundaryXYDataVec()
{
    std::vector<std::vector<float>> roomcontainer_boundary_xy_data_vec;

    if(!world_observation_.getRoomContainerBoundaryPolygon(world_controller_))
    {
        std::cout << "WorldEnvironment::getRoomContainerBoundaryXYData :\n" <<
          "getRoomContainerBoundaryPolygon failed!\n";

        return roomcontainer_boundary_xy_data_vec;
    }

    const std::vector<EasyPolygon2D>& roomcontainer_boundary_polygon_vec =
      world_observation_.roomcontainer_boundary_polygon_vec_;

    if(roomcontainer_boundary_polygon_vec.size() == 0)
    {
        return roomcontainer_boundary_xy_data_vec;
    }

    roomcontainer_boundary_xy_data_vec.resize(roomcontainer_boundary_polygon_vec.size());

    for(size_t i = 0; i < roomcontainer_boundary_polygon_vec.size(); ++i)
    {
        std::vector<float>& roomcontainer_boundary_xy_data = roomcontainer_boundary_xy_data_vec[i];
        const EasyPolygon2D& roomcontainer_boundary_polygon = roomcontainer_boundary_polygon_vec[i];

        if(roomcontainer_boundary_polygon.point_list.size() == 0)
        {
            std::cout << "WorldEnvironment::getRoomContainerBoundaryXYData :\n" <<
              "roomcontainer boundary polygon is empty!\n";

            continue;
        }

        roomcontainer_boundary_xy_data.resize(2 * roomcontainer_boundary_polygon.point_list.size(), 0);

        for(size_t j = 0; j < roomcontainer_boundary_polygon.point_list.size(); ++j)
        {
            const EasyPoint2D& roomcontainer_boundary_point = roomcontainer_boundary_polygon.point_list[j];

            roomcontainer_boundary_xy_data[2 * j] = roomcontainer_boundary_point.x;
            roomcontainer_boundary_xy_data[2 * j + 1] = roomcontainer_boundary_point.y;
        }
    }

    return roomcontainer_boundary_xy_data_vec;
}

std::vector<std::vector<float>> WorldEnvironment::getWallRoomBoundaryXYDataVec()
{
    std::vector<std::vector<float>> wallroom_boundary_xy_data_vec;

    if(!world_observation_.getWallRoomBoundaryPolygon(world_controller_))
    {
        std::cout << "WorldEnvironment::getWallRoomBoundaryXYData :\n" <<
          "getWallRoomBoundaryPolygon failed!\n";

        return wallroom_boundary_xy_data_vec;
    }

    const std::vector<EasyPolygon2D>& wallroom_boundary_polygon_vec =
      world_observation_.wallroom_boundary_polygon_vec_;

    if(wallroom_boundary_polygon_vec.size() == 0)
    {
        return wallroom_boundary_xy_data_vec;
    }

    wallroom_boundary_xy_data_vec.resize(wallroom_boundary_polygon_vec.size());

    for(size_t i = 0; i < wallroom_boundary_polygon_vec.size(); ++i)
    {
        std::vector<float>& wallroom_boundary_xy_data = wallroom_boundary_xy_data_vec[i];
        const EasyPolygon2D& wallroom_boundary_polygon = wallroom_boundary_polygon_vec[i];

        if(wallroom_boundary_polygon.point_list.size() == 0)
        {
            std::cout << "WorldEnvironment::getWallRoomBoundaryXYData :\n" <<
              "wallroom boundary polygon is empty!\n";

            continue;
        }

        wallroom_boundary_xy_data.resize(2 * wallroom_boundary_polygon.point_list.size(), 0);

        for(size_t j = 0; j < wallroom_boundary_polygon.point_list.size(); ++j)
        {
            const EasyPoint2D& wallroom_boundary_point = wallroom_boundary_polygon.point_list[j];

            wallroom_boundary_xy_data[2 * j] = wallroom_boundary_point.x;
            wallroom_boundary_xy_data[2 * j + 1] = wallroom_boundary_point.y;
        }
    }

    return wallroom_boundary_xy_data_vec;
}

std::vector<std::vector<float>> WorldEnvironment::getFreeRoomBoundaryXYDataVec()
{
    std::vector<std::vector<float>> freeroom_boundary_xy_data_vec;

    if(!world_observation_.getFreeRoomBoundaryPolygon(world_controller_))
    {
        std::cout << "WorldEnvironment::getFreeRoomBoundaryXYData :\n" <<
          "getFreeRoomBoundaryPolygon failed!\n";

        return freeroom_boundary_xy_data_vec;
    }

    const std::vector<EasyPolygon2D>& freeroom_boundary_polygon_vec =
      world_observation_.freeroom_boundary_polygon_vec_;

    if(freeroom_boundary_polygon_vec.size() == 0)
    {
        return freeroom_boundary_xy_data_vec;
    }

    freeroom_boundary_xy_data_vec.resize(freeroom_boundary_polygon_vec.size());

    for(size_t i = 0; i < freeroom_boundary_polygon_vec.size(); ++i)
    {
        std::vector<float>& freeroom_boundary_xy_data = freeroom_boundary_xy_data_vec[i];
        const EasyPolygon2D& freeroom_boundary_polygon = freeroom_boundary_polygon_vec[i];

        if(freeroom_boundary_polygon.point_list.size() == 0)
        {
            std::cout << "WorldEnvironment::getFreeRoomBoundaryXYData :\n" <<
              "freeroom boundary polygon is empty!\n";

            continue;
        }

        freeroom_boundary_xy_data.resize(2 * freeroom_boundary_polygon.point_list.size(), 0);

        for(size_t j = 0; j < freeroom_boundary_polygon.point_list.size(); ++j)
        {
            const EasyPoint2D& freeroom_boundary_point = freeroom_boundary_polygon.point_list[j];

            freeroom_boundary_xy_data[2 * j] = freeroom_boundary_point.x;
            freeroom_boundary_xy_data[2 * j + 1] = freeroom_boundary_point.y;
        }
    }

    return freeroom_boundary_xy_data_vec;
}

std::vector<std::vector<float>> WorldEnvironment::getDoorBoundaryXYDataVec()
{
    std::vector<std::vector<float>> door_boundary_xy_data_vec;

    if(!world_observation_.getDoorBoundaryPolygon(world_controller_))
    {
        std::cout << "WorldEnvironment::getDoorBoundaryXYData :\n" <<
          "getDoorBoundaryPolygon failed!\n";

        return door_boundary_xy_data_vec;
    }

    const std::vector<EasyPolygon2D>& door_boundary_polygon_vec =
      world_observation_.door_boundary_polygon_vec_;

    if(door_boundary_polygon_vec.size() == 0)
    {
        return door_boundary_xy_data_vec;
    }

    door_boundary_xy_data_vec.resize(door_boundary_polygon_vec.size());

    for(size_t i = 0; i < door_boundary_polygon_vec.size(); ++i)
    {
        std::vector<float>& door_boundary_xy_data = door_boundary_xy_data_vec[i];
        const EasyPolygon2D& door_boundary_polygon = door_boundary_polygon_vec[i];

        if(door_boundary_polygon.point_list.size() == 0)
        {
            std::cout << "WorldEnvironment::getDoorBoundaryXYData :\n" <<
              "door boundary polygon is empty!\n";

            continue;
        }

        door_boundary_xy_data.resize(2 * door_boundary_polygon.point_list.size(), 0);

        for(size_t j = 0; j < door_boundary_polygon.point_list.size(); ++j)
        {
            const EasyPoint2D& door_boundary_point = door_boundary_polygon.point_list[j];

            door_boundary_xy_data[2 * j] = door_boundary_point.x;
            door_boundary_xy_data[2 * j + 1] = door_boundary_point.y;
        }
    }

    return door_boundary_xy_data_vec;
}

std::vector<std::vector<float>> WorldEnvironment::getWindowBoundaryXYDataVec()
{
    std::vector<std::vector<float>> window_boundary_xy_data_vec;

    if(!world_observation_.getWindowBoundaryPolygon(world_controller_))
    {
        std::cout << "WorldEnvironment::getWindowBoundaryXYData :\n" <<
          "getWindowBoundaryPolygon failed!\n";

        return window_boundary_xy_data_vec;
    }

    const std::vector<EasyPolygon2D>& window_boundary_polygon_vec =
      world_observation_.window_boundary_polygon_vec_;

    if(window_boundary_polygon_vec.size() == 0)
    {
        return window_boundary_xy_data_vec;
    }

    window_boundary_xy_data_vec.resize(window_boundary_polygon_vec.size());

    for(size_t i = 0; i < window_boundary_polygon_vec.size(); ++i)
    {
        std::vector<float>& window_boundary_xy_data = window_boundary_xy_data_vec[i];
        const EasyPolygon2D& window_boundary_polygon = window_boundary_polygon_vec[i];

        if(window_boundary_polygon.point_list.size() == 0)
        {
            std::cout << "WorldEnvironment::getWindowBoundaryXYData :\n" <<
              "window boundary polygon is empty!\n";

            continue;
        }

        window_boundary_xy_data.resize(2 * window_boundary_polygon.point_list.size(), 0);

        for(size_t j = 0; j < window_boundary_polygon.point_list.size(); ++j)
        {
            const EasyPoint2D& window_boundary_point = window_boundary_polygon.point_list[j];

            window_boundary_xy_data[2 * j] = window_boundary_point.x;
            window_boundary_xy_data[2 * j + 1] = window_boundary_point.y;
        }
    }

    return window_boundary_xy_data_vec;
}

std::vector<std::vector<float>> WorldEnvironment::getTeamBoundaryXYDataVec()
{
    std::vector<std::vector<float>> team_boundary_xy_data_vec;

    if(!world_observation_.getTeamBoundaryPolygon(world_controller_))
    {
        std::cout << "WorldEnvironment::getTeamBoundaryXYData :\n" <<
          "getTeamBoundaryPolygon failed!\n";

        return team_boundary_xy_data_vec;
    }

    const std::vector<EasyPolygon2D>& team_boundary_polygon_vec =
      world_observation_.team_boundary_polygon_vec_;

    if(team_boundary_polygon_vec.size() == 0)
    {
        return team_boundary_xy_data_vec;
    }

    team_boundary_xy_data_vec.resize(team_boundary_polygon_vec.size());

    for(size_t i = 0; i < team_boundary_polygon_vec.size(); ++i)
    {
        std::vector<float>& team_boundary_xy_data = team_boundary_xy_data_vec[i];
        const EasyPolygon2D& team_boundary_polygon = team_boundary_polygon_vec[i];

        if(team_boundary_polygon.point_list.size() == 0)
        {
            std::cout << "WorldEnvironment::getTeamBoundaryXYData :\n" <<
              "team boundary polygon is empty!\n";

            continue;
        }

        team_boundary_xy_data.resize(2 * team_boundary_polygon.point_list.size(), 0);

        for(size_t j = 0; j < team_boundary_polygon.point_list.size(); ++j)
        {
            const EasyPoint2D& team_boundary_point = team_boundary_polygon.point_list[j];

            team_boundary_xy_data[2 * j] = team_boundary_point.x;
            team_boundary_xy_data[2 * j + 1] = team_boundary_point.y;
        }
    }

    return team_boundary_xy_data_vec;
}

std::vector<std::vector<float>> WorldEnvironment::getPersonBoundaryXYDataVec()
{
    std::vector<std::vector<float>> person_boundary_xy_data_vec;

    if(!world_observation_.getPersonBoundaryPolygon(world_controller_))
    {
        std::cout << "WorldEnvironment::getPersonBoundaryXYData :\n" <<
          "getPersonBoundaryPolygon failed!\n";

        return person_boundary_xy_data_vec;
    }

    const std::vector<EasyPolygon2D>& person_boundary_polygon_vec =
      world_observation_.person_boundary_polygon_vec_;

    if(person_boundary_polygon_vec.size() == 0)
    {
        return person_boundary_xy_data_vec;
    }

    person_boundary_xy_data_vec.resize(person_boundary_polygon_vec.size());

    for(size_t i = 0; i < person_boundary_polygon_vec.size(); ++i)
    {
        std::vector<float>& person_boundary_xy_data = person_boundary_xy_data_vec[i];
        const EasyPolygon2D& person_boundary_polygon = person_boundary_polygon_vec[i];

        if(person_boundary_polygon.point_list.size() == 0)
        {
            std::cout << "WorldEnvironment::getPersonBoundaryXYData :\n" <<
              "person boundary polygon is empty!\n";

            continue;
        }

        person_boundary_xy_data.resize(2 * person_boundary_polygon.point_list.size(), 0);

        for(size_t j = 0; j < person_boundary_polygon.point_list.size(); ++j)
        {
            const EasyPoint2D& person_boundary_point = person_boundary_polygon.point_list[j];

            person_boundary_xy_data[2 * j] = person_boundary_point.x;
            person_boundary_xy_data[2 * j + 1] = person_boundary_point.y;
        }
    }

    return person_boundary_xy_data_vec;
}

std::vector<std::vector<float>> WorldEnvironment::getFurnitureBoundaryXYDataVec()
{
    std::vector<std::vector<float>> furniture_boundary_xy_data_vec;

    if(!world_observation_.getFurnitureBoundaryPolygon(world_controller_))
    {
        std::cout << "WorldEnvironment::getFurnitureBoundaryXYData :\n" <<
          "getFurnitureBoundaryPolygon failed!\n";

        return furniture_boundary_xy_data_vec;
    }

    const std::vector<EasyPolygon2D>& furniture_boundary_polygon_vec =
      world_observation_.furniture_boundary_polygon_vec_;

    if(furniture_boundary_polygon_vec.size() == 0)
    {
        return furniture_boundary_xy_data_vec;
    }

    furniture_boundary_xy_data_vec.resize(furniture_boundary_polygon_vec.size());

    for(size_t i = 0; i < furniture_boundary_polygon_vec.size(); ++i)
    {
        std::vector<float>& furniture_boundary_xy_data = furniture_boundary_xy_data_vec[i];
        const EasyPolygon2D& furniture_boundary_polygon = furniture_boundary_polygon_vec[i];

        if(furniture_boundary_polygon.point_list.size() == 0)
        {
            std::cout << "WorldEnvironment::getFurnitureBoundaryXYData :\n" <<
              "furniture boundary polygon is empty!\n";

            continue;
        }

        furniture_boundary_xy_data.resize(2 * furniture_boundary_polygon.point_list.size(), 0);

        for(size_t j = 0; j < furniture_boundary_polygon.point_list.size(); ++j)
        {
            const EasyPoint2D& furniture_boundary_point = furniture_boundary_polygon.point_list[j];

            furniture_boundary_xy_data[2 * j] = furniture_boundary_point.x;
            furniture_boundary_xy_data[2 * j + 1] = furniture_boundary_point.y;
        }
    }

    return furniture_boundary_xy_data_vec;
}

