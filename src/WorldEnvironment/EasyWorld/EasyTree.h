#ifndef EASY_TREE_H
#define EASY_TREE_H

#include "export_library_global.h"

#include "EasyNode.h"

class LIBRARY_EXPORT EasyTree
{
public:
    EasyTree()
    {
        root_ = nullptr;
    }
    ~EasyTree();

    bool reset();

    bool resetButRemainWall();

    bool createWorld(
        const std::string &world_name,
        const float &world_center_x,
        const float &world_center_y);

    bool createNode(
        const std::string &node_name,
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
        const bool &is_allow_y_direction_move_in_parent_axis,
        const bool &is_force_move);

    bool setNodeAxisCenterPositionInWorld(
        const size_t &node_id,
        const NodeType &node_type,
        const EasyPoint2D &axis_new_center_position_in_world,
        const bool &is_allow_x_direction_move_in_parent_axis,
        const bool &is_allow_y_direction_move_in_parent_axis,
        const bool &is_force_move);

    bool setNodeAxisXDirectionInParent(
        const size_t &node_id,
        const NodeType &node_type,
        const EasyPoint2D &axis_new_x_direction_in_parent,
        const bool &is_force_move);

    bool setNodeAxisXDirectionInWorld(
        const size_t &node_id,
        const NodeType &node_type,
        const EasyPoint2D &axis_new_x_direction_in_world,
        const bool &is_force_move);

    bool setNodeAxisInParent(
        const size_t &node_id,
        const NodeType &node_type,
        const EasyAxis2D &axis_in_parent,
        const bool &is_force_move);

    bool setNodeAxisInWorld(
        const size_t &node_id,
        const NodeType &node_type,
        const EasyAxis2D &axis_in_world,
        const bool &is_force_move);

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
    EasyNode* root_;
};

#endif //EASY_TREE_H
