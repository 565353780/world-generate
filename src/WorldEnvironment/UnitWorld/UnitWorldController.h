#ifndef UNIT_WORLD_CONTROLLER_H
#define UNIT_WORLD_CONTROLLER_H

#include "export_library_global.h"

#include "UnitTree.h"
#include "UnitNodeLineManager.h"

class LIBRARY_EXPORT UnitWorldController
{
public:
    UnitWorldController()
    {
    }

    bool reset();
    bool resetButRemainWall();

    bool createWorld();

    bool createWall(
        const std::string& wall_name,
        const size_t& wall_id,
        const NodeType& wall_type);

    bool createRoom(
        const std::string& room_name,
        const size_t& room_id,
        const NodeType& room_type,
        const size_t& on_wall_id,
        const NodeType& on_wall_type);

    bool setWallBoundaryPolygon(
        const size_t& wall_id,
        const NodeType& wall_type,
        const EasyPolygon2D& wall_boundary_polygon);

    bool getNearestWall(
        const EasyPoint2D& point,
        size_t& nearest_wall_id,
        NodeType& nearest_wall_type);

    bool setRoomPositionOnTree(
        const size_t& room_id,
        const NodeType& room_type,
        const size_t& parent_id,
        const NodeType& parent_type,
        const float& room_target_param,
        const float& room_target_width,
        const float& room_target_height);

    bool setRoomPositionOnTreeByPosition(
        const size_t& room_id,
        const NodeType& room_type,
        const EasyPoint2D& point,
        const float& room_target_width,
        const float& room_target_height);

    UnitTree unit_tree;
    UnitNodeLineManager unit_node_line_manager;
};

#endif // UNIT_WORLD_CONTROLLER_H
