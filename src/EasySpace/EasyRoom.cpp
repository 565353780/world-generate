#include "EasyRoom.h"

bool EasyRoom::reset()
{
    id = 0;
    name = "";
    is_on_boundary = false;
    position.setPosition(0, 0);
    boundary.reset();
    neighboor_room_id_vec.clear();

    return true;
}

bool EasyRoom::findPositionOnBoundary(
    const EasyPolygon2D &boundary)
{
    if(is_on_boundary)
    {
        std::cout << "EasyRoom::findPositionOnBoundary : " <<
          "room-" << id << " already on boundary!" << std::endl;

        return true;
    }

    if(boundary.point_list.size() == 0)
    {
        std::cout << "EasyRoom::findPositionOnBoundary : " <<
          "boundary is empty!" << std::endl;

        return false;
    }

    if(boundary.point_list.size() == 1)
    {
        position = boundary.point_list[0];
        is_on_boundary = true;

        return true;
    }

    return false;
}

bool EasyRoom::haveThisNeighboor(
    const size_t &neighboor_room_id)
{
    if(neighboor_room_id_vec.size() == 0)
    {
        return false;
    }

    if(std::find(neighboor_room_id_vec.cbegin(), neighboor_room_id_vec.cend(), neighboor_room_id) ==
        neighboor_room_id_vec.cend())
    {
        return false;
    }

    return true;
}

bool EasyRoom::addNeighboorRoomID(
    const size_t &room_id)
{
    if(haveThisNeighboor(room_id))
    {
        std::cout << "EasyRoom::addNeighboorRoomID : " <<
          "the room-" << id << " already has the neighboor room-" << room_id << "!" << std::endl;

        return true;
    }

    neighboor_room_id_vec.emplace_back(room_id);

    return true;
}

