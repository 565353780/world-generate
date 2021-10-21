#ifndef WORLD_EDITER_H
#define WORLD_EDITER_H

#include <iostream>
#include <string>

#include "WorldPlaceGenerator.h"

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

    bool addWall(
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
        const float &real_height);

    bool setWallRoomContainer(
        const size_t &wall_roomcontainer_data_idx,
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &on_wall_boundary_idx,
        const float &on_wall_boundary_start_position,
        const float &target_width,
        const float &real_width,
        const float &target_height,
        const float &real_height);

    bool setFreeRoomContainer(
        const size_t &team_x_direction_person_num,
        const size_t &team_y_direction_person_num,
        const float &team_dist,
        const float &person_edge);

    bool outputInfo(
        const size_t &info_level);

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

    bool setWallBoundaryPolygon(
        const EasyPolygon2D &wall_boundary_polygon);

    bool generateWorld();

    bool readData();

    bool loadData();

    WorldPlaceGenerator world_place_generator_;
    WorldGenerateDataManager world_generate_data_manager_;
};

#endif //WORLD_EDITER_H
