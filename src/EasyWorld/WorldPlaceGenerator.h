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

    size_t place_idx;
    float line_start_position;
    float line_end_position;
    float line_width;
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
        const BoundaryLine &new_boundary_line,
        BoundaryLine &valid_boundary_line);

    bool outputInfo(
        const size_t &info_level);

    size_t current_place_idx_;
    std::vector<BoundaryLineList> boundary_line_list_vec_;
};

enum PointOccupancyState
{
    PointFree = 0,
    PointUsed = 1
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

    bool setBoundaryPolygon(
        const EasyPolygon2D &boundary_polygon);

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

    bool getMaxMinDistPointToPolygonVec(
        const std::vector<EasyPolygon2D> &polygon_vec,
        size_t &max_min_dist_point_x_idx,
        size_t &max_min_dist_point_y_idx);

    bool getMaxFreeRect(
        const std::vector<EasyPolygon2D> &polygon_vec,
        float &max_free_rect_start_position_x,
        float &max_free_rect_start_position_y,
        float &max_free_rect_width,
        float &max_free_rect_height);

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
        free_room_error_max_ = 1;

        team_x_direction_person_num_ = 2 * (std::rand() % 3 + 1);
        team_y_direction_person_num_ = 2 * (std::rand() % 3 + 1);
        team_dist_ = 0.5;
        person_edge_ = 2.0;
    }

    bool reset();

    bool setWallBoundaryPolygon(
        const EasyPolygon2D &wall_boundary_polygon);

    bool generateWorld(
        WorldController &world_controller);

    bool placeWallRoomContainer(
        WorldController &world_controller,
        const size_t &boundary_idx,
        const float &roomcontainer_start_position,
        const float &roomcontainer_width,
        const float &roomcontainer_height);

    bool generateFreeRoomContainer(
        WorldController &world_controller,
        const size_t &team_x_direction_person_num,
        const size_t &team_y_direction_person_num,
        const float &team_dist,
        const float &person_edge);

// private:
    bool isReadyToGenerate();

    bool createNewWorld(
        WorldController &world_controller);

    bool generateWall(
        WorldController &world_controller);

    bool generateRoom(
        WorldController &world_controller);

public:
    BoundaryLineListManager boundary_line_list_manager_;
    PointMatrix point_matrix_;

    bool is_wall_boundary_polygon_set_;
    EasyPolygon2D wall_boundary_polygon_;

    float free_room_error_max_;

    size_t current_new_room_id_;

    size_t team_x_direction_person_num_;
    size_t team_y_direction_person_num_;
    float team_dist_;
    float person_edge_;
};

#endif //WORLD_PLACE_GENERATOR
