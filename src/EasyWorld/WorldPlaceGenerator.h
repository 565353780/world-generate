#ifndef WORLD_PLACE_GENERATOR
#define WORLD_PLACE_GENERATOR

#include <iostream>
#include <string>

#include "WorldController.h"

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

    bool is_person_num_set_;
    size_t person_num_;

    bool is_room_num_set_;
    size_t room_num_;
};

#endif //WORLD_PLACE_GENERATOR
