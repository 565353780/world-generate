#include "EasyRoomLine.h"

bool EasyRoomLine::reset()
{
    resetSize();

    is_circle = false;

    sorted_room_idx_line.clear();

    return true;
}

bool EasyRoomLine::resetSize()
{
    target_area = -1;
    real_area = -1;
    target_width = -1;
    real_width = -1;
    target_height = -1;
    real_height = -1;

    return true;
}

bool EasyRoomLine::setTargetSize(
    const float &width,
    const float &height)
{
    target_width = width;
    target_height = height;
    target_area = target_width * target_height;

    return true;
}

bool EasyRoomLine::haveThisRoom(
    const size_t &room_idx)
{
    if(sorted_room_idx_line.size() == 0)
    {
        return false;
    }

    for(const size_t &exist_room_idx : sorted_room_idx_line)
    {
        if(exist_room_idx == room_idx)
        {
            return true;
        }
    }

    return false;
}

