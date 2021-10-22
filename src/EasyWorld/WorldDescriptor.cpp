#include "WorldDescriptor.h"

bool RoomProp::reset()
{
    name = "Name Undefined";
    target_width = -1;
    real_width = -1;
    target_height = -1;
    real_height = -1;

    roomcontainer_id_ = 0;
    room_id_ = 0;

    return true;
}

bool RoomProp::setRoomProp(
    const std::string &room_name,
    const float &room_target_width,
    const float &room_target_height)
{
    reset();

    if(room_target_width <= 0 || room_target_height <= 0)
    {
        std::cout << "RoomProp::setRoomProp : " << std::endl <<
          "Input :\n" <<
          "\troom_name = " << room_name << std::endl <<
          "\troom_target_size = [" << room_target_width << "," <<
          room_target_height << "]" << std::endl <<
          "room target size not valid!" << std::endl;

        return false;
    }

    name = room_name;
    target_width = room_target_width;
    target_height = room_target_height;

    return true;
}

bool RoomContainerProp::reset()
{
    return true;
}

bool WorldDescriptor::reset()
{
    return true;
}

