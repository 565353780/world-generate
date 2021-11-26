#ifndef UNIT_NODE_H
#define UNIT_NODE_H

#include "export_library_global.h"

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
    Window = 12,
    Space = 13
};

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

    bool getPointPosition(
        const float& point_param,
        EasyPoint2D& point_position);

    bool getPointParam(
        const EasyPoint2D &point_position,
        float& point_param);

    bool outputInfo(
        const size_t &info_level) const;

    std::string name;
    size_t id;
    NodeType type;
    UnitNode* parent;
    std::vector<UnitNode*> child_vec;
    EasyPolygon2D boundary_polygon;
    float param_on_parent_polygon;
};

#endif // UNIT_NODE_H
