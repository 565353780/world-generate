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

    EasyNode* findNode(
        const size_t &node_id,
        const NodeType &node_type);

    bool getWallNodeVec(
        std::vector<EasyNode*> &wall_node_vec);

    bool getWallBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &wall_boundary_node_vec_vec);

    bool getWallSpaceNodeVec(
        std::vector<EasyNode*> &wall_space_node_vec);

    bool getRoomNodeVec(
        std::vector<EasyNode*> &wall_node_vec);

    bool outputInfo();

private:
    EasyTree world_tree_;

    std::vector<std::pair<size_t, NodeType>> wall_pair_vec_;
    std::vector<std::pair<size_t, NodeType>> room_pair_vec_;
    std::vector<std::pair<size_t, NodeType>> furniture_pair_vec_;
};

#endif //WORLD_CONTROLLER_H