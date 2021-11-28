#ifndef UNIT_NODE_H
#define UNIT_NODE_H

#include "export_library_global.h"

#include "EasyWorld/EasyNode.h"
#include "EasyShape/EasyShape.h"

#define PI 3.1415926535898

class LIBRARY_EXPORT UnitNode
{
public:
    UnitNode()
    {
        parent = nullptr;
    }
    ~UnitNode();

    bool reset();

    UnitNode* findChild(
        const size_t &child_id,
        const NodeType &child_type);

    UnitNode* findFromAllChild(
        const size_t &child_id,
        const NodeType &child_type);

    bool haveThisChild(
        const size_t &child_id,
        const NodeType &child_type);

    bool createChild(
        const std::string &child_name,
        const size_t &child_id,
        const NodeType &child_type);

    bool addChild(
        UnitNode* child_node);

    bool removeChild(
        const size_t &child_id,
        const NodeType &child_type);

    bool removeChildButRemainData(
        const size_t &child_id,
        const NodeType &child_type);

    bool removeAllChild();

    bool setPositionOnParentPolygonByPolygonParam(
        const float& point_param_on_parent_polygon,
        const float& new_dist_to_parent_polygon,
        const float& new_target_width,
        const float& new_target_height,
        const float& new_left_angle,
        const float& new_right_angle);

    bool setPositionOnParentPolygonByLineParam(
        const size_t& parent_polygon_line_idx,
        const float& point_param_on_line,
        const float& new_dist_to_parent_polygon,
        const float& new_target_width,
        const float& new_target_height,
        const float& new_left_angle,
        const float& new_right_angle);

    bool setPositionOnParentPolygonByLength(
        const float& point_length,
        const float& new_dist_to_parent_polygon,
        const float& new_target_width,
        const float& new_target_height,
        const float& new_left_angle,
        const float& new_right_angle);

    bool setPositionOnParentPolygonByPosition(
        const EasyPoint2D& point_position,
        const float& new_dist_to_parent_polygon,
        const float& new_target_width,
        const float& new_target_height,
        const float& new_left_angle,
        const float& new_right_angle);

    bool updatePolygon();

    bool outputInfo(
        const size_t &info_level) const;

    std::string name;
    size_t id;
    NodeType type;

    EasyPolygon2D boundary_polygon;
    size_t right_down_point_idx;
    size_t right_up_point_idx;
    size_t left_up_point_idx;

    UnitNode* parent;
    std::vector<UnitNode*> child_vec;

    EasyPolygonPoint2D polygon_point_on_parent_polygon;
    float dist_to_parent_polygon;
    float target_width;
    float target_height;
    float left_angle;
    float right_angle;
    float real_width;
    float real_height;
};

#endif // UNIT_NODE_H
