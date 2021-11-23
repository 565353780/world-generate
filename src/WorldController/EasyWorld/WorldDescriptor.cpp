#include "WorldDescriptor.h"

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

    room_num = 0;
    room_name_vec.clear();

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
      line_start << "\treal_size = [" << real_width << "," << real_height << "]" << std::endl <<
      line_start << "\troom_num = " << room_num << std::endl <<
      line_start << "\troom_name_vec = ";

    if(room_name_vec.size() == 0)
    {
        std::cout << "NULL" << std::endl;
    }
    else
    {
        for(const std::string &room_name : room_name_vec)
        {
            std::cout << room_name << " ";
        }

        std::cout << std::endl;
    }

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

bool WorldDescriptor::reset()
{
    world_data.reset();
    wall_data_vec.clear();
    wall_roomcontainer_data_vec.clear();
    free_roomcontainer_data.reset();

    return true;
}

bool WorldDescriptor::readData(
    WorldController &world_controller,
    WorldPlaceGenerator &world_place_generator)
{
    if(!reset())
    {
        std::cout << "WorldDescriptor::readData : " << std::endl <<
          "reset world generate data manager failed!" << std::endl;

        return false;
    }

    EasyNode* world_node = world_controller.findNode(
        0, NodeType::World);

    if(world_node == nullptr)
    {
        std::cout << "WorldDescriptor::readData : " << std::endl <<
          "world node not found!" << std::endl;

        return false;
    }

    const EasyAxis2D &world_axis_in_world =
      world_node->getAxisInWorld();

    if(!setWorld(
          world_node->getName(),
          world_axis_in_world.center_.x,
          world_axis_in_world.center_.y))
    {
        std::cout << "WorldDescriptor::readData : " << std::endl <<
          "setWorldCenter failed!" << std::endl;

        return false;
    }

    for(EasyNode* wall_node : world_node->getChildNodeVec())
    {
        const NodeType &wall_type = wall_node->getNodeType();

        if(wall_type != NodeType::OuterWall &&
            wall_type != NodeType::InnerWall)
        {
            continue;
        }

        EasyNode* wall_space_node = wall_node->findChild(0, NodeType::Space);

        if(wall_space_node == nullptr)
        {
            std::cout << "WorldDescriptor::readData : " << std::endl <<
              "wall space node is nullptr!" << std::endl;

            return false;
        }

        if(!addWall(
              wall_node->getName(),
              wall_node->getID(),
              wall_node->getNodeType(),
              wall_space_node->getBoundaryPolygon()))
        {
            std::cout << "WorldDescriptor::readData : " << std::endl <<
              "addWall failed!" << std::endl;

            return false;
        }
    }

    if(!setFreeRoomContainer(
          world_place_generator.team_x_direction_person_num_,
          world_place_generator.team_y_direction_person_num_,
          world_place_generator.team_dist_,
          world_place_generator.person_edge_))
    {
        std::cout << "WorldDescriptor::readData : " << std::endl <<
          "setFreeRoomContainer failed!" << std::endl;

        return false;
    }

    const size_t wall_roomcontainer_data_num =
      world_place_generator.boundary_line_manager_.valid_boundary_polygon_vec_.size();
    
    if(wall_roomcontainer_data_num == 0)
    {
        wall_roomcontainer_data_vec.clear();

        return true;
    }

    wall_roomcontainer_data_vec.resize(
        wall_roomcontainer_data_num);

    for(const WallBoundaryLineList &wall_boundary_line_list :
        world_place_generator.boundary_line_manager_.wall_boundary_line_list_vec_)
    {
        const size_t &wall_id = wall_boundary_line_list.wall_id_;
        const NodeType &wall_type = wall_boundary_line_list.wall_type_;

        for(size_t i = 0; i < wall_boundary_line_list.boundary_line_list_vec_.size(); ++i)
        {
            const BoundaryLineList &boundary_line_list = wall_boundary_line_list.boundary_line_list_vec_[i];

            BoundaryLine* boundary_line = boundary_line_list.boundary_line_list_;

            while(boundary_line != nullptr)
            {
                if(!setWallRoomContainer(
                      boundary_line->place_idx,
                      wall_id,
                      wall_type,
                      i,
                      boundary_line->line_start_position,
                      boundary_line->line_width,
                      boundary_line->line_end_position - boundary_line->line_start_position,
                      boundary_line->line_height,
                      boundary_line->line_real_height,
                      boundary_line->line_room_num,
                      boundary_line->room_name_vec))
                {
                    std::cout << "WorldDescriptor::readData : " << std::endl <<
                      "setWallRoomContainer failed!" << std::endl;

                    return false;
                }

                boundary_line = boundary_line->next_line;
            }
        }
    }

    return true;
}

bool WorldDescriptor::loadData(
    WorldController &world_controller,
    WorldPlaceGenerator &world_place_generator)
{
    const float &world_center_x = world_data.world_center_x;
    const float &world_center_y = world_data.world_center_y;

    if(!world_place_generator.reset())
    {
        std::cout << "WorldDescriptor::loadData : " << std::endl <<
          "reset world place generator failed!" << std::endl;

        return false;
    }

    if(!world_place_generator.createNewWorld(
          world_controller,
          world_center_x,
          world_center_y))
    {
        std::cout << "WorldDescriptor::loadData : " << std::endl <<
          "createNewWorld failed!" << std::endl;

        return false;
    }

    if(wall_data_vec.size() == 0)
    {
        std::cout << "WorldDescriptor::loadData : " << std::endl <<
          "no wall data found!" << std::endl;

        return false;
    }

    for(const WallData &wall_data : wall_data_vec)
    {
        if(wall_data.type == NodeType::OuterWall)
        {
            world_place_generator.outerwall_boundary_polygon_ = wall_data.boundary_polygon;
            world_place_generator.is_outerwall_boundary_polygon_set_ = true;
        }

        if(!world_place_generator.generateWall(world_controller,
              wall_data.name,
              wall_data.type,
              wall_data.boundary_polygon))
        {
            std::cout << "WorldDescriptor::loadData : " << std::endl <<
              "generateWall failed!" << std::endl;

            return false;
        }
    }

    for(const WallRoomContainerData &wall_roomcontainer_data :
        wall_roomcontainer_data_vec)
    {
        if(!world_place_generator.placeWallRoomContainer(
              world_controller,
              wall_roomcontainer_data.wall_id,
              wall_roomcontainer_data.wall_type,
              wall_roomcontainer_data.on_wall_boundary_idx,
              wall_roomcontainer_data.on_wall_boundary_start_position,
              wall_roomcontainer_data.target_width,
              wall_roomcontainer_data.target_height,
              wall_roomcontainer_data.room_num,
              wall_roomcontainer_data.room_name_vec))
        {
            // std::cout << "WorldDescriptor::loadData : " << std::endl <<
            //   "placeWallRoomContainer failed!" << std::endl;

            continue;
        }
    }

    world_place_generator.team_x_direction_person_num_ =
      free_roomcontainer_data.team_x_direction_person_num;
    world_place_generator.team_y_direction_person_num_ =
      free_roomcontainer_data.team_y_direction_person_num;
    world_place_generator.team_dist_ =
      free_roomcontainer_data.team_dist;
    world_place_generator.person_edge_ =
      free_roomcontainer_data.person_edge;

    if(!world_place_generator.generateFreeRoomContainer(
          world_controller,
          free_roomcontainer_data.team_x_direction_person_num,
          free_roomcontainer_data.team_y_direction_person_num,
          free_roomcontainer_data.team_dist,
          free_roomcontainer_data.person_edge))
    {
        std::cout << "WorldDescriptor::loadData : " << std::endl <<
          "generateFreeRoomContainer failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldDescriptor::setWorld(
    const std::string &name,
    const float &world_center_x,
    const float &world_center_y)
{
    world_data.name = name;
    world_data.world_center_x = world_center_x;
    world_data.world_center_y = world_center_y;

    return true;
}

bool WorldDescriptor::addWall(
    const std::string &name,
    const size_t &id,
    const NodeType &type,
    const EasyPolygon2D &boundary_polygon)
{
    WallData new_wall_data;
    new_wall_data.name = name;
    new_wall_data.id = id;
    new_wall_data.type = type;
    new_wall_data.boundary_polygon = boundary_polygon;

    wall_data_vec.emplace_back(new_wall_data);

    return true;
}

bool WorldDescriptor::addWallRoomContainer(
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &on_wall_boundary_idx,
    const float &on_wall_boundary_start_position,
    const float &target_width,
    const float &real_width,
    const float &target_height,
    const float &real_height,
    const size_t &room_num,
    const std::vector<std::string> &room_name_vec)
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
    new_wall_roomcontainer_data.room_num = room_num;
    new_wall_roomcontainer_data.room_name_vec = room_name_vec;

    wall_roomcontainer_data_vec.emplace_back(new_wall_roomcontainer_data);

    return true;
}

bool WorldDescriptor::setWallRoomContainer(
    const size_t &wall_roomcontainer_data_idx,
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &on_wall_boundary_idx,
    const float &on_wall_boundary_start_position,
    const float &target_width,
    const float &real_width,
    const float &target_height,
    const float &real_height,
    const size_t &room_num,
    const std::vector<std::string> &room_name_vec)
{
    if(wall_roomcontainer_data_idx >= wall_roomcontainer_data_vec.size())
    {
        std::cout << "WorldDescriptor::setWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\twall_roomcontainer_data_idx = " << wall_roomcontainer_data_idx << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\ton_wall_boundary_idx = " << on_wall_boundary_idx << std::endl <<
          "\ton_wall_boundary_start_position = " << on_wall_boundary_start_position << std::endl <<
          "\ttarget_size = [" << target_width << "," << target_height << "]" << std::endl <<
          "\treal_size = [" << real_width << "," << real_height << "]" << std::endl <<
          "\troom_num = " << room_num << std::endl <<
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
    wall_roomcontainer_data.room_num = room_num;
    wall_roomcontainer_data.room_name_vec = room_name_vec;

    return true;
}

bool WorldDescriptor::setFreeRoomContainer(
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

bool WorldDescriptor::outputInfo(
    const size_t &info_level)
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "WorldDescriptor : " << std::endl;
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

