#ifndef EASY_NODE_H
#define EASY_NODE_H

#include <iostream>
#include <string>

#include "EasyWorld/EasyAxis2D.h"

#include "EasyShape/EasyShape.h"

enum NodeType
{
    Free = 0,
    World = 1,
    OuterWall = 2,
    InnerWall = 3,
    Room = 4,
    Door = 5,
    Furniture = 6,
    Space = 7
};

class EasyNode
{
public:
    EasyNode() {}
    ~EasyNode();

    bool reset();

    bool setID(
        const size_t &id);

    bool setNodeType(
        const NodeType& type);

    bool setAxis(
        const float &axis_center_x_in_parent,
        const float &axis_center_y_in_parent,
        const float &axis_x_direction_x_in_parent,
        const float &axis_x_direction_y_in_parent);

    bool setParent(
        EasyNode* parent);

    bool findChild(
        const size_t &child_id,
        const NodeType &child_type,
        size_t &child_idx);

    EasyNode* findFromAllChild(
        const size_t &child_id,
        const NodeType &child_type);

    bool haveThisChild(
        const size_t &child_id,
        const NodeType &child_type);

    bool createChild(
        const size_t &child_id,
        const NodeType &child_type);

    bool removeChild(
        const size_t &child_id,
        const NodeType &child_type);

    bool removeChildButRemainData(
        const size_t &child_id,
        const NodeType &child_type);

    bool removeAllChild();

    bool setChildType(
        const size_t &child_id,
        const NodeType &child_type);

    bool setChildAxisInParent(
        const size_t &child_id,
        const NodeType &child_type,
        const float &child_axis_center_x_in_parent,
        const float &child_axis_center_y_in_parent,
        const float &child_axis_x_direction_x_in_parent,
        const float &child_axis_x_direction_y_in_parent);

    const size_t& getID() { return id_; }
    const NodeType& getNodeType() { return type_; }
    const EasyAxis2D& getAxis() { return axis_; }

private:
    size_t id_;

    NodeType type_;

    EasyNode* parent_;

    std::vector<EasyNode*> child_vec_;

    EasyAxis2D axis_;
};

#endif //EASY_NODE_H
