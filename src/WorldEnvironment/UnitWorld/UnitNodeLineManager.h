#ifndef UNIT_NODE_LINE_MANAGER_H
#define UNIT_NODE_LINE_MANAGER_H

#include "export_library_global.h"

#include "UnitTree.h"

class LIBRARY_EXPORT UnitNodePosition
{
public:
    UnitNodePosition()
    {
        next_position = nullptr;
        prev_position = nullptr;

        reset();
    }

    bool reset();

    bool outputInfo(
        const size_t &info_level) const;

    size_t node_id;
    NodeType node_type;
    float target_left_param;
    float target_right_param;
    float target_height;
    float real_left_param;
    float real_right_param;
    float real_height;

    UnitNodePosition* prev_position;
    UnitNodePosition* next_position;
};

class LIBRARY_EXPORT UnitNodeLine
{
public:
    UnitNodeLine()
    {
        position_line = nullptr;
    }
    ~UnitNodeLine();

    bool reset();

    bool findNearestUnusedPosition(
        const UnitNodePosition& target_position,
        float &nearest_unused_left_param,
        float &nearest_unused_right_param);

    bool updatePosition(
        UnitNodePosition& target_position);

    bool insertValidPosition(
        const UnitNodePosition &valid_position);

    bool outputInfo(
        const size_t &info_level) const;

    UnitNodePosition* position_line;
};

class LIBRARY_EXPORT WallUnitNodeLine
{
public:
    WallUnitNodeLine()
    {
    }

    bool resetPositionLine();

    bool reset();

    bool setWall(
        const size_t &target_wall_id,
        const NodeType &target_wall_type);

    bool setBoundaryPolygon(
        const EasyPolygon2D &boundary_polygon);

    bool insertPosition(
        UnitNodePosition& target_position);

    bool outputInfo(
        const size_t &info_level) const;

    size_t wall_id;
    NodeType wall_type;
    EasyPolygon2D wall_boundary_polygon;

    UnitNodeLine wall_boundary_line;
};

class LIBRARY_EXPORT UnitNodeLineManager
{
public:
    UnitNodeLineManager()
    {
    }
    
    bool reset();

    bool resetButRemainWall();

    bool haveThisWallLine(
        const size_t& wall_id,
        const NodeType& wall_type);

    bool getWallLineIdx(
        const size_t& wall_id,
        const NodeType& wall_type,
        size_t& wall_line_idx);

    bool createWallLine(
        const size_t& wall_id,
        const NodeType& wall_type);

    bool setBoundaryPolygon(
        const size_t &wall_id,
        const NodeType &wall_type,
        const EasyPolygon2D &boundary_polygon);

    bool getMaxHeight(
        const size_t &wall_id,
        const NodeType &wall_type,
        const UnitNodePosition& target_position,
        float &max_height);

    bool removePosition(
        const size_t& node_id,
        const NodeType& node_type);

    bool insertPosition(
        const size_t &wall_id,
        const NodeType &wall_type,
        UnitNodePosition& target_position);

    std::vector<WallUnitNodeLine> wall_line_vec;

    std::vector<EasyPolygon2D> valid_boundary_polygon_vec;

    EasyLine2D error_base_line;
    EasyLine2D error_polygon_line;
};

#endif // UNIT_NODE_LINE_MANAGER_H
