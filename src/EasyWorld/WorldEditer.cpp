#include "WorldEditer.h"

bool WorldData::reset()
{
    world_center_x = 0;
    world_center_y = 0;

    return true;
}

bool WorldData::outputInfo(
    const size_t &info_level)
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << "WorldData : " << std::endl <<
      "\tworld_center = [" << world_center_x << "," <<
      world_center_y << "]" << std::endl;

    return true;
}

bool WallData::reset()
{
    id = 0;
    type = NodeType::NodeFree;
    boundary_polygon.reset();

    return true;
}

bool WallData::outputInfo(
    const size_t &info_level)
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "WallData : " << std::endl <<
      line_start << "\tid = " << id << std::endl <<
      line_start << "\ttype = " << type << std::endl;

    return true;
}

bool WallRoomContainerData::reset()
{
    wall_id = 0;
    wall_type = NodeType::NodeFree;
    on_wall_boundary_idx = 0;
    on_wall_boundary_start_position = -1;
    target_width = -1;
    real_width = -1;
    target_height = -1;
    real_height = -1;

    return true;
}

bool WallRoomContainerData::outputInfo(
    const size_t &info_level)
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "WallRoomContainerData : " << std::endl <<
      line_start << "\twall_id = " << wall_id << std::endl <<
      line_start << "\twall_type = " << wall_type << std::endl <<
      line_start << "\ton_wall_boundary_idx = " << on_wall_boundary_idx << std::endl <<
      line_start << "\ton_wall_boundary_start_position = " << on_wall_boundary_start_position << std::endl <<
      line_start << "\ttarget_size = [" << target_width << "," << target_height << "]" << std::endl <<
      line_start << "\treal_size = [" << real_width << "," << real_height << "]" << std::endl;

    return true;
}

bool FreeRoomContainerData::reset()
{
    team_x_direction_person_num = 0;
    team_y_direction_person_num = 0;
    team_dist = -1;
    person_edge = -1;

    return true;
}

bool FreeRoomContainerData::outputInfo(
    const size_t &info_level)
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "FreeRoomContainerData : " << std::endl <<
      line_start << "\tteam_x_direction_person_num = " << team_x_direction_person_num << std::endl <<
      line_start << "\tteam_y_direction_person_num = " << team_y_direction_person_num << std::endl <<
      line_start << "\tteam_dist = " << team_dist << std::endl <<
      line_start << "\tperson_edge = " << person_edge << std::endl;

    return true;
}

bool WorldGenerateDataManager::reset()
{
    world_data.reset();
    wall_data_vec.clear();
    wall_roomcontainer_data_vec.clear();
    free_roomcontainer_data.reset();

    return true;
}

bool WorldGenerateDataManager::setWorldCenter(
    const float &world_center_x,
    const float &world_center_y)
{
    world_data.world_center_x = world_center_x;
    world_data.world_center_y = world_center_y;

    return true;
}

bool WorldGenerateDataManager::addWall(
    const size_t &id,
    const NodeType &type,
    const EasyPolygon2D &boundary_polygon)
{
    WallData new_wall_data;
    new_wall_data.id = id;
    new_wall_data.type = type;
    new_wall_data.boundary_polygon = boundary_polygon;

    wall_data_vec.emplace_back(new_wall_data);

    return true;
}

bool WorldGenerateDataManager::addWallRoomContainer(
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &on_wall_boundary_idx,
    const float &on_wall_boundary_start_position,
    const float &target_width,
    const float &real_width,
    const float &target_height,
    const float &real_height)
{
    WallRoomContainerData new_wall_roomcontainer_data;
    new_wall_roomcontainer_data.wall_id = wall_id;
    new_wall_roomcontainer_data.wall_type = wall_type;
    new_wall_roomcontainer_data.on_wall_boundary_idx = on_wall_boundary_idx;
    new_wall_roomcontainer_data.on_wall_boundary_start_position = on_wall_boundary_start_position;
    new_wall_roomcontainer_data.target_width = target_width;
    new_wall_roomcontainer_data.real_width = real_width;
    new_wall_roomcontainer_data.target_height = target_height;
    new_wall_roomcontainer_data.real_height = real_height;

    wall_roomcontainer_data_vec.emplace_back(new_wall_roomcontainer_data);

    return true;
}

bool WorldGenerateDataManager::setWallRoomContainer(
    const size_t &wall_roomcontainer_data_idx,
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &on_wall_boundary_idx,
    const float &on_wall_boundary_start_position,
    const float &target_width,
    const float &real_width,
    const float &target_height,
    const float &real_height)
{
    if(wall_roomcontainer_data_idx >= wall_roomcontainer_data_vec.size())
    {
        std::cout << "WorldGenerateDataManager::setWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_data_idx = " << wall_roomcontainer_data_idx << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\ton_wall_boundary_idx = " << on_wall_boundary_idx << std::endl <<
          "\ton_wall_boundary_start_position = " << on_wall_boundary_start_position << std::endl <<
          "\ttarget_size = [" << target_width << "," << target_height << "]" << std::endl <<
          "\treal_size = [" << real_width << "," << real_height << "]" << std::endl <<
          "wall_roomcontainer_data_idx out of range!" << std::endl;

        return false;
    }

    WallRoomContainerData &wall_roomcontainer_data = wall_roomcontainer_data_vec[wall_roomcontainer_data_idx];
    wall_roomcontainer_data.wall_id = wall_id;
    wall_roomcontainer_data.wall_type = wall_type;
    wall_roomcontainer_data.on_wall_boundary_idx = on_wall_boundary_idx;
    wall_roomcontainer_data.on_wall_boundary_start_position = on_wall_boundary_start_position;
    wall_roomcontainer_data.target_width = target_width;
    wall_roomcontainer_data.real_width = real_width;
    wall_roomcontainer_data.target_height = target_height;
    wall_roomcontainer_data.real_height = real_height;

    return true;
}

bool WorldGenerateDataManager::setFreeRoomContainer(
    const size_t &team_x_direction_person_num,
    const size_t &team_y_direction_person_num,
    const float &team_dist,
    const float &person_edge)
{
    free_roomcontainer_data.team_x_direction_person_num = team_x_direction_person_num;
    free_roomcontainer_data.team_y_direction_person_num = team_y_direction_person_num;
    free_roomcontainer_data.team_dist = team_dist;
    free_roomcontainer_data.person_edge = person_edge;

    return true;
}

bool WorldGenerateDataManager::outputInfo(
    const size_t &info_level)
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "WorldGenerateDataManager : " << std::endl;
    world_data.outputInfo(info_level + 1);

    for(WallData &wall_data : wall_data_vec)
    {
        wall_data.outputInfo(info_level + 1);
    }

    for(WallRoomContainerData &wall_roomcontainer_data : wall_roomcontainer_data_vec)
    {
        wall_roomcontainer_data.outputInfo(info_level + 1);
    }

    free_roomcontainer_data.outputInfo(info_level + 1);

    return true;
}

bool WorldEditer::reset()
{
    world_generate_data_manager_.reset();

    return true;
}

bool WorldEditer::readData(
    WorldPlaceGenerator &world_place_generator)
{
    if(!world_generate_data_manager_.reset())
    {
        std::cout << "WorldEditer::readData : " << std::endl <<
          "reset world generate data manager failed!" << std::endl;

        return false;
    }

    EasyNode* world_node = world_place_generator.world_controller_.findNode(
        0, NodeType::World);

    if(world_node == nullptr)
    {
        std::cout << "WorldEditer::readData : " << std::endl <<
          "world node not found!" << std::endl;

        return false;
    }

    const EasyAxis2D &world_axis_in_world =
      world_node->getAxisInWorld();

    if(!world_generate_data_manager_.setWorldCenter(
          world_axis_in_world.center_.x,
          world_axis_in_world.center_.y))
    {
        std::cout << "WorldEditer::readData : " << std::endl <<
          "setWorldCenter failed!" << std::endl;

        return false;
    }

    if(!world_generate_data_manager_.addWall(
          0,
          NodeType::OuterWall,
          world_place_generator.wall_boundary_polygon_))
    {
        std::cout << "WorldEditer::readData : " << std::endl <<
          "addWall failed!" << std::endl;

        return false;
    }

    const size_t wall_roomcontainer_data_num =
      world_place_generator.boundary_line_list_manager_.current_place_idx_;
    
    if(wall_roomcontainer_data_num == 0)
    {
        return true;
    }

    world_generate_data_manager_.wall_roomcontainer_data_vec.resize(
        wall_roomcontainer_data_num);

    for(size_t i = 0;
        i < world_place_generator.boundary_line_list_manager_.boundary_line_list_vec_.size();
        ++i)
    {
        const BoundaryLineList &boundary_line_list =
          world_place_generator.boundary_line_list_manager_.boundary_line_list_vec_[i];

        BoundaryLine* boundary_line = boundary_line_list.boundary_line_list_;

        while(boundary_line != nullptr)
        {
            if(!world_generate_data_manager_.setWallRoomContainer(
                  boundary_line->place_idx,
                  0,
                  NodeType::OuterWall,
                  i,
                  boundary_line->line_start_position,
                  boundary_line->line_width,
                  boundary_line->line_end_position - boundary_line->line_start_position,
                  boundary_line->line_height,
                  boundary_line->line_real_height))
            {
                std::cout << "WorldEditer::readData : " << std::endl <<
                  "setWallRoomContainer failed!" << std::endl;

                return false;
            }

            boundary_line = boundary_line->next_line;
        }
    }

    if(!world_generate_data_manager_.setFreeRoomContainer(
          world_place_generator.team_x_direction_person_num_,
          world_place_generator.team_y_direction_person_num_,
          world_place_generator.team_dist_,
          world_place_generator.person_edge_))
    {
        std::cout << "WorldEditer::readData : " << std::endl <<
          "setFreeRoomContainer failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldEditer::loadData(
    WorldPlaceGenerator &world_place_generator)
{
    const float &world_center_x = world_generate_data_manager_.world_data.world_center_x;
    const float &world_center_y = world_generate_data_manager_.world_data.world_center_y;

    if(world_generate_data_manager_.wall_data_vec.size() == 0)
    {
        std::cout << "WorldEditer::loadData : " << std::endl <<
          "no wall data found!" << std::endl;

        return false;
    }

    if(!world_place_generator.reset())
    {
        std::cout << "WorldEditer::loadData : " << std::endl <<
          "reset world place generator failed!" << std::endl;

        return false;
    }

    world_place_generator.current_new_room_id_ = 0;

    if(!world_place_generator.world_controller_.createWorld(world_center_x, world_center_y))
    {
        std::cout << "WorldEditer::loadData : " << std::endl <<
          "createWorld failed!" << std::endl;

        return false;
    }

    for(const WallData &wall_data : world_generate_data_manager_.wall_data_vec)
    {
        if(!world_place_generator.world_controller_.createWall(
              wall_data.id,
              wall_data.type))
        {
            std::cout << "WorldEditer::loadData : " << std::endl <<
              "createWall failed!" << std::endl;

            return false;
        }

        if(!world_place_generator.world_controller_.setWallBoundaryPolygon(
              wall_data.id,
              wall_data.type,
              wall_data.boundary_polygon))
        {
            std::cout << "WorldEditer::loadData : " << std::endl <<
              "setWallBoundaryPolygon failed!" << std::endl;

            return false;
        }

        if(!world_place_generator.setWallBoundaryPolygon(
              wall_data.boundary_polygon))
        {
            std::cout << "WorldEditer::loadData : " << std::endl <<
              "setWallBoundaryPolygon failed!" << std::endl;

            return false;
        }
    }

    for(const WallRoomContainerData wall_roomcontainer_data : world_generate_data_manager_.wall_roomcontainer_data_vec)
    {
        if(!world_place_generator.placeWallRoomContainer(
              wall_roomcontainer_data.on_wall_boundary_idx,
              wall_roomcontainer_data.on_wall_boundary_start_position,
              wall_roomcontainer_data.target_width,
              wall_roomcontainer_data.target_height))
        {
            // std::cout << "WorldEditer::loadData : " << std::endl <<
            //   "placeWallRoomContainer failed!" << std::endl;

            continue;
        }
    }

    world_place_generator.team_x_direction_person_num_ =
      world_generate_data_manager_.free_roomcontainer_data.team_x_direction_person_num;
    world_place_generator.team_y_direction_person_num_ =
      world_generate_data_manager_.free_roomcontainer_data.team_y_direction_person_num;
    world_place_generator.team_dist_ =
      world_generate_data_manager_.free_roomcontainer_data.team_dist;
    world_place_generator.person_edge_ =
      world_generate_data_manager_.free_roomcontainer_data.person_edge;

    if(!world_place_generator.generateFreeRoomContainer(
          world_generate_data_manager_.free_roomcontainer_data.team_x_direction_person_num,
          world_generate_data_manager_.free_roomcontainer_data.team_y_direction_person_num,
          world_generate_data_manager_.free_roomcontainer_data.team_dist,
          world_generate_data_manager_.free_roomcontainer_data.person_edge))
    {
        std::cout << "WorldEditer::loadData : " << std::endl <<
          "generateFreeRoomContainer failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldEditer::setWallRoomContainerPosition(
    WorldPlaceGenerator &world_place_generator,
    const size_t &wall_roomcontainer_id,
    const float &new_position_x,
    const float &new_position_y,
    const float &mouse_pos_x_direction_delta)
{
    const float start_change_edge_error = 1.0;

    if(!readData(world_place_generator))
    {
        std::cout << "WorldEditer::setWallRoomContainerPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]" << std::endl <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "readData failed!" << std::endl;

        return false;
    }

    EasyNode* wall_roomcontainer_node = world_place_generator.world_controller_.findNode(
        wall_roomcontainer_id, NodeType::RoomContainer);

    if(wall_roomcontainer_node == nullptr)
    {
        std::cout << "WorldEditer::setWallRoomContainerPosition : " << std::endl <<
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
        std::cout << "WorldEditer::setWallRoomContainerPosition : " << std::endl <<
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
        std::cout << "WorldEditer::setWallRoomContainerPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_id = " << wall_roomcontainer_id << std::endl <<
          "\tnew_position = [" << new_position_x << "," <<
          new_position_y << "]" << std::endl <<
          "\tmouse_pos_x_direction_delta = " << mouse_pos_x_direction_delta << std::endl <<
          "getPointInNode failed!" << std::endl;

        return false;
    }

    WallRoomContainerData &wall_roomcontainer_data =
      world_generate_data_manager_.wall_roomcontainer_data_vec[wall_roomcontainer_id];

    const size_t &wall_id = wall_roomcontainer_data.wall_id;
    const float &wall_length =
      world_place_generator.boundary_line_list_manager_.boundary_line_list_vec_[wall_id].boundary_length_;

    if(wall_roomcontainer_data.on_wall_boundary_start_position < start_change_edge_error &&
        new_position_in_parent.y > wall_roomcontainer_data.real_height)
    {
        wall_roomcontainer_data.on_wall_boundary_idx =
          (wall_roomcontainer_data.on_wall_boundary_idx - 1 +
           world_place_generator.boundary_line_list_manager_.boundary_line_list_vec_.size()) %
          world_place_generator.boundary_line_list_manager_.boundary_line_list_vec_.size();

        wall_roomcontainer_data.on_wall_boundary_start_position = 0;
    }
    else if(wall_roomcontainer_data.on_wall_boundary_start_position + wall_roomcontainer_data.real_width >
        wall_length - start_change_edge_error &&
        new_position_in_parent.y > wall_roomcontainer_data.real_height)
    {
        wall_roomcontainer_data.on_wall_boundary_idx =
          (wall_roomcontainer_data.on_wall_boundary_idx + 1) %
          world_place_generator.boundary_line_list_manager_.boundary_line_list_vec_.size();

        wall_roomcontainer_data.on_wall_boundary_start_position =
          world_place_generator.boundary_line_list_manager_.boundary_line_list_vec_[
          (wall_id + 1) % world_place_generator.boundary_line_list_manager_.boundary_line_list_vec_.size()].boundary_length_;
    }
    else
    {
        wall_roomcontainer_data.on_wall_boundary_start_position =
          new_position_in_parent.x - mouse_pos_x_direction_delta;
    }

    if(!loadData(world_place_generator))
    {
        std::cout << "WorldEditer::setWallRoomContainerPosition : " << std::endl <<
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

