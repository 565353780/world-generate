#ifndef UNIT_TREE_H
#define UNIT_TREE_H

#include "export_library_global.h"

#include "UnitNode.h"

class LIBRARY_EXPORT UnitTree
{
public:
    UnitTree()
    {
        root = nullptr;
    }
    ~UnitTree();

    bool reset();

    bool resetButRemainWall();

    bool createTree();

    UnitNode* findNode(
        const size_t &id,
        const NodeType &type);

    bool createNode(
        const std::string &node_name,
        const size_t &node_id,
        const NodeType &node_type,
        const size_t &parent_node_id,
        const NodeType &parent_node_type);

    bool setBoundaryPolygon(
        const size_t& node_id,
        const NodeType& node_type,
        const EasyPolygon2D& new_boundary_polygon);

    bool setNodePositionOnParentPolygonByPolygonParam(
        const size_t& node_id,
        const NodeType& node_type,
        const float& point_param_on_parent_polygon,
        const float& new_dist_to_parent_polygon,
        const float& new_target_width,
        const float& new_target_height,
        const float& new_left_angle,
        const float& new_right_angle);

    bool setNodePositionOnParentPolygonByLineParam(
        const size_t& node_id,
        const NodeType& node_type,
        const size_t& parent_polygon_line_idx,
        const float& point_param_on_line,
        const float& new_dist_to_parent_polygon,
        const float& new_target_width,
        const float& new_target_height,
        const float& new_left_angle,
        const float& new_right_angle);

    bool setNodePositionOnParentPolygonByLength(
        const size_t& node_id,
        const NodeType& node_type,
        const float& point_length,
        const float& new_dist_to_parent_polygon,
        const float& new_target_width,
        const float& new_target_height,
        const float& new_left_angle,
        const float& new_right_angle);

    bool setNodePositionOnParentPolygonByPosition(
        const size_t& node_id,
        const NodeType& node_type,
        const EasyPoint2D& point_position,
        const float& new_dist_to_parent_polygon,
        const float& new_target_width,
        const float& new_target_height,
        const float& new_left_angle,
        const float& new_right_angle);

    bool outputInfo(
        const size_t& info_level) const;

    UnitNode* root;
};

#endif // UNIT_TREE_H
