#ifndef WORLD_REWARD_H
#define WORLD_REWARD_H

#include "export_library_global.h"

#include "EasyWorld/WorldObservation.h"

class LIBRARY_EXPORT WorldReward
{
public:
    WorldReward()
    {
    }

    bool reset();

    bool getReward(
        const WorldObservation& world_observation,
        float &reward);

private:
    bool getSpaceUtilizationReward(
        const WorldObservation& world_observation,
        float &space_utilization_reward);

    bool getNeighboorReward(
        const WorldObservation& world_observation,
        float &neighboor_reward);

    bool getMovableReward(
        const WorldObservation& world_observation,
        float &movable_reward);

    bool getEascapableReward(
        const WorldObservation& world_observation,
        float &eascapable_reward);

private:
    float space_utilization_ratio_;
    float neighboor_satisfied_ratio_;
    size_t movable_split_space_num_;
};

#endif //WORLD_REWARD_H
