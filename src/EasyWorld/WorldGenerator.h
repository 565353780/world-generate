#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <iostream>
#include <string>

#include "WorldController.h"

class WorldGenerator
{
public:
    WorldGenerator()
    {
        is_wall_boundary_polygon_set_ = false;
        is_person_num_set_ = false;
        is_room_num_set_ = false;
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

    bool isWallBoundaryStartPositionValid(
        const size_t &wall_boundary_idx,
        const float &wall_boundary_start_position,
        float &max_line_width,
        float &max_line_height);

    bool isWallBoundaryLineValid(
        const size_t &wall_boundary_idx,
        const std::vector<float> &wall_boundary_line,
        float &max_line_height);

    bool generateWall();
    bool generateRoom();

private:
    WorldController world_controller_;

    bool is_wall_boundary_polygon_set_;
    EasyPolygon2D wall_boundary_polygon_;
    std::vector<float> wall_boundary_length_vec_;
    //line_start, line_end, room_height
    std::vector<std::vector<std::vector<float>>> wall_boundary_used_line_vec_vec_;

    bool is_person_num_set_;
    size_t person_num_;

    bool is_room_num_set_;
    size_t room_num_;
};

#endif //WORLD_GENERATOR_H
