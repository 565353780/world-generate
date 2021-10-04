#ifndef WORLD_CONTROLLER_H
#define WORLD_CONTROLLER_H

#include <iostream>
#include <string>

#include "EasyTree.h"

class WorldController
{
public:
    WorldController() {}

    bool reset();

    bool createWorld();

    bool createWall(
        const size_t &wall_id,
        const NodeType &wall_type);

    bool createWallBoundary(
        const size_t &wall_id,
        const NodeType &wall_type,
        const EasyPolygon2D &wall_boundary_polygon);

private:
    EasyTree world_tree_;
};

#endif //WORLD_CONTROLLER_H
