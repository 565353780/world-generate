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

