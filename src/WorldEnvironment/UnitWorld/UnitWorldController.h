#ifndef UNIT_WORLD_CONTROLLER_H
#define UNIT_WORLD_CONTROLLER_H

#include "UnitTree.h"

class UnitWorldController
{
public:
    UnitWorldController()
    {
    }

    bool reset();

    bool createWorld();

    bool createWall(
        const std::string& wall_name,
        const size_t& wall_id,
        const NodeType& wall_type);

    bool createRoom(
        const std::string& room_name,
        const size_t& room_id,
        const NodeType& room_type,
        const size_t& on_wall_id,
        const NodeType& on_wall_type);

    UnitTree unit_tree_;
};

#endif // UNIT_WORLD_CONTROLLER_H
