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

    bool createWorld(
        const float &world_center_x,
        const float &world_center_y);

    bool createNode(
        const size_t &node_id,
        const NodeType &node_type,
        const size_t &parent_node_id,
        const NodeType &parent_node_type,
        const size_t &parent_boundary_node_id);

    EasyNode* findNode(
        const size_t &id,
        const NodeType &type);

    bool setNodeAxisCenterPositionInParent(
        const size_t &node_id,
        const NodeType &node_type,
        const EasyPoint2D &axis_new_center_position_in_parent,
        const bool &is_allow_x_direction_move_in_parent_axis,
        const bool &is_allow_y_direction_move_in_parent_axis);

    bool setNodeAxisCenterPositionInWorld(
        const size_t &node_id,
        const NodeType &node_type,
        const EasyPoint2D &axis_new_center_position_in_world,
        const bool &is_allow_x_direction_move_in_parent_axis,
        const bool &is_allow_y_direction_move_in_parent_axis);

    bool setNodeBoundaryPolygon(
        const size_t &node_id,
        const NodeType &node_type,
        const EasyPolygon2D &node_boundary_polygon);

    bool setNodeBoundaryPolygonPointPosition(
        const size_t &node_id,
        const NodeType &node_type,
        const size_t &point_idx,
        const EasyPoint2D &point_new_position_in_world);

    bool outputInfo() const;

private:
    bool isNodeInParentSpace(
        EasyNode* node);

    bool isNodeInParentChildNodeSpace(
        EasyNode* node);

    bool isNodeSpaceValid(
        EasyNode* node);

private:
    EasyNode *root_;

    std::vector<size_t> outerwall_id_vec_;
    std::vector<size_t> innerwall_id_vec_;
    std::vector<size_t> room_id_vec_;
    std::vector<size_t> furniture_id_vec_;
};

#endif //EASY_TREE_H
