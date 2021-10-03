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
    EasyNode(){}
    ~EasyNode();

    bool reset();

    bool setParent(
        EasyNode* parent);

    bool findThisChild(
        const size_t &child_id,
        size_t &child_idx);

    bool haveThisChild(
        const size_t &child_id);

    bool createChild(
        const size_t &child_id);

    bool setChildType(
        const size_t &child_id,
        const NodeType &child_type);

    bool setChildAxisInParent(
        const size_t &child_id,
        const float &child_axis_center_x_in_parent,
        const float &child_axis_center_y_in_parent,
        const float &child_axis_x_direction_x_in_parent,
        const float &child_axis_x_direction_y_in_parent);

public:
    size_t id_;

    NodeType type_;

    EasyNode* parent_;

    std::vector<EasyNode*> child_vec_;

    EasyAxis2D axis_;
};

#endif //EASY_NODE_H
