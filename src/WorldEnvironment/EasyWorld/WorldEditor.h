#ifndef WORLD_EDITOR_H
#define WORLD_EDITOR_H

#include "export_library_global.h"

#include "WorldDescriptor.h"

class LIBRARY_EXPORT WorldEditor
{
public:
    WorldEditor()
    {
    }

    bool reset();

    bool setWallRoomContainerPosition(
        WorldController &world_controller,
        WorldPlaceGenerator &world_place_generator,
        const size_t &wall_roomcontainer_id,
        const float &new_position_x,
        const float &new_position_y,
        const float &mouse_pos_x_direction_delta);

private:
    WorldDescriptor world_descriptor_;
};

#endif //WORLD_EDITOR_H
