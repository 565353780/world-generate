#ifndef WORLD_EDITER_H
#define WORLD_EDITER_H

#include <iostream>
#include <string>

#include "WorldController.h"
#include "WorldPlaceGenerator.h"

class WorldData
{
public:
    WorldData()
    {
    }

    bool reset();
    
    bool outputInfo(
        const size_t &info_level);

    float world_center_x;
    float world_center_y;

    std::string name;
};

class WallData
{
public:
    WallData()
    {
    }

    bool reset();

    bool outputInfo(
        const size_t &info_level);

    size_t id;
    NodeType type;
    EasyPolygon2D boundary_polygon;

    std::string name;
};

class WallRoomContainerData
{
public:
    WallRoomContainerData()
    {
    }

    bool reset();

    bool outputInfo(
        const size_t &info_level);

    size_t wall_id;
    NodeType wall_type;
    size_t on_wall_boundary_idx;
    float on_wall_boundary_start_position;
    float target_width;
    float real_width;
    float target_height;
    float real_height;

    size_t room_num;
    std::vector<std::string> room_name_vec;
};

class FreeRoomContainerData
{
public:
    FreeRoomContainerData()
    {
    }

    bool reset();

    bool outputInfo(
        const size_t &info_level);

    size_t team_x_direction_person_num;
    size_t team_y_direction_person_num;
    float team_dist;
    float person_edge;
};

class WorldGenerateDataManager
{
public:
    WorldGenerateDataManager()
    {
    }

    bool reset();

    bool setWorld(
        const std::string &name,
        const float &world_center_x,
        const float &world_center_y);

    bool addWall(
        const std::string &name,
        const size_t &id,
        const NodeType &type,
        const EasyPolygon2D &boundary_polygon);

    bool addWallRoomContainer(
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &on_wall_boundary_idx,
        const float &on_wall_boundary_start_position,
        const float &target_width,
        const float &real_width,
        const float &target_height,
        const float &real_height,
        const size_t &room_num,
        const std::vector<std::string> &room_name_vec);

    bool setWallRoomContainer(
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
        const std::vector<std::string> &room_name_vec);

    bool setFreeRoomContainer(
        const size_t &team_x_direction_person_num,
        const size_t &team_y_direction_person_num,
        const float &team_dist,
        const float &person_edge);

    bool outputInfo(
        const size_t &info_level);

    WorldData world_data;
    std::vector<WallData> wall_data_vec;
    std::vector<WallRoomContainerData> wall_roomcontainer_data_vec;
    FreeRoomContainerData free_roomcontainer_data;
};

class WorldEditer
{
public:
    WorldEditer()
    {
    }

    bool reset();

    bool readData(
        WorldController &world_controller,
        WorldPlaceGenerator &world_place_generator);

    bool loadData(
        WorldController &world_controller,
        WorldPlaceGenerator &world_place_generator);

    bool setWallRoomContainerPosition(
        WorldController &world_controller,
        WorldPlaceGenerator &world_place_generator,
        const size_t &wall_roomcontainer_id,
        const float &new_position_x,
        const float &new_position_y,
        const float &mouse_pos_x_direction_delta);

private:
    WorldGenerateDataManager world_generate_data_manager_;
};

#endif //WORLD_EDITER_H
