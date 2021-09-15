#include "EasyRoom.h"

bool EasyRoom::reset()
{
    name = "";
    is_on_boundary = false;
    position.setPosition(0, 0);
    boundary.reset();
    neighboor_room_idx_vec.clear();

    return true;
}

bool EasyRoom::haveThisNeighboor(
    const size_t &neighboor_room_id)
{
    if(neighboor_room_idx_vec.size() == 0)
    {
        return false;
    }

    if(std::find(neighboor_room_idx_vec.cbegin(), neighboor_room_idx_vec.cend(), neighboor_room_id) ==
        neighboor_room_idx_vec.cend())
    {
        return false;
    }

    return true;
}

bool EasyRoom::addNeighboorRoomIdx(
    const size_t &room_idx)
{
    if(haveThisNeighboor(room_idx))
    {
        std::cout << "EasyRoom::addNeighboorRoomID : " <<
          "this room already has the neighboor room-" << room_idx << "!" << std::endl;

        return true;
    }

    neighboor_room_idx_vec.emplace_back(room_idx);

    return true;
}

