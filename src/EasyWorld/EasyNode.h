#ifndef EASY_NODE_H
#define EASY_NODE_H

#include <iostream>
#include <string>

#include "EasyWorld/EasyAxis2D.h"

#include "EasyShape/EasyShape.h"

enum NodeType
{
    NodeFree = 0,
    World = 1,
    OuterWall = 2,
    InnerWall = 3,
    RoomContainer = 4,
    WallRoom = 5,
    FreeRoom = 6,
    Team = 7,
    Person = 8,
    Furniture = 9,
    Boundary = 10,
    Door = 11,
    Space = 12
};

class EasyNode
{
public:
    EasyNode()
    {
        parent_ = nullptr;
    }

    ~EasyNode();

    bool reset();

    bool setID(
        const size_t &id);

    bool setNodeType(
        const NodeType& type);

    bool setAxisInParent(
        const float &axis_center_x_in_parent,
        const float &axis_center_y_in_parent,
        const float &axis_x_direction_x_in_parent,
        const float &axis_x_direction_y_in_parent);

    bool setAxisInWorld(
        const float &axis_center_x_in_world,
        const float &axis_center_y_in_world,
        const float &axis_x_direction_x_in_world,
        const float &axis_x_direction_y_in_world);

    bool updateAxisInWorldFromParent();

    bool setParent(
        EasyNode* parent);

    bool setBoundaryPolygon(
        const EasyPolygon2D &boundary_polygon);

    bool setBoundaryPolygonPointPosition(
        const size_t &point_idx,
        const EasyPoint2D &point_new_position_in_world);

    EasyNode* findChild(
        const size_t &child_id,
        const NodeType &child_type);

    EasyNode* findFromAllChild(
        const size_t &child_id,
        const NodeType &child_type);

    bool haveThisChild(
        const size_t &child_id,
        const NodeType &child_type);

    bool createChild(
        const size_t &child_id,
        const NodeType &child_type);

    bool addChild(
        EasyNode* child_node);

    bool removeChild(
        const size_t &child_id,
        const NodeType &child_type);

    bool removeChildButRemainData(
        const size_t &child_id,
        const NodeType &child_type);

    bool removeAllChild();

    bool setChildAxisInParent(
        const size_t &child_id,
        const NodeType &child_type,
        const float &child_axis_center_x_in_parent,
        const float &child_axis_center_y_in_parent,
        const float &child_axis_x_direction_x_in_parent,
        const float &child_axis_x_direction_y_in_parent);

    bool setChildBoundaryPolygon(
        const size_t &child_id,
        const NodeType &child_type,
        const EasyPolygon2D &child_boundary_polygon);

    bool getPointInNode(
        const EasyPoint2D &point_in_world,
        EasyPoint2D &point_in_node);

    bool getPointInWorld(
        const EasyPoint2D &point_in_node,
        EasyPoint2D &point_in_world);

    const size_t& getID() const { return id_; }
    const NodeType& getNodeType() const { return type_; }
    EasyNode* getParent() { return parent_; }
    const std::vector<EasyNode*>& getChildNodeVec() const { return child_vec_; }
    const EasyAxis2D& getAxisInParent() const { return axis_in_parent_; }
    const EasyAxis2D& getAxisInWorld() const { return axis_in_world_; }
    const EasyPolygon2D& getBoundaryPolygon() const { return boundary_polygon_; }

    bool outputInfo(
        const size_t &info_level) const;

private:
    size_t id_;

    NodeType type_;

    EasyNode* parent_;

    std::vector<EasyNode*> child_vec_;

    EasyAxis2D axis_in_parent_;
    EasyAxis2D axis_in_world_;

    EasyPolygon2D boundary_polygon_;
};

#endif //EASY_NODE_H
