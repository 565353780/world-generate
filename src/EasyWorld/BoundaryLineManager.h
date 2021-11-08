#ifndef BOUNDARY_LINE_MANAGER_H
#define BOUNDARY_LINE_MANAGER_H

#include "EasyShape/EasyShape.h"

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

    size_t line_room_num;
    std::vector<std::string> room_name_vec;

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

class BoundaryLineManager
{
public:
    BoundaryLineManager()
    {
    }

    bool reset();
};

#endif //BOUNDARY_LINE_MANAGER_H
