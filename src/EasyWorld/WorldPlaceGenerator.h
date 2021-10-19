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

    bool insertUsedBoundaryLine(
        const BoundaryLine &new_boundary_line);

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

    std::vector<BoundaryLineList> boundary_line_list_vec_;
};

class BoundaryUnusedLine
{
public:
    BoundaryUnusedLine()
    {
    }

    bool setBoundaryLength(
        const float &boundary_length);

    bool haveThisUnusedPosition(
        const float &boundary_position,
        size_t &position_on_unused_line_idx);

    bool isThisPositionUnused(
        const float &boundary_position);

    bool getNearestUnusedLine(
        const BoundaryLine &new_boundary_line,
        BoundaryLine &nearest_unused_boundary_line,
        size_t &nearest_unused_boundary_line_idx);

    bool splitBoundaryLine(
        const BoundaryLine &new_boundary_line);

    bool generateWallRoomContainer(
        const float &roomcontainer_start_position,
        const float &roomcontainer_width,
        const float &roomcontainer_height);

    float boundary_length_;
    std::vector<BoundaryLine> boundary_unused_line_vec;
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

    bool is_wall_boundary_polygon_set_;
    EasyPolygon2D wall_boundary_polygon_;

    bool is_person_num_set_;
    size_t person_num_;

    bool is_room_num_set_;
    size_t room_num_;
};

#endif //WORLD_PLACE_GENERATOR
