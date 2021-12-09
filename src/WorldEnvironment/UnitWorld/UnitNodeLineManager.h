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

    float target_left_param;
    float target_right_param;
    float real_left_param;
    float real_right_param;

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

    bool findNearestValidPosition(
        const UnitNodePosition& target_position,
        UnitNodePosition& valid_position);

    bool insertValidPosition(
        const UnitNodePosition &valid_position);

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
        const UnitNodePosition& target_position,
        UnitNodePosition& valid_position);

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

    UnitTree unit_tree_;
};

#endif // UNIT_NODE_LINE_MANAGER_H
