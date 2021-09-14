#ifndef SPACE_CONTROLLER_H
#define SPACE_CONTROLLER_H

#include <iostream>
#include <string>

#include "BoundaryController.h"

class SpaceController
{
public:
    SpaceController()
    {
    }

    bool CreateSpace(
        const std::string &space_name);
};

#endif //SPACE_CONTROLLER_H
