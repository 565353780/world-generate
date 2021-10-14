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

bool WorldGenerator::setRoomNum(
    const size_t &room_num)
{
    room_num_ = 0;
    is_room_num_set_ = false;

    if(room_num == 0)
    {
        std::cout << "WorldGenerator::setPersonNum : " << std::endl <<
          "Input :\n" <<
          "\troom_num = " << room_num << std::endl <<
          "perosn num not valid!" << std::endl;

        return false;
    }

    room_num_ = room_num;
    is_room_num_set_ = true;

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
        
        if(!is_person_num_set_)
        {
            std::cout << "WorldGenerator::generateWorld : " << std::endl <<
              "person_num not set!" << std::endl;

            return false;
        }

        std::cout << "WorldGenerator::generateWorld : " << std::endl <<
          "room_num not set!" << std::endl;

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
    if(is_wall_boundary_polygon_set_ &&
        is_person_num_set_ &&
        is_room_num_set_)
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
    const float person_width = 2;
    const float person_height = 2;

    const float wall_boundary_polygon_area = wall_boundary_polygon_.getPolygonArea();

    float person_area = person_width * person_height;
    float person_area_sum = person_area * person_num_;

    float room_area_sum_max = wall_boundary_polygon_area - person_area_sum;

    float room_area_max = room_area_sum_max / room_num_;

    const size_t room_width_max = size_t(std::sqrt(room_area_max));
    const size_t room_height_max = size_t(room_width_max);

    std::cout << "WorldGenerator::generateRoom : " << std::endl <<
      "world area = " << wall_boundary_polygon_area << std::endl <<
      "person num = " << person_num_ << std::endl <<
      "room num = " << room_num_ << std::endl <<
      "person size = [" << person_width << "," << person_height << "]" << std::endl <<
      "room size max = [" << room_width_max << "," << room_height_max << "]" << std::endl;

    size_t roomcontainer_num = 1 + std::rand() % room_num_;
    std::vector<size_t> room_num_in_roomcontainer_vec;
    room_num_in_roomcontainer_vec.resize(roomcontainer_num, 0);

    size_t current_used_room_num = 0;

    for(size_t i = 0; i < roomcontainer_num; ++i)
    {
        // room_num_in_roomcontainer_vec[i] = 1 + std::rand() % ();
    }

    return true;
}

