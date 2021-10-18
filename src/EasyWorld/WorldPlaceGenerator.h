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
    }

    float line_start_position;
    float line_end_position;
};

class BoundaryUnUsedLine
{
public:
    BoundaryUnUsedLine()
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

    bool isBoundaryLineUnused(
        const BoundaryLine &new_boundary_line);

    bool splitBoundaryLine(
        const BoundaryLine &new_boundary_line);

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

    bool is_wall_boundary_polygon_set_;
    EasyPolygon2D wall_boundary_polygon_;
    std::vector<float> wall_boundary_length_vec_;
    std::vector<BoundaryUnUsedLine> wall_boundary_unused_line_vec_;

    bool is_person_num_set_;
    size_t person_num_;

    bool is_room_num_set_;
    size_t room_num_;
};

#endif //WORLD_PLACE_GENERATOR
