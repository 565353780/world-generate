#include "WorldGenerator.h"

bool WorldGenerator::reset()
{
    if(!world_controller_.reset())
    {
        std::cout << "WorldGenerator::reset : " <<
          "reset for world_controller_ failed!" << std::endl;

        return false;
    }

    wall_boundary_polygon_.point_list.clear();
    is_wall_boundary_polygon_set_ = false;

    person_num_ = 0;
    is_person_num_set_ = false;

    return true;
}

bool WorldGenerator::setWallBoundaryPolygon(
    const EasyPolygon2D &wall_boundary_polygon)
{
    wall_boundary_polygon_.point_list.clear();

    is_wall_boundary_polygon_set_ = false;

    if(wall_boundary_polygon.point_list.size() == 0)
    {
        std::cout << "WorldGenerator::setArea : " << std::endl <<
          "wall boundary polygon is empty!" << std::endl;

        return false;
    }

    wall_boundary_polygon_ = wall_boundary_polygon;
    is_wall_boundary_polygon_set_ = true;

    return true;
}

bool WorldGenerator::setPersonNum(
    const size_t &person_num)
{
    person_num_ = 0;
    is_person_num_set_ = false;

    if(person_num == 0)
    {
        std::cout << "WorldGenerator::setPersonNum : " << std::endl <<
          "Input :\n" <<
          "\tperson_num = " << person_num << std::endl <<
          "perosn num not valid!" << std::endl;

        return false;
    }

    person_num_ = person_num;
    is_person_num_set_ = true;

    return true;
}

bool WorldGenerator::generateWorld()
{
    if(!isReadyToGenerate())
    {
        if(!is_wall_boundary_polygon_set_)
        {
            std::cout << "WorldGenerator::generateWorld : " << std::endl <<
              "wall_boundary_polygon not set!" << std::endl;

            return false;
        }
        
        std::cout << "WorldGenerator::generateWorld : " << std::endl <<
          "person_num not set!" << std::endl;

        return false;
    }

    if(!world_controller_.reset())
    {
        std::cout << "WorldGenerator::generateWorld : " << std::endl <<
          "reset for world_controller_ failed!" << std::endl;

        return false;
    }

    if(!generateWall())
    {
        std::cout << "WorldGenerator::generateWorld : " << std::endl <<
          "generateWall failed!" << std::endl;

        return false;
    }

    if(!generateRoom())
    {
        std::cout << "WorldGenerator::generateWorld : " << std::endl <<
          "generateRoom failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldGenerator::isReadyToGenerate()
{
    if(is_wall_boundary_polygon_set_ && is_person_num_set_)
    {
        return true;
    }

    return false;
}

bool WorldGenerator::generateWall()
{
    if(!world_controller_.createWorld(1, 1))
    {
        std::cout << "WorldGenerator::generateWall : " << std::endl <<
          "createWorld failed!" << std::endl;

        return false;
    }

    if(!world_controller_.createWall(0, NodeType::OuterWall))
    {
        std::cout << "WorldGenerator::generateWall : " << std::endl <<
          "createWall failed!" << std::endl;

        return false;
    }

    if(!world_controller_.setWallBoundaryPolygon(0, NodeType::OuterWall, wall_boundary_polygon_))
    {
        std::cout << "WorldGenerator::generateWall : " << std::endl <<
          "setWallBoundaryPolygon failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldGenerator::generateRoom()
{
    const float person_width_min = 2;
    const float person_height_min = 2;

    const float room_width_min = 8;
    const float room_height_min = 8;

    const float wall_boundary_polygon_area = wall_boundary_polygon_.getPolygonArea();

    float person_area_min = person_width_min * person_height_min;
    float person_area_min_sum = person_area_min * person_num_;

    float room_area_min = room_width_min * room_height_min;

    float room_num_max = (wall_boundary_polygon_area - person_area_min_sum) / (room_area_min - person_area_min);

    std::cout << "WorldGenerator::generateRoom : " << std::endl <<
      "person num = " << person_num_ << std::endl <<
      "world area = " << wall_boundary_polygon_area << std::endl <<
      "person size min = [" << person_width_min << "," << person_height_min << "]" << std::endl <<
      "room size min = [" << room_width_min << "," << room_height_min << "]" << std::endl;
    std::cout << "can generate 1 meeting room, 1 bathing room, " <<
      size_t(room_num_max) - 2 << " office room" << std::endl;

    return true;
}

