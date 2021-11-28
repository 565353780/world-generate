#include "WallGenerator.h"

bool WallGenerator::reset()
{
    outerwall_vec_.clear();
    innerwall_vec_.clear();

    return true;
}

bool WallGenerator::createWall(
    const NodeType& wall_type)
{
    if(wall_type == NodeType::OuterWall)
    {
        outerwall_vec_.emplace_back(EasyPolygon2D());

        return true;
    }

    if(wall_type == NodeType::InnerWall)
    {
        innerwall_vec_.emplace_back(EasyPolygon2D());

        return true;
    }

    std::cout << "WallGenerator::createWall :\n" <<
      "Input:\n" <<
      "\t wall_type = " << wall_type << std::endl <<
      "this type is not the wall type!\n";

    return false;
}

bool WallGenerator::addPointForWall(
    const NodeType &wall_type,
    const size_t &wall_idx,
    const float &point_x,
    const float &point_y)
{
    if(wall_type == NodeType::OuterWall)
    {
        if(wall_idx >= outerwall_vec_.size())
        {
            std::cout << "WallGenerator::addPointForWall :\n" <<
              "Input:\n" <<
              "\t wall_type = " << wall_type << std::endl <<
              "\t wall_idx = " << wall_idx << std::endl <<
              "\t point = [" << point_x << "," <<
              point_y << "]\n" <<
              "wall_idx out of range!\n";

            return false;
        }

        EasyPolygon2D& wall_boundary_polygon =
          outerwall_vec_[wall_idx];

        std::cout << "in addPoint\n";
        wall_boundary_polygon.addPoint(point_x, point_y);
        std::cout << "out addPointForWall\n";

        return true;
    }

    if(wall_type == NodeType::InnerWall)
    {
        if(wall_idx >= innerwall_vec_.size())
        {
            std::cout << "WallGenerator::addPointForWall :\n" <<
              "Input:\n" <<
              "\t wall_type = " << wall_type << std::endl <<
              "\t wall_idx = " << wall_idx << std::endl <<
              "\t point = [" << point_x << "," <<
              point_y << "]\n" <<
              "wall_idx out of range!\n";

            return false;
        }

        EasyPolygon2D& wall_boundary_polygon =
          innerwall_vec_[wall_idx];

        wall_boundary_polygon.addPoint(point_x, point_y);

        return true;
    }

    std::cout << "WallGenerator::addPointForWall :\n" <<
      "Input:\n" <<
      "\t wall_type = " << wall_type << std::endl <<
      "\t wall_idx = " << wall_idx << std::endl <<
      "\t point = [" << point_x << "," <<
      point_y << "]\n" <<
      "this type is not the wall type!\n";

    return false;
}

