#include "WorldReward.h"

bool WorldReward::reset()
{
    return true;
}

bool WorldReward::getReward(
    WorldController &world_controller,
    float &reward)
{
    reward = 0;

    float new_reward;

    if(!getSpaceUtilizationReward(world_controller, new_reward))
    {
        std::cout << "WorldReward::getReward : " << std::endl <<
          "getSpaceUtilizationReward failed!" << std::endl;

        return false;
    }
    reward += new_reward;

    if(!getNeighboorReward(world_controller, new_reward))
    {
        std::cout << "WorldReward::getReward : " << std::endl <<
          "getNeighboorReward failed!" << std::endl;

        return false;
    }
    reward += new_reward;

    if(!getMovableReward(world_controller, new_reward))
    {
        std::cout << "WorldReward::getReward : " << std::endl <<
          "getMovableReward failed!" << std::endl;

        return false;
    }
    reward += new_reward;

    if(!getEascapableReward(world_controller, new_reward))
    {
        std::cout << "WorldReward::getReward : " << std::endl <<
          "getEascapableReward failed!" << std::endl;

        return false;
    }
    reward += new_reward;

    return true;
}

bool WorldReward::getSpaceUtilizationReward(
    WorldController &world_controller,
    float &space_utilization_reward)
{
    space_utilization_reward = 0;

    return true;
}

bool WorldReward::getNeighboorReward(
    WorldController &world_controller,
    float &neighboor_reward)
{
    neighboor_reward = 0;

    return true;
}

bool WorldReward::getMovableReward(
    WorldController &world_controller,
    float &movable_reward)
{
    movable_reward = 0;

    return true;
}

bool WorldReward::getEascapableReward(
    WorldController &world_controller,
    float &eascapable_reward)
{
    eascapable_reward = 0;

    return true;
}
