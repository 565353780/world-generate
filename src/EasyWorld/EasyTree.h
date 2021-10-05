#ifndef EASY_TREE_H
#define EASY_TREE_H

#include <iostream>
#include <string>

#include "EasyNode.h"

// Tree Struct :
// World
// Boundary World
// Boundary Line & Space
// Room World
// Room Line & Space
// Furniture World
// Furniture Line & Space

class EasyTree
{
public:
    EasyTree()
    {
        root_ = nullptr;
    }

    bool reset();

    bool createWorld();

    EasyNode* findNode(
        const size_t &id,
        const NodeType &type);

    bool createWall(
        const size_t &wall_id,
        const NodeType &wall_type);

    bool createWallBoundary(
        const size_t &wall_id,
        const NodeType &wall_type,
        const EasyPolygon2D &wall_boundary_polygon);

    bool createRoom(
        const size_t &room_id,
        const size_t &on_wall_id,
        const NodeType &on_wall_type,
        const size_t &wall_boundary_id);

    bool outputInfo() const;

private:
    EasyNode *root_;

    std::vector<size_t> outerwall_id_vec_;
    std::vector<size_t> innerwall_id_vec_;
    std::vector<size_t> room_id_vec_;
    std::vector<size_t> furniture_id_vec_;
};

#endif //EASY_TREE_H
