#ifndef WORLD_PLACE_GENERATOR
#define WORLD_PLACE_GENERATOR

#include <iostream>
#include <string>

#include "WorldController.h"

class BoundaryLine
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
        const size_t &info_level);

    float line_start_position;
    float line_end_position;
    float line_height;
    float line_real_height;

    BoundaryLine* prev_line;
    BoundaryLine* next_line;
};

class BoundaryLineList
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
        const size_t &info_level);

    float boundary_length_;
    BoundaryLine* boundary_line_list_;
};

class BoundaryLineListManager
{
public:
    BoundaryLineListManager()
    {
    }

    bool reset();

    bool setBoundaryPolygon(
        const EasyPolygon2D &boundary_polygon);

    bool getMaxHeight(
        const size_t &boundary_idx,
        const BoundaryLine &boundary_line,
        float &max_height);

    bool insertBoundaryLine(
        const size_t &boundary_idx,
        const BoundaryLine &new_boundary_line);

    bool outputInfo(
        const size_t &info_level);

    std::vector<BoundaryLineList> boundary_line_list_vec_;
};

enum PointOccupancyState
{
    Free = 0,
    Used = 1
};

class PointMatrix
{
public:
    PointMatrix()
    {
        reset();
    }

    bool reset();

    bool setBoundaryPosition(
        const float &boundary_start_x,
        const float &boundary_start_y,
        const float &boundary_width,
        const float &boundary_height);

    bool setSplitEdgeLength(
        const float &split_edge_length);

    bool getPointPosition(
        const size_t &point_x_idx,
        const size_t &point_y_idx,
        EasyPoint2D &point_position);

    bool setAllPointOccupancyState(
        const PointOccupancyState &point_occupancy_state);

    bool setPartPointOccupancyState(
        const size_t &point_x_idx_start,
        const size_t &point_x_idx_end,
        const size_t &point_y_idx_start,
        const size_t &point_y_idx_end,
        const PointOccupancyState &point_occupancy_state);

    bool getPointIdxRangeFromRect(
        const float &rect_start_position_x,
        const float &rect_start_position_y,
        const float &rect_width,
        const float &rect_height,
        size_t &point_x_idx_start,
        size_t &point_x_idx_end,
        size_t &point_y_idx_start,
        size_t &point_y_idx_end);

    bool setRectPointOccupancyState(
        const float &rect_start_position_x,
        const float &rect_start_position_y,
        const float &rect_width,
        const float &rect_height,
        const PointOccupancyState &point_occupancy_state);

private:
    bool isValid();

    bool is_boundary_position_set_;
    float boundary_start_x_;
    float boundary_start_y_;
    float boundary_width_;
    float boundary_height_;

    bool is_split_edge_length_set_;
    size_t split_edge_length_;

    size_t x_direction_point_num_;
    size_t y_direction_point_num_;

    std::vector<std::vector<PointOccupancyState>> point_matrix_;
};

class WorldPlaceGenerator
{
public:
    WorldPlaceGenerator()
    {
    }

    bool reset();

    bool setWallBoundaryPolygon(
        const EasyPolygon2D &wall_boundary_polygon);

    bool setPersonNum(
        const size_t &person_num);

    bool setRoomNum(
        const size_t &room_num);

    bool generateWorld();

private:
    bool isReadyToGenerate();

    bool generateWall();
    bool generateRoom();

public:
    WorldController world_controller_;
    BoundaryLineListManager boundary_line_list_manager_;
    PointMatrix point_matrix_;

    bool is_wall_boundary_polygon_set_;
    EasyPolygon2D wall_boundary_polygon_;

    bool is_person_num_set_;
    size_t person_num_;

    bool is_room_num_set_;
    size_t room_num_;
};

#endif //WORLD_PLACE_GENERATOR
