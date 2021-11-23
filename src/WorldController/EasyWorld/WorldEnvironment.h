#ifndef WORLD_ENVIRONMENT_H
#define WORLD_ENVIRONMENT_H

#include "EasyWorld/WallGenerator.h"
#include "EasyWorld/WorldPlaceGenerator.h"
#include "EasyWorld/WorldEditor.h"

class WorldEnvironment
{
public:
    WorldEnvironment()
    {
    }

    bool reset();
    bool resetButRemainWall();

    bool createNewWorld(
        const float& world_center_x,
        const float& world_center_y);

    bool createOuterWall();
    bool createInnerWall();

    bool addPointForOuterWall(
        const size_t& outerwall_idx,
        const float& point_x,
        const float& point_y);
    bool addPointForInnerWall(
        const size_t& innerwall_idx,
        const float& point_x,
        const float& point_y);

    bool generateWall();

    bool placeWallRoomContainer(
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &boundary_idx,
        const float &roomcontainer_start_position,
        const float &roomcontainer_width,
        const float &roomcontainer_height,
        const size_t &room_num);

    bool generateFreeRoomContainer(
        const size_t &team_x_direction_person_num,
        const size_t &team_y_direction_person_num,
        const float &team_dist,
        const float &person_edge);

    bool setWallRoomContainerPosition(
        const size_t &wall_roomcontainer_id,
        const float &new_position_x,
        const float &new_position_y,
        const float &mouse_pos_x_direction_delta);

    WallGenerator wall_generator_;
    WorldController world_controller_;
    WorldPlaceGenerator world_place_generator_;
    WorldEditor world_editor_;
};

#endif //WORLD_ENVIRONMENT_H
