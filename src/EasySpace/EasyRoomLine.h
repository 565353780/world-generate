#ifndef EASY_ROOM_LINE_H
#define EASY_ROOM_LINE_H

#include <iostream>
#include <string>

#include "EasyShape/EasyShape.h"
#include "EasyRoom.h"

class EasyRoomLine
{
public:
    EasyRoomLine()
    {
    }

    bool reset();

    bool setTargetSize(
        const float &width,
        const float &height);

    float target_area;
    float real_area;
    float target_width;
    float real_width;
    float target_height;
    float real_height;

    EasyRect2D rect;
    std::vector<size_t> sorted_room_idx_line;
};

#endif //EASY_ROOM_LINE_H
