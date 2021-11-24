#include "WorldReward.h"

bool WorldReward::reset()
{
    return true;
}

bool WorldReward::getReward(
    const WorldObservation& world_observation,
    float &reward)
{
    reward = 0;

    float new_reward;

    if(!getSpaceUtilizationReward(world_observation, new_reward))
    {
        std::cout << "WorldReward::getReward : " << std::endl <<
          "getSpaceUtilizationReward failed!" << std::endl;

        return false;
    }
    reward += new_reward;

    if(!getNeighboorReward(world_observation, new_reward))
    {
        std::cout << "WorldReward::getReward : " << std::endl <<
          "getNeighboorReward failed!" << std::endl;

        return false;
    }
    reward += new_reward;

    if(!getMovableReward(world_observation, new_reward))
    {
        std::cout << "WorldReward::getReward : " << std::endl <<
          "getMovableReward failed!" << std::endl;

        return false;
    }
    reward += new_reward;

    if(!getEascapableReward(world_observation, new_reward))
    {
        std::cout << "WorldReward::getReward : " << std::endl <<
          "getEascapableReward failed!" << std::endl;

        return false;
    }
    reward += new_reward;

    return true;
}

bool WorldReward::getSpaceUtilizationReward(
    const WorldObservation& world_observation,
    float &space_utilization_reward)
{
    space_utilization_reward = 0;

    const std::vector<EasyPolygon2D>& outerwall_boundary_polygon_vec =
      world_observation.outerwall_boundary_polygon_vec_;

    return true;
}

bool WorldReward::getNeighboorReward(
    const WorldObservation& world_observation,
    float &neighboor_reward)
{
    neighboor_reward = 0;

    return true;
}

bool WorldReward::getMovableReward(
    const WorldObservation& world_observation,
    float &movable_reward)
{
    movable_reward = 0;

    return true;
}

bool WorldReward::getEascapableReward(
    const WorldObservation& world_observation,
    float &eascapable_reward)
{
    eascapable_reward = 0;

    return true;
}
