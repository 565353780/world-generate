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

private:
    WorldController world_controller_;

    bool is_wall_boundary_polygon_set_;
    EasyPolygon2D wall_boundary_polygon_;

    bool is_person_num_set_;
    size_t person_num_;

    bool is_room_num_set_;
    size_t room_num_;
};

#endif //WORLD_GENERATOR_H
