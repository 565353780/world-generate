#include "WorldPlaceGenerator.h"

bool WorldPlaceGenerator::reset()
{
    if(!boundary_line_manager_.reset())
    {
        std::cout << "WorldPlaceGenerator::reset : " <<
          "reset for boundary_line_manager_ failed!" << std::endl;

        return false;
    }

    if(!point_matrix_.reset())
    {
        std::cout << "WorldPlaceGenerator::reset : " <<
          "reset for point_matrix_ failed!" << std::endl;

        return false;
    }

    free_room_error_max_ = 1;

    current_new_innerwall_id_ = 0;
    current_new_outerwall_id_ = 0;
    current_new_room_id_ = 0;

    team_x_direction_person_num_ = 0;
    team_y_direction_person_num_ = 0;
    team_dist_ = -1;
    person_edge_ = -1;

    return true;
}

bool WorldPlaceGenerator::resetButRemainWall(
    WorldController &world_controller)
{
    if(!world_controller.resetButRemainWall())
    {
        std::cout << "WorldPlaceGenerator::resetButRemainWall : " << std::endl <<
          "resetButRemainWall failed!" << std::endl;

        return false;
    }

    if(!boundary_line_manager_.reset())
    {
        std::cout << "WorldPlaceGenerator::resetButRemainWall : " <<
          "reset for boundary_line_manager_ failed!" << std::endl;

        return false;
    }

    current_new_room_id_ = 0;

    team_x_direction_person_num_ = 0;
    team_y_direction_person_num_ = 0;
    team_dist_ = -1;
    person_edge_ = -1;

    return true;
}

bool WorldPlaceGenerator::createNewWorld(
    WorldController &world_controller,
    const float &world_center_x,
    const float &world_center_y)
{
    if(!world_controller.reset())
    {
        std::cout << "WorldPlaceGenerator::createNewWorld : " << std::endl <<
          "\tworld_center = [" << world_center_x << "," <<
          world_center_y << "]" << std::endl <<
          "reset for world_controller failed!" << std::endl;

        return false;
    }

    if(!world_controller.createWorld("World", world_center_x, world_center_y))
    {
        std::cout << "WorldPlaceGenerator::createNewWorld : " << std::endl <<
          "\tworld_center = [" << world_center_x << "," <<
          world_center_y << "]" << std::endl <<
          "createWorld failed!" << std::endl;

        return false;
    }

    if(!boundary_line_manager_.reset())
    {
        std::cout << "WorldPlaceGenerator::createNewWorld : " << std::endl <<
          "\tworld_center = [" << world_center_x << "," <<
          world_center_y << "]" << std::endl <<
          "reset for boundary_line_manager_ failed!" << std::endl;

        return false;
    }

    current_new_innerwall_id_ = 0;
    current_new_outerwall_id_ = 0;
    current_new_room_id_ = 0;

    return true;
}

bool WorldPlaceGenerator::generateWall(
    WorldController &world_controller,
    const std::string &wall_name,
    const NodeType &wall_type,
    const EasyPolygon2D &wall_polygon)
{
    EasyAxis2D wall_axis_in_parent;
    wall_axis_in_parent.setCenter(0, 0);
    wall_axis_in_parent.setXDirection(1, 0);

    if(!world_controller.createWallForWorld(
          wall_name,
          wall_axis_in_parent,
          wall_type,
          wall_polygon))
    {
        std::cout << "WorldPlaceGenerator::generateWall : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "createWallForWorld failed!" << std::endl;

        return false;
    }

    if(wall_type == NodeType::OuterWall)
    {
        outerwall_boundary_polygon_ = wall_polygon;
        is_outerwall_boundary_polygon_set_ = true;

        if(!point_matrix_.setSplitEdgeLength(free_room_error_max_))
        {
            std::cout << "WorldPlaceGenerator::generateWall : " << std::endl <<
              "Input :\n" <<
              "\twall_name = " << wall_name << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "setSplitEdgeLength failed!" << std::endl;

            return false;
        }

        if(!point_matrix_.setBoundaryPolygon(wall_polygon))
        {
            std::cout << "WorldPlaceGenerator::generateWall : " << std::endl <<
              "Input :\n" <<
              "\twall_name = " << wall_name << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "setBoundaryPolygon failed!" << std::endl;

            return false;
        }

        if(!boundary_line_manager_.addBoundaryPolygon(
              current_new_outerwall_id_, wall_type, wall_polygon))
        {
            std::cout << "WorldPlaceGenerator::generateWall : " << std::endl <<
              "Input :\n" <<
              "\twall_name = " << wall_name << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "addBoundaryPolygon failed!" << std::endl;

            return false;
        }

        ++current_new_outerwall_id_;

        return true;
    }

    if(!boundary_line_manager_.addBoundaryPolygon(
          current_new_innerwall_id_, wall_type, wall_polygon))
    {
        std::cout << "WorldPlaceGenerator::generateWall : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "addBoundaryPolygon failed!" << std::endl;

        return false;
    }

    ++current_new_innerwall_id_;

    return true;
}

bool WorldPlaceGenerator::generateOuterWall(
    WorldController &world_controller,
    const std::string &wall_name,
    const EasyPolygon2D &wall_polygon)
{
    EasyAxis2D wall_axis_in_parent;
    wall_axis_in_parent.setCenter(0, 0);
    wall_axis_in_parent.setXDirection(1, 0);

    if(!generateWall(
          world_controller,
          wall_name,
          NodeType::OuterWall,
          wall_polygon))
    {
        std::cout << "WorldPlaceGenerator::generateOuterWall : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "generateWall failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldPlaceGenerator::generateInnerWall(
    WorldController &world_controller,
    const std::string &wall_name,
    const EasyPolygon2D &wall_polygon)
{
    EasyAxis2D wall_axis_in_parent;
    wall_axis_in_parent.setCenter(0, 0);
    wall_axis_in_parent.setXDirection(1, 0);

    if(!generateWall(
          world_controller,
          wall_name,
          NodeType::InnerWall,
          wall_polygon))
    {
        std::cout << "WorldPlaceGenerator::generateInnerWall : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "generateWall failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldPlaceGenerator::generateWorld(
    WorldController &world_controller)
{
    if(!world_controller.resetButRemainWall())
    {
        std::cout << "WorldPlaceGenerator::generateWorld : " << std::endl <<
          "resetButRemainWall failed!" << std::endl;

        return false;
    }

    if(!boundary_line_manager_.reset())
    {
        std::cout << "WorldPlaceGenerator::generateWorld : " << std::endl <<
          "reset for boundary_line_manager_ failed!" << std::endl;

        return false;
    }

    current_new_room_id_ = 0;

    if(!generateRoom(world_controller))
    {
        std::cout << "WorldPlaceGenerator::generateWorld : " << std::endl <<
          "generateRoom failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldPlaceGenerator::placeWallRoomContainer(
    WorldController &world_controller,
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &boundary_idx,
    const float &roomcontainer_start_position,
    const float &roomcontainer_width,
    const float &roomcontainer_height,
    const size_t &room_num,
    const std::vector<std::string> &room_name_vec)
{
    const float door_width = 1.5;
    const float window_width_scale = 0.7;
    const float person_edge = 2.0;
    const float team_dist = 3.0 * person_edge;

    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "\troom_num = " << room_num << std::endl <<
          "wall_type is not the wall type!" << std::endl;

        return false;
    }

    if(room_num == 0)
    {
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "\troom_num = " << room_num << std::endl <<
          "room_num not valid!" << std::endl;

        return false;
    }

    if(room_name_vec.size() != room_num)
    {
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "\troom_num = " << room_num << std::endl <<
          "room_name_vec size != room_num!" << std::endl;

        return false;
    }

    BoundaryLine new_boundary_line;
    new_boundary_line.line_start_position = roomcontainer_start_position;
    new_boundary_line.line_end_position = roomcontainer_start_position + roomcontainer_width;
    new_boundary_line.line_width = roomcontainer_width;
    new_boundary_line.line_height = roomcontainer_height;
    new_boundary_line.line_room_num = room_num;
    new_boundary_line.room_name_vec = room_name_vec;

    BoundaryLine valid_boundary_line;

    std::cout << "IN1-1" << std::endl;
    if(!boundary_line_manager_.insertBoundaryLine(
          wall_id,
          wall_type,
          boundary_idx,
          new_boundary_line,
          valid_boundary_line))
    {
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "\troom_num = " << room_num << std::endl <<
          "insertBoundaryLine for new boundary line failed!" << std::endl;

        return false;
    }

    std::cout << "IN1-2" << std::endl;
    if(valid_boundary_line.line_real_height < 0)
    {
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "\troom_num = " << room_num << std::endl <<
          "valid boundary line real height not valid!" << std::endl;

        return false;
    }

    const float valid_roomcontainer_start_position = valid_boundary_line.line_start_position;
    const float valid_roomcontainer_width = valid_boundary_line.line_end_position - valid_boundary_line.line_start_position;
    const float valid_roomcontainer_height = valid_boundary_line.line_real_height;

    if(valid_roomcontainer_width < 0 || valid_roomcontainer_height < 0)
    {
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "\troom_num = " << room_num << std::endl <<
          "valid roomcontainer size not valid!" << std::endl;

        return false;
    }

    if(valid_roomcontainer_width == 0 || valid_roomcontainer_height == 0)
    {
        // std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
        //   "Input :\n" <<
        //   "\tboundary_idx = " << boundary_idx << std::endl <<
        //   "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
        //   "\troomcontainer_size = [" << roomcontainer_width << "," <<
        //   roomcontainer_height << "]" << std::endl <<
        //   "\troom_num = " << room_num << std::endl <<
        //   "valid roomcontainer area = 0!" << std::endl;

        return true;
    }

    EasyAxis2D roomcontainer_axis;
    roomcontainer_axis.setXDirection(1, 0);
    roomcontainer_axis.setCenter(valid_roomcontainer_start_position, 0);

    if(!world_controller.createWallRoomContainerForWall(
          "Auto Generate Wall RoomContainer",
          room_name_vec,
          0,
          NodeType::OuterWall,
          boundary_idx,
          valid_roomcontainer_width,
          valid_roomcontainer_height,
          roomcontainer_axis,
          room_num))
    {
        std::cout << "valid roomcontainer size = " << valid_roomcontainer_width << "," <<
          valid_roomcontainer_height << std::endl;
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "\troom_num = " << room_num << std::endl <<
          "createWallRoomContainerForWall failed!" << std::endl;

        return false;
    }

    const float room_width = 1.0 * valid_roomcontainer_width / room_num;
    const float room_height = valid_roomcontainer_height;

    const float window_width = window_width_scale * room_width;

    size_t person_x_direction_num = 0;
    size_t person_y_direction_num = 0;

    if(room_width >= team_dist)
    {
        person_x_direction_num = size_t((room_width - 0.5 * team_dist) / person_edge);

        if(person_x_direction_num == 0)
        {
            person_x_direction_num = 1;
        }
    }
    if(room_height >= team_dist)
    {
        person_y_direction_num = size_t((room_height - 0.5 * team_dist) / person_edge);

        if(person_y_direction_num == 0)
        {
            person_y_direction_num = 1;
        }
    }

    if(person_x_direction_num == 0 || person_y_direction_num == 0)
    {
        current_new_room_id_ += room_num;

        return true;
    }

    const float team_width = 1.0 * person_x_direction_num * person_edge;
    const float team_height = 1.0 * person_y_direction_num * person_edge;

    const float team_center_x = (room_width - team_width) / 2.0;
    const float team_center_y = (room_height - team_height) / 2.0;

    EasyAxis2D door_axis;
    EasyAxis2D window_axis;
    EasyAxis2D team_axis;
    door_axis.setXDirection(1, 0);
    window_axis.setXDirection(1, 0);
    team_axis.setXDirection(1, 0);

    size_t wall_boundary_line_list_idx;
    if(!boundary_line_manager_.getWallBoundaryLineListIdx(
          wall_id, wall_type, wall_boundary_line_list_idx))
    {
        std::cout << "valid roomcontainer size = " << valid_roomcontainer_width << "," <<
          valid_roomcontainer_height << std::endl;
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "\troom_num = " << room_num << std::endl <<
          "getWallBoundaryLineListIdx failed!" << std::endl;

        return false;
    }

    const WallBoundaryLineList &wall_boundary_line_list =
      boundary_line_manager_.wall_boundary_line_list_vec_[wall_boundary_line_list_idx];

    const float &boundary_length =
      wall_boundary_line_list.boundary_line_list_vec_[boundary_idx].boundary_length_;
    window_axis.setCenter((room_width - window_width) / 2.0, 0);
    team_axis.setCenter(team_center_x, team_center_y);

    std::vector<std::vector<std::string>> person_name_matrix;
    person_name_matrix.resize(person_x_direction_num);
    for(std::vector<std::string> &person_name_row : person_name_matrix)
    {
        person_name_row.resize(person_y_direction_num, "Auto Generate Person");
    }

    std::vector<std::vector<std::string>> furniture_name_matrix;
    furniture_name_matrix.resize(person_x_direction_num);
    for(std::vector<std::string> &furniture_name_row : furniture_name_matrix)
    {
        furniture_name_row.resize(person_y_direction_num, "Auto Generate Furniture");
    }

    for(size_t i = 0; i < room_num; ++i)
    {
        const bool is_face_horizontal = (std::rand() % 2) == 1;

        // if(!world_controller.createTeamForRoom(
              // "Auto Generate Team",
              // person_name_matrix,
              // furniture_name_matrix,
              // current_new_room_id_,
              // NodeType::WallRoom,
              // team_width,
              // team_height,
              // team_axis,
              // person_x_direction_num,
              // person_y_direction_num,
              // false))
        // {
            // std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
              // "Input :\n" <<
              // "\twall_id = " << wall_id << std::endl <<
              // "\twall_type = " << wall_type << std::endl <<
              // "\tboundary_idx = " << boundary_idx << std::endl <<
              // "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
              // "\troomcontainer_size = [" << roomcontainer_width << "," <<
              // roomcontainer_height << "]" << std::endl <<
              // "\troom_num = " << room_num << std::endl <<
              // "createTeamForRoom failed!" << std::endl;
//
            // return false;
        // }

        const float room_center_position = valid_roomcontainer_start_position +
          (1.0 * i + 0.5) * room_width;
        bool is_handle_on_right_from_outside;

        if(room_center_position < 0.5 * boundary_length)
        {
            door_axis.setCenter(0.1 * (room_width - door_width), 0);
            is_handle_on_right_from_outside = true;
        }
        else
        {
            door_axis.setCenter(0.9 * (room_width - door_width), 0);
            is_handle_on_right_from_outside = false;
        }

        if(!world_controller.createWindowForRoom(
              "Auto Generate Window",
              current_new_room_id_,
              NodeType::WallRoom,
              0,
              window_width,
              window_axis))
        {
            std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
              "Input :\n" <<
              "\twall_id = " << wall_id << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "\tboundary_idx = " << boundary_idx << std::endl <<
              "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
              "\troomcontainer_size = [" << roomcontainer_width << "," <<
              roomcontainer_height << "]" << std::endl <<
              "\troom_num = " << room_num << std::endl <<
              "createWindowForRoom failed!" << std::endl;

            return false;
        }

        if(!world_controller.createDoorForRoom(
              "Auto Generate Door",
              current_new_room_id_,
              NodeType::WallRoom,
              2,
              door_width,
              door_axis,
              is_handle_on_right_from_outside))
        {
            std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
              "Input :\n" <<
              "\twall_id = " << wall_id << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "\tboundary_idx = " << boundary_idx << std::endl <<
              "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
              "\troomcontainer_size = [" << roomcontainer_width << "," <<
              roomcontainer_height << "]" << std::endl <<
              "\troom_num = " << room_num << std::endl <<
              "createDoorForRoom failed!" << std::endl;

            return false;
        }

        ++current_new_room_id_;
    }

    return true;
}

bool WorldPlaceGenerator::placeWallRoomContainer(
    WorldController &world_controller,
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &boundary_idx,
    const float &roomcontainer_start_position,
    const float &roomcontainer_width,
    const float &roomcontainer_height)
{
    size_t room_num = size_t(1.0 * roomcontainer_width / roomcontainer_height);
    if(room_num == 0)
    {
        room_num = 1;
    }

    std::vector<std::string> room_name_vec;
    room_name_vec.resize(room_num, "Auto Generate WallRoom");

    if(!placeWallRoomContainer(
          world_controller,
          wall_id,
          wall_type,
          boundary_idx,
          roomcontainer_start_position,
          roomcontainer_width,
          roomcontainer_height,
          room_num,
          room_name_vec))
    {
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "createDoorForRoom failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldPlaceGenerator::generateFreeRoomContainer(
    WorldController &world_controller,
    const size_t &team_x_direction_person_num,
    const size_t &team_y_direction_person_num,
    const float &team_dist,
    const float &person_edge)
{
    team_x_direction_person_num_ = team_x_direction_person_num;
    team_y_direction_person_num_ = team_y_direction_person_num;
    team_dist_ = team_dist;
    person_edge_ = person_edge;

    if(!point_matrix_.setAllPointOccupancyState(PointOccupancyState::PointFree))
    {
        std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
          team_y_direction_person_num << "]" << std::endl <<
          "\tteam_dist = " << team_dist << std::endl <<
          "\tperson_edge = " << person_edge << std::endl <<
          "setAllPointOccupancyState failed!" << std::endl;

        return false;
    }

    EasyNode* wall_node = world_controller.findNode(0, NodeType::OuterWall);

    if(wall_node == nullptr)
    {
        std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
          team_y_direction_person_num << "]" << std::endl <<
          "\tteam_dist = " << team_dist << std::endl <<
          "\tperson_edge = " << person_edge << std::endl <<
          "find wall node failed!" << std::endl;

        return false;
    }

    std::vector<EasyPolygon2D> polygon_vec_in_wall_node;

    std::vector<EasyNode*> roomcontainer_node_vec;
    world_controller.getRoomContainerNodeVec(roomcontainer_node_vec);

    for(EasyNode* roomcontainer_node : roomcontainer_node_vec)
    {
        EasyNode* roomcontainer_space_node = roomcontainer_node->findChild(0, NodeType::Space);

        if(roomcontainer_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &roomcontainer_space_polygon =
          roomcontainer_space_node->getBoundaryPolygon();

        EasyPolygon2D roomcontainer_polygon_in_wall_node;

        for(const EasyPoint2D &roomcontainer_boundary_point : roomcontainer_space_polygon.point_list)
        {
            EasyPoint2D roomcontainer_boundary_point_in_world;

            if(!roomcontainer_space_node->getPointInWorld(
                  roomcontainer_boundary_point,
                  roomcontainer_boundary_point_in_world))
            {
                std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
                  "Input :\n" <<
                  "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
                  team_y_direction_person_num << "]" << std::endl <<
                  "\tteam_dist = " << team_dist << std::endl <<
                  "\tperson_edge = " << person_edge << std::endl <<
                  "getPointInWorld failed!" << std::endl;

                return false;
            }

            EasyPoint2D roomcontainer_boundary_point_in_wall_node;

            if(!wall_node->getPointInNode(
                  roomcontainer_boundary_point_in_world,
                  roomcontainer_boundary_point_in_wall_node))
            {
                std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
                  "Input :\n" <<
                  "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
                  team_y_direction_person_num << "]" << std::endl <<
                  "\tteam_dist = " << team_dist << std::endl <<
                  "\tperson_edge = " << person_edge << std::endl <<
                  "getPointInNode failed!" << std::endl;

                return false;
            }

            roomcontainer_polygon_in_wall_node.addPoint(roomcontainer_boundary_point_in_wall_node);
        }

        polygon_vec_in_wall_node.emplace_back(roomcontainer_polygon_in_wall_node);
    }

    for(const EasyPolygon2D &polygon_in_wall_node : polygon_vec_in_wall_node)
    {
        const float &boundary_polygon_x_min = polygon_in_wall_node.rect.x_min;
        const float &boundary_polygon_y_min = polygon_in_wall_node.rect.y_min;
        const float &boundary_polygon_width = polygon_in_wall_node.rect.x_diff;
        const float &boundary_polygon_height = polygon_in_wall_node.rect.y_diff;

        if(!point_matrix_.setRectPointOccupancyState(
              boundary_polygon_x_min,
              boundary_polygon_y_min,
              boundary_polygon_width,
              boundary_polygon_height,
              PointOccupancyState::PointUsed))
        {
            std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
              "Input :\n" <<
              "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
              team_y_direction_person_num << "]" << std::endl <<
              "\tteam_dist = " << team_dist << std::endl <<
              "\tperson_edge = " << person_edge << std::endl <<
              "setRectPointOccupancyState failed!" << std::endl;

            return false;
        }
    }

    for(size_t i = 0; i < outerwall_boundary_polygon_.point_list.size(); ++i)
    {
        const EasyPoint2D &current_point = outerwall_boundary_polygon_.point_list[i];
        const EasyPoint2D &next_point = outerwall_boundary_polygon_.point_list[
          (i + 1) % outerwall_boundary_polygon_.point_list.size()];

        EasyPolygon2D new_boundary_line_polygon;
        new_boundary_line_polygon.addPoint(current_point);
        new_boundary_line_polygon.addPoint(next_point);

        polygon_vec_in_wall_node.emplace_back(new_boundary_line_polygon);
    }

    size_t current_freeroom_id_start = 0;
    bool is_new_roomcontainer_valid = true;

    while(is_new_roomcontainer_valid)
    {
        is_new_roomcontainer_valid = false;

        float max_free_roomcontainer_start_position_x;
        float max_free_roomcontainer_start_position_y;
        float max_free_roomcontainer_width;
        float max_free_roomcontainer_height;

        if(!point_matrix_.getMaxFreeRect(
              polygon_vec_in_wall_node,
              max_free_roomcontainer_start_position_x,
              max_free_roomcontainer_start_position_y,
              max_free_roomcontainer_width,
              max_free_roomcontainer_height))
        {
            // std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
            //   "Input :\n" <<
            //   "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
            //   team_y_direction_person_num << "]" << std::endl <<
            //   "\tteam_dist = " << team_dist << std::endl <<
            //   "\tperson_edge = " << person_edge << std::endl <<
            //   "getMaxFreeRect failed!" << std::endl;

            continue;
        }

        size_t x_direction_room_num = 
          max_free_roomcontainer_width / (team_x_direction_person_num * person_edge + team_dist);

        size_t y_direction_room_num = 
          max_free_roomcontainer_height / (team_y_direction_person_num * person_edge + team_dist);

        if(x_direction_room_num == 0)
        {
            x_direction_room_num = 1;
        }
        if(y_direction_room_num == 0)
        {
            y_direction_room_num = 1;
        }

        const float room_width = max_free_roomcontainer_width / x_direction_room_num;
        const float room_height = max_free_roomcontainer_height / y_direction_room_num;

        size_t person_x_direction_num = 0;
        size_t person_y_direction_num = 0;

        if(room_width >= team_dist)
        {
            person_x_direction_num = size_t((room_width - team_dist) / person_edge);

            if(person_x_direction_num == 0)
            {
                ++person_x_direction_num;
            }
        }
        if(room_height >= team_dist)
        {
            person_y_direction_num = size_t((room_height - team_dist) / person_edge);

            if(person_y_direction_num == 0)
            {
                ++person_y_direction_num;
            }
        }

        if(person_x_direction_num < 1 || person_y_direction_num < 1)
        {
            continue;
        }

        is_new_roomcontainer_valid = true;

        const bool is_face_horizontal = (std::rand() % 2) == 1;

        const float team_width = 1.0 * person_x_direction_num * person_edge;
        const float team_height = 1.0 * person_y_direction_num * person_edge;

        const float team_center_x = (room_width - team_width) / 2.0;
        const float team_center_y = (room_height - team_height) / 2.0;

        EasyAxis2D team_axis;
        team_axis.setXDirection(1, 0);
        team_axis.setCenter(team_center_x, team_center_y);

        EasyAxis2D room_axis;
        room_axis.setXDirection(1, 0);

        std::vector<std::string> free_name_vec;
        free_name_vec.resize(1);
        free_name_vec[0] = "Auto Generate FreeRoom";

        std::vector<std::vector<std::string>> person_name_matrix;
        person_name_matrix.resize(person_x_direction_num);
        for(std::vector<std::string> &person_name_row : person_name_matrix)
        {
            person_name_row.resize(person_y_direction_num, "Auto Generate Person");
        }

        std::vector<std::vector<std::string>> furniture_name_matrix;
        furniture_name_matrix.resize(person_x_direction_num);
        for(std::vector<std::string> &furniture_name_row : furniture_name_matrix)
        {
            furniture_name_row.resize(person_y_direction_num, "Auto Generate Person");
        }

        for(size_t i = 0; i < x_direction_room_num; ++i)
        {
            for(size_t j = 0; j < y_direction_room_num; ++j)
            {
                room_axis.setCenter(
                    max_free_roomcontainer_start_position_x + i * room_width,
                    max_free_roomcontainer_start_position_y + j * room_height);

                world_controller.createFreeRoomContainerForWall(
                    "Auto Generate Free RoomContainer",
                    free_name_vec,
                    0,
                    NodeType::OuterWall,
                    0,
                    room_width,
                    room_height,
                    room_axis,
                    1);

                world_controller.createTeamForRoom(
                    "Auto Generate Team",
                    person_name_matrix,
                    furniture_name_matrix,
                    current_freeroom_id_start,
                    NodeType::FreeRoom,
                    team_width,
                    team_height,
                    team_axis,
                    person_x_direction_num,
                    person_y_direction_num,
                    false);

                ++current_freeroom_id_start;
            }
        }

        EasyPolygon2D new_room_polygon;
        new_room_polygon.addPoint(
            max_free_roomcontainer_start_position_x,
            max_free_roomcontainer_start_position_y);
        new_room_polygon.addPoint(
            max_free_roomcontainer_start_position_x + max_free_roomcontainer_width,
            max_free_roomcontainer_start_position_y);
        new_room_polygon.addPoint(
            max_free_roomcontainer_start_position_x + max_free_roomcontainer_width,
            max_free_roomcontainer_start_position_y + max_free_roomcontainer_height);
        new_room_polygon.addPoint(
            max_free_roomcontainer_start_position_x,
            max_free_roomcontainer_start_position_y + max_free_roomcontainer_height);
        new_room_polygon.setAntiClockWise();
        polygon_vec_in_wall_node.emplace_back(new_room_polygon);

        if(!point_matrix_.setRectPointOccupancyState(
              max_free_roomcontainer_start_position_x,
              max_free_roomcontainer_start_position_y,
              max_free_roomcontainer_width,
              max_free_roomcontainer_height,
              PointOccupancyState::PointUsed))
        {
            std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
              "Input :\n" <<
              "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
              team_y_direction_person_num << "]" << std::endl <<
              "\tteam_dist = " << team_dist << std::endl <<
              "\tperson_edge = " << person_edge << std::endl <<
              "setRectPointOccupancyState failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool WorldPlaceGenerator::generateRoom(
    WorldController &world_controller)
{
    const size_t roomcontainer_num = 3;

    const float roomcontainer_width_min = 6;
    const float roomcontainer_width_max = 24;
    const float roomcontainer_height_min = 6;
    const float roomcontainer_height_max = 8;

    for(size_t i = 0; i < roomcontainer_num; ++i)
    {
        // const size_t random_wall_id = std::rand() % boundary_line_manager_.wall_boundary_line_list_vec_.size();
        const size_t random_wall_id = 0;
        NodeType random_wall_type = NodeType::OuterWall;

        size_t wall_boundary_line_list_idx;
        if(!boundary_line_manager_.getWallBoundaryLineListIdx(random_wall_id, random_wall_type, wall_boundary_line_list_idx))
        {
            std::cout << "WorldPlaceGenerator::generateRoom : " << std::endl <<
              "getWallBoundaryLineListIdx failed!" << std::endl;

            return false;
        }
        const WallBoundaryLineList &wall_boundary_line_list =
          boundary_line_manager_.wall_boundary_line_list_vec_[wall_boundary_line_list_idx];

        const size_t random_boundary_idx = std::rand() % wall_boundary_line_list.wall_boundary_polygon_.point_list.size();
        const float random_boundary_start_position = 1.0 * (std::rand() %
            size_t(wall_boundary_line_list.boundary_line_list_vec_[random_boundary_idx].boundary_length_));

        const float random_width =
          1.0 * (std::rand() % size_t(roomcontainer_width_max - roomcontainer_width_min)) + roomcontainer_width_min;
        const float random_height =
          1.0 * (std::rand() % size_t(roomcontainer_height_max - roomcontainer_height_min)) + roomcontainer_height_min;

        if(!placeWallRoomContainer(
              world_controller,
              0,
              NodeType::OuterWall,
              random_boundary_idx,
              random_boundary_start_position,
              random_width,
              random_height))
        {
            continue;
        }
    }

    if(!generateFreeRoomContainer(
          world_controller,
          team_x_direction_person_num_,
          team_y_direction_person_num_,
          team_dist_,
          person_edge_))
    {
        std::cout << "WorldPlaceGenerator::generateRoom : " << std::endl <<
          "generateFreeRoomContainer failed!" << std::endl;

        return false;
    }

    return true;
}

