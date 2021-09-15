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

    EasyRect2D rect;
    std::vector<size_t> sorted_room_idx_line;
};

#endif //EASY_ROOM_LINE_H
