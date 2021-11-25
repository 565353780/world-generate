#include "WorldReward.h"

bool WorldReward::reset()
{
    space_utilization_ratio_ = 0;
    movable_split_space_num_ = 0;

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

    if(outerwall_boundary_polygon_vec.size() == 0)
    {
        return true;
    }

    float outerwall_area_sum = 0;

    for(const EasyPolygon2D& outerwall_boundary_polygon : outerwall_boundary_polygon_vec)
    {
        outerwall_area_sum += outerwall_boundary_polygon.getPolygonAreaAbs();
    }

    const std::vector<EasyPolygon2D>& innerwall_boundary_polygon_vec =
      world_observation.innerwall_boundary_polygon_vec_;

    float innerwall_area_sum = 0;

    for(const EasyPolygon2D& innerwall_boundary_polygon : innerwall_boundary_polygon_vec)
    {
        innerwall_area_sum += innerwall_boundary_polygon.getPolygonAreaAbs();
    }

    const float valid_area = outerwall_area_sum - innerwall_area_sum;

    const std::vector<EasyPolygon2D>& roomcontainer_boundary_polygon_vec =
      world_observation.roomcontainer_boundary_polygon_vec_;

    float roomcontainer_area_sum = 0;

    for(const EasyPolygon2D& roomcontainer_boundary_polygon : roomcontainer_boundary_polygon_vec)
    {
        roomcontainer_area_sum += roomcontainer_boundary_polygon.getPolygonAreaAbs();
    }

    float current_space_utilization_ratio = roomcontainer_area_sum / valid_area;

    space_utilization_reward = current_space_utilization_ratio - space_utilization_ratio_;

    space_utilization_ratio_ = current_space_utilization_ratio;

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

    const std::vector<EasyPolygon2D>& outerwall_boundary_polygon_vec =
      world_observation.outerwall_boundary_polygon_vec_;

    if(outerwall_boundary_polygon_vec.size() == 0)
    {
        return true;
    }

    if(movable_split_space_num_ < outerwall_boundary_polygon_vec.size())
    {
        movable_split_space_num_ = outerwall_boundary_polygon_vec.size();
    }

    size_t current_movable_split_space_num = 0;

    for(const EasyPolygon2D& outerwall_boundary_polygon : outerwall_boundary_polygon_vec)
    {
    }

    return true;
}

bool WorldReward::getEascapableReward(
    const WorldObservation& world_observation,
    float &eascapable_reward)
{
    eascapable_reward = 0;

    return true;
}
