#ifndef WORLD_DESCRIPTOR_H
#define WORLD_DESCRIPTOR_H

#include <iostream>
#include <string>

#include "WorldController.h"
#include "WorldPlaceGenerator.h"

class RoomProp
{
public:
    RoomProp()
    {
    }

    bool reset();

    bool setRoomProp(
        const std::string &room_name,
        const float &room_target_width,
        const float &room_target_height);

    std::string name;
    float target_width;
    float target_height;

    size_t roomcontainer_id_;
    size_t room_id_;

    float real_width;
    float real_height;
};

class RoomContainerProp
{
public:
    RoomContainerProp()
    {
    }

    bool reset();

    std::vector<RoomProp> room_prop_vec;

    size_t roomcontainer_id_;
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
};

#endif //WORLD_DESCRIPTOR_H
