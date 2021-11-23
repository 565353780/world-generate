#ifndef WALL_GENERATOR_H
#define WALL_GENERATOR_H

#include "EasyShape/EasyShape.h"
#include "EasyWorld/EasyWorld.h"

class WallGenerator
{
public:
    WallGenerator()
    {
    }

    bool reset();

    bool createWall(
        const NodeType& wall_type);

    bool addPointForWall(
        const NodeType& wall_type,
        const size_t& wall_idx,
        const float& point_x,
        const float& point_y);

// private:
    std::vector<EasyPolygon2D> outerwall_vec_;
    std::vector<EasyPolygon2D> innerwall_vec_;
};

#endif //WALL_GENERATOR_H
