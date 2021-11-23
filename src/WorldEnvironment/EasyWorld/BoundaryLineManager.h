#ifndef BOUNDARY_LINE_MANAGER_H
#define BOUNDARY_LINE_MANAGER_H

#include "export_library_global.h"

#include "EasyShape/EasyShape.h"
#include "EasyWorld.h"

class LIBRARY_EXPORT BoundaryLine
{
public:
    BoundaryLine()
    {
        next_line = nullptr;
        prev_line = nullptr;

        reset();
    }

    bool reset();

    bool outputInfo(
        const size_t &info_level) const;

    size_t place_idx;
    float line_start_position;
    float line_end_position;
    float line_width;
    float line_height;
    float line_real_height;

    size_t line_room_num;
    std::vector<std::string> room_name_vec;

    BoundaryLine* prev_line;
    BoundaryLine* next_line;
};

class LIBRARY_EXPORT BoundaryLineList
{
public:
    BoundaryLineList()
    {
        boundary_line_list_ = nullptr;
    }
    ~BoundaryLineList();

    bool reset();

    bool setBoundaryLength(
        const float &boundary_length);

    bool findNearestUnusedBoundaryLine(
        const BoundaryLine &new_boundary_line,
        float &nearest_unused_start_position,
        float &nearest_unused_end_position);

    bool findNearestValidBoundaryLine(
        const BoundaryLine &new_boundary_line,
        BoundaryLine &valid_boundary_line);

    bool insertValidBoundaryLine(
        const BoundaryLine &valid_boundary_line);

    bool outputInfo(
        const size_t &info_level) const;

    float boundary_length_;
    BoundaryLine* boundary_line_list_;
};

class LIBRARY_EXPORT WallBoundaryLineList
{
public:
    WallBoundaryLineList()
    {
    }

    bool resetBoundaryLine();

    bool reset();

    bool setWall(
        const size_t &wall_id,
        const NodeType &wall_type);

    bool setBoundaryPolygon(
        const EasyPolygon2D &boundary_polygon);

    bool insertBoundaryLine(
        const size_t &boundary_idx,
        const BoundaryLine &valid_boundary_line);

    bool getBoundaryPoint(
        const size_t &boundary_idx,
        const float &boundary_position,
        const float &point_height,
        EasyPoint2D &boundary_point);

    bool getBoundaryLinePolygon(
        const size_t &boundary_idx,
        const float &line_start_position,
        const float &line_width,
        const float &line_height,
        EasyPolygon2D &boundary_line_polygon);

    bool outputInfo(
        const size_t &info_level) const;

    size_t wall_id_;
    NodeType wall_type_;
    EasyPolygon2D wall_boundary_polygon_;

    std::vector<BoundaryLineList> boundary_line_list_vec_;
};

class LIBRARY_EXPORT BoundaryLineManager
{
public:
    BoundaryLineManager()
    {
    }

    bool reset();

    bool resetButRemainWall();

    bool addBoundaryPolygon(
        const size_t &wall_id,
        const NodeType &wall_type,
        const EasyPolygon2D &boundary_polygon);

    bool setBoundaryPolygon(
        const size_t &wall_id,
        const NodeType &wall_type,
        const EasyPolygon2D &boundary_polygon);

    bool insertBoundaryLine(
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &boundary_idx,
        const BoundaryLine &new_boundary_line,
        BoundaryLine &valid_boundary_line);

    bool getWallBoundaryLineListIdx(
        const size_t &wall_id,
        const NodeType &wall_type,
        size_t &wall_boundary_line_list_idx);

private:
    bool getMaxHeight(
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &boundary_idx,
        const BoundaryLine &boundary_line,
        float &max_height);

public:
    bool outputInfo(
        const size_t &info_level) const;

    std::vector<WallBoundaryLineList> wall_boundary_line_list_vec_;

    size_t current_place_idx_;

    std::vector<EasyPolygon2D> valid_boundary_polygon_vec_;
};

#endif //BOUNDARY_LINE_MANAGER_H
