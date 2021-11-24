#ifndef WORLD_REWARD_H
#define WORLD_REWARD_H

#include "export_library_global.h"

#include "EasyWorld/WorldController.h"

class LIBRARY_EXPORT WorldReward
{
public:
    WorldReward()
    {
    }

    bool reset();

    bool getReward(
        WorldController &world_controller,
        float &reward);

private:
    bool getSpaceUtilizationReward(
        WorldController &world_controller,
        float &space_utilization_reward);

    bool getNeighboorReward(
        WorldController &world_controller,
        float &neighboor_reward);

    bool getMovableReward(
        WorldController &world_controller,
        float &movable_reward);

    bool getEascapableReward(
        WorldController &world_controller,
        float &eascapable_reward);
};

#endif //WORLD_REWARD_H
