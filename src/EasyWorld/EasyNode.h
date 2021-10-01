#ifndef EASY_NODE_H
#define EASY_NODE_H

#include <iostream>
#include <string>

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

    bool setChildPositionInParent(
        const size_t &child_id,
        const EasyPoint2D &child_position_in_parent);

public:
    size_t id_;

    NodeType type_;

    EasyNode* parent_;

    std::vector<EasyNode*> child_vec_;

    EasyPoint2D position_in_parent_;
    EasyPoint2D direction_in_parent_;

    EasyPoint2D position_;
    EasyPoint2D direction_;
};

#endif //EASY_NODE_H
