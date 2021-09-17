#include "EasyRoom.h"

bool EasyRoom::reset()
{
    name = "";

    target_area = -1;
    real_area = -1;
    target_width = -1;
    real_width = -1;
    target_height = -1;
    real_height = -1;

    position.setPosition(0, 0);

    boundary.reset();
    boundary_near_vec.clear();

    neighboor_room_idx_vec.clear();

    return true;
}

bool EasyRoom::setTargetSize(
    const float &width,
    const float &height)
{
    target_width = width;
    target_height = height;
    target_area = target_width * target_height;

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

