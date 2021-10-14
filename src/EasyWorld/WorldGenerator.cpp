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
    wall_boundary_length_vec_.clear();
    wall_boundary_used_line_vec_vec_.clear();
    is_wall_boundary_polygon_set_ = false;

    person_num_ = 0;
    is_person_num_set_ = false;

    return true;
}

bool WorldGenerator::setWallBoundaryPolygon(
    const EasyPolygon2D &wall_boundary_polygon)
{
    wall_boundary_polygon_.point_list.clear();
    wall_boundary_length_vec_.clear();
    wall_boundary_used_line_vec_vec_.clear();

    is_wall_boundary_polygon_set_ = false;

    if(wall_boundary_polygon.point_list.size() == 0)
    {
        std::cout << "WorldGenerator::setArea : " << std::endl <<
          "wall boundary polygon is empty!" << std::endl;

        return false;
    }

    wall_boundary_polygon_ = wall_boundary_polygon;

    wall_boundary_length_vec_.resize(wall_boundary_polygon_.point_list.size(), -1);
    wall_boundary_used_line_vec_vec_.resize(wall_boundary_polygon_.point_list.size());

    for(size_t i = 0; i < wall_boundary_polygon_.point_list.size(); ++i)
    {
        const EasyPoint2D &current_point = wall_boundary_polygon_.point_list[i];
        const EasyPoint2D &next_point = wall_boundary_polygon_.point_list[
          (i + 1) % wall_boundary_polygon_.point_list.size()];

        const float wall_boundary_length = EasyComputation::pointDist(current_point, next_point);

        wall_boundary_length_vec_[i] = wall_boundary_length;
    }

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

bool WorldGenerator::isWallBoundaryStartPositionValid(
    const size_t &wall_boundary_idx,
    const float &wall_boundary_start_position,
    float &max_line_width,
    float &max_line_height)
{
    max_line_width = -1;
    max_line_height = -1;

    if(wall_boundary_idx >= wall_boundary_polygon_.point_list.size())
    {
        std::cout << "WorldGenerator::isWallBoundaryStartPositionValid : " << std::endl <<
          "Input :\n" <<
          "\twall_boundary_idx = " << wall_boundary_idx << std::endl <<
          "\twall_boundary_start_position = " << wall_boundary_start_position << std::endl <<
          "wall boundary idx out of range!" << std::endl;

        return false;
    }

    const float &wall_boundary_length = wall_boundary_length_vec_[wall_boundary_idx];

    if(wall_boundary_start_position < 0 || wall_boundary_start_position > wall_boundary_length)
    {
        std::cout << "WorldGenerator::isWallBoundaryStartPositionValid : " << std::endl <<
          "Input :\n" <<
          "\twall_boundary_idx = " << wall_boundary_idx << std::endl <<
          "\twall_boundary_start_position = " << wall_boundary_start_position << std::endl <<
          "wall boundary start position out of range!" << std::endl;

        return false;
    }

    max_line_width = wall_boundary_length;

    for(const std::vector<float> &wall_boundary_used_line :
        wall_boundary_used_line_vec_vec_[wall_boundary_idx])
    {
        if(wall_boundary_used_line[0] < wall_boundary_start_position &&
            wall_boundary_start_position < wall_boundary_used_line[1])
        {
            std::cout << "WorldGenerator::isWallBoundaryStartPositionValid : " << std::endl <<
              "Input :\n" <<
              "\twall_boundary_idx = " << wall_boundary_idx << std::endl <<
              "\twall_boundary_start_position = " << wall_boundary_start_position << std::endl <<
              "wall boundary line intersect with another line!" << std::endl;

            return false;
        }

        if(wall_boundary_used_line[0] < max_line_width)
        {
            max_line_width = wall_boundary_used_line[0];
        }
    }

    const float &last_wall_boundary_length = wall_boundary_length_vec_[
      (wall_boundary_idx - 1 + wall_boundary_polygon_.point_list.size()) %
        wall_boundary_polygon_.point_list.size()];

    max_line_height = last_wall_boundary_length;

    for(const std::vector<float> &last_wall_boundary_used_line : wall_boundary_used_line_vec_vec_[
      (wall_boundary_idx - 1 + wall_boundary_polygon_.point_list.size()) %
        wall_boundary_polygon_.point_list.size()])
    {
        if(last_wall_boundary_length - last_wall_boundary_used_line[1] >
            max_line_height)
        {
            max_line_height = last_wall_boundary_length - last_wall_boundary_used_line[1];
        }
    }

    return true;
}

bool WorldGenerator::isWallBoundaryLineValid(
    const size_t &wall_boundary_idx,
    const std::vector<float> &wall_boundary_line,
    float &max_line_height)
{
    max_line_height = -1;

    if(wall_boundary_idx >= wall_boundary_polygon_.point_list.size())
    {
        std::cout << "WorldGenerator::isWallBoundaryLineValid : " << std::endl <<
          "Input :\n" <<
          "\twall_boundary_idx = " << wall_boundary_idx << std::endl <<
          "\twall_boundary_line = [" << wall_boundary_line[0] << "," <<
          wall_boundary_line[1] << "," <<
          wall_boundary_line[2] << "]" << std::endl <<
          "wall boundary idx out of range!" << std::endl;

        return false;
    }

    const float &wall_boundary_length = wall_boundary_length_vec_[wall_boundary_idx];

    if(wall_boundary_line[0] < 0 || wall_boundary_line[1] > wall_boundary_length)
    {
        std::cout << "WorldGenerator::isWallBoundaryLineValid : " << std::endl <<
          "Input :\n" <<
          "\twall_boundary_idx = " << wall_boundary_idx << std::endl <<
          "\twall_boundary_line = [" << wall_boundary_line[0] << "," <<
          wall_boundary_line[1] << "," <<
          wall_boundary_line[2] << "]" << std::endl <<
          "wall boundary line out of range!" << std::endl;

        return false;
    }

    for(const std::vector<float> &wall_boundary_used_line :
        wall_boundary_used_line_vec_vec_[wall_boundary_idx])
    {
        if(wall_boundary_used_line[0] < wall_boundary_line[1] &&
            wall_boundary_line[0] < wall_boundary_used_line[1])
        {
            std::cout << "WorldGenerator::isWallBoundaryLineValid : " << std::endl <<
              "Input :\n" <<
              "\twall_boundary_idx = " << wall_boundary_idx << std::endl <<
              "\twall_boundary_line = [" << wall_boundary_line[0] << "," <<
              wall_boundary_line[1] << "," <<
              wall_boundary_line[2] << "]" << std::endl <<
              "wall boundary line intersect with another line!" << std::endl;

            return false;
        }
    }

    const float &last_wall_boundary_length = wall_boundary_length_vec_[
      (wall_boundary_idx - 1 + wall_boundary_polygon_.point_list.size()) %
        wall_boundary_polygon_.point_list.size()];

    float last_wall_boundary_used_line_max_position = 0;
    float last_wall_boundary_used_line_max_position_height = 0;

    for(const std::vector<float> &last_wall_boundary_used_line : wall_boundary_used_line_vec_vec_[
      (wall_boundary_idx - 1 + wall_boundary_polygon_.point_list.size()) %
        wall_boundary_polygon_.point_list.size()])
    {
        if(last_wall_boundary_used_line[1] > last_wall_boundary_used_line_max_position)
        {
            last_wall_boundary_used_line_max_position = last_wall_boundary_used_line[1];
            last_wall_boundary_used_line_max_position_height = last_wall_boundary_used_line[2];
        }
    }

    if(last_wall_boundary_used_line_max_position_height > wall_boundary_line[0] &&
        last_wall_boundary_length - last_wall_boundary_used_line_max_position < wall_boundary_line[2])
    {
        max_line_height = last_wall_boundary_length - last_wall_boundary_used_line_max_position;

        std::cout << "WorldGenerator::isWallBoundaryLineValid : " << std::endl <<
          "Input :\n" <<
          "\twall_boundary_idx = " << wall_boundary_idx << std::endl <<
          "\twall_boundary_line = [" << wall_boundary_line[0] << "," <<
          wall_boundary_line[1] << "," <<
          wall_boundary_line[2] << "]" << std::endl <<
          "wall boundary line's current height intersect with last boundary room!" << std::endl;

        return false;
    }

    float next_wall_boundary_used_line_min_position = 0;
    float next_wall_boundary_used_line_min_position_height = 0;

    for(const std::vector<float> &next_wall_boundary_used_line : wall_boundary_used_line_vec_vec_[
      (wall_boundary_idx + 1) % wall_boundary_polygon_.point_list.size()])
    {
        if(next_wall_boundary_used_line[0] < next_wall_boundary_used_line_min_position)
        {
            next_wall_boundary_used_line_min_position = next_wall_boundary_used_line[0];
            next_wall_boundary_used_line_min_position_height = next_wall_boundary_used_line[2];
        }
    }

    if(next_wall_boundary_used_line_min_position_height > wall_boundary_length - wall_boundary_line[1] &&
        next_wall_boundary_used_line_min_position < wall_boundary_line[2])
    {
        max_line_height = next_wall_boundary_used_line_min_position;

        std::cout << "WorldGenerator::isWallBoundaryLineValid : " << std::endl <<
          "Input :\n" <<
          "\twall_boundary_idx = " << wall_boundary_idx << std::endl <<
          "\twall_boundary_line = [" << wall_boundary_line[0] << "," <<
          wall_boundary_line[1] << "," <<
          wall_boundary_line[2] << "]" << std::endl <<
          "wall boundary line's current height intersect with next boundary room!" << std::endl;

        return false;
    }

    return true;
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

    const float room_width_min = 4;
    const float room_height_min = 4;

    const float wall_boundary_polygon_area = wall_boundary_polygon_.getPolygonArea();

    float person_area_min = person_width_min * person_height_min;
    float person_area_min_sum = person_area_min * person_num_;

    if(person_area_min_sum >= wall_boundary_polygon_area)
    {
        std::cout << "WorldGenerator::generateRoom : " << std::endl <<
          "person area min sum >= wall boundary polygon area!" << std::endl;

        return false;
    }

    float room_area_sum_max = wall_boundary_polygon_area - person_area_min_sum;

    float room_area_max = room_area_sum_max / room_num_;

    if(room_area_max < room_width_min * room_height_min)
    {
        std::cout << "WorldGenerator::generateRoom : " << std::endl <<
          "room area max < target min room area!" << std::endl;

        return false;
    }

    const size_t room_width_max = size_t(std::sqrt(room_area_max));
    const size_t room_height_max = room_width_max;

    std::cout << "WorldGenerator::generateRoom : " << std::endl <<
      "world area = " << wall_boundary_polygon_area << std::endl <<
      "person num = " << person_num_ << std::endl <<
      "room num = " << room_num_ << std::endl <<
      "person size min = [" << person_width_min << "," << person_height_min << "]" << std::endl <<
      "room size max = [" << room_width_max << "," << room_height_max << "]" << std::endl;

    size_t roomcontainer_num = 1 + std::rand() % room_num_;
    std::vector<size_t> room_num_in_roomcontainer_vec;
    room_num_in_roomcontainer_vec.resize(roomcontainer_num, 0);

    size_t current_unused_room_num = room_num_;

    std::cout << "roomcontainer = " << roomcontainer_num << std::endl;
    for(size_t i = 0; i < roomcontainer_num; ++i)
    {
        const size_t must_unused_room_num = roomcontainer_num - i - 1;
        const size_t current_random_room_num =
          1 + std::rand() % (current_unused_room_num - must_unused_room_num);

        room_num_in_roomcontainer_vec[i] = current_random_room_num;

        current_unused_room_num -= current_random_room_num;
    }

    if(current_unused_room_num > 0)
    {
        room_num_in_roomcontainer_vec.back() += current_unused_room_num;
    }

    for(size_t i = 0; i < roomcontainer_num; ++i)
    {
        const size_t &current_room_num = room_num_in_roomcontainer_vec[i];
        float current_roomcontainer_width_max = current_room_num * room_width_max;
        float current_roomcontainer_height_max = room_height_max;

        size_t current_random_boundary_idx = std::rand() % wall_boundary_polygon_.point_list.size();
        float current_random_boundary_start_position =
          std::rand() % size_t(wall_boundary_length_vec_[current_random_boundary_idx]);

        float max_line_width;
        float max_line_height;

        const size_t try_time = 100;
        size_t current_try_time = 0;
        while(!isWallBoundaryStartPositionValid(
              current_random_boundary_idx,
              current_random_boundary_start_position,
              max_line_width,
              max_line_height))
        {
            ++current_try_time;

            current_random_boundary_idx = std::rand() % wall_boundary_polygon_.point_list.size();
            current_random_boundary_start_position =
              std::rand() % size_t(wall_boundary_length_vec_[current_random_boundary_idx]);

            if(current_try_time > try_time)
            {
                std::cout << "WorldGenerator::generateRoom : " << std::endl <<
                  "create random roomcontainer failed!" << std::endl;

                return false;
            }
        }

        if(max_line_width < current_roomcontainer_width_max)
        {
            current_roomcontainer_width_max = max_line_width;
        }

        if(max_line_height < current_roomcontainer_height_max)
        {
            current_roomcontainer_height_max = max_line_height;
        }
        std::cout << "current_roomcontainer_width_max = " <<
          current_roomcontainer_width_max << std::endl;
        std::cout << "current_roomcontainer_height_max = " <<
          current_roomcontainer_height_max << std::endl;

        std::vector<float> current_wall_boundary_line;
        current_wall_boundary_line.resize(3);
        current_wall_boundary_line[0] = current_random_boundary_start_position;
        current_wall_boundary_line[1] =
          current_random_boundary_start_position + current_roomcontainer_width_max;
        current_wall_boundary_line[2] = current_roomcontainer_height_max;
        if(!isWallBoundaryLineValid(
              current_random_boundary_idx,
              current_wall_boundary_line,
              max_line_height))
        {
            current_roomcontainer_height_max = max_line_height;
        }

        EasyAxis2D axis;
        axis.setXDirection(1, 0);
        axis.setCenter(current_random_boundary_start_position, 0);
        if(!world_controller_.createWallRoomContainerForWall(
              0,
              NodeType::OuterWall,
              current_random_boundary_idx,
              current_roomcontainer_width_max,
              current_roomcontainer_height_max,
              axis,
              current_room_num))
        {
            std::cout << "WorldGenerator::generateRoom : " << std::endl <<
              "createWallRoomContainerForWall failed!" << std::endl;

            return false;
        }

        std::vector<float> current_valid_wall_boundary_line;
        current_valid_wall_boundary_line.resize(3);
        current_valid_wall_boundary_line[0] = current_random_boundary_start_position;
        current_valid_wall_boundary_line[1] =
          current_random_boundary_start_position + current_roomcontainer_width_max;
        current_valid_wall_boundary_line[2] = current_roomcontainer_height_max;
        wall_boundary_used_line_vec_vec_[current_random_boundary_idx].emplace_back(
            current_valid_wall_boundary_line);
    }

    std::cout << "finish generate WallRoom!" << std::endl;

    return true;
}

