#ifndef WORLD_DESCRIPTOR_H
#define WORLD_DESCRIPTOR_H

#include <iostream>
#include <string>

#include "WorldEditer.h"

class RoomContainerProp
{
public:
    RoomContainerProp()
    {
    }

    bool reset();

    size_t room_num;
    std::vector<float> room_target_area_vec;
    std::vector<float> room_real_area_vec;
    float room_height;
};

class WorldDescriptor
{
public:
    WorldDescriptor()
    {
    }

    bool reset();

    bool addRoomContainer(
        const size_t &room_num,
        const float &room_width,
        const float &room_height);

    WorldEditer world_editer_;
};

#endif //WORLD_DESCRIPTOR_H
