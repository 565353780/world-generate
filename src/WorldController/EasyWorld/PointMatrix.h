#ifndef POINT_MATRIX_H
#define POINT_MATRIX_H

#include "export_library_global.h"

#include "EasyShape/EasyShape.h"

enum PointOccupancyState
{
    PointFree = 0,
    PointUsed = 1
};

class LIBRARY_EXPORT PointMatrix
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

#endif //POINT_MATRIX_H
