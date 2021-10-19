#include "WorldPlaceGenerator.h"

bool BoundaryLine::reset()
{
    line_start_position = -1;
    line_end_position = -1;
    line_height = -1;
    line_real_height = -1;

    return true;
}

bool BoundaryUnusedLine::setBoundaryLength(
    const float &boundary_length)
{
    if(boundary_length <= 0)
    {
        std::cout << "BoundaryUnusedLine::setBoundaryLength : " << std::endl <<
          "Input :\n" <<
          "\tboundary_length = " << boundary_length << std::endl <<
          "boundary length not valid!" << std::endl;

        return false;
    }

    boundary_length_ = boundary_length;

    boundary_unused_line_vec.resize(1);
    BoundaryLine boundary_unused_line;
    boundary_unused_line.line_start_position = 0;
    boundary_unused_line.line_end_position = boundary_length_;
    boundary_unused_line_vec[0] = boundary_unused_line;

    return true;
}

bool BoundaryUnusedLine::haveThisUnusedPosition(
    const float &boundary_position,
    size_t &position_on_unused_line_idx)
{
    position_on_unused_line_idx = 0;

    for(size_t i = 0; i < boundary_unused_line_vec.size(); ++i)
    {
        const BoundaryLine &boundary_unused_line = boundary_unused_line_vec[i];

        if(boundary_unused_line.line_start_position <= boundary_position &&
            boundary_position <= boundary_unused_line.line_end_position)
        {
            position_on_unused_line_idx = i;
            return true;
        }
    }

    return false;
}

bool BoundaryUnusedLine::isThisPositionUnused(
    const float &boundary_position)
{
    size_t position_on_unused_line_idx;

    if(haveThisUnusedPosition(boundary_position, position_on_unused_line_idx))
    {
        return true;
    }

    return false;
}

bool BoundaryUnusedLine::getNearestUnusedLine(
    const BoundaryLine &new_boundary_line,
    BoundaryLine &nearest_unused_boundary_line,
    size_t &nearest_unused_boundary_line_idx)
{
    nearest_unused_boundary_line.reset();
    nearest_unused_boundary_line.line_height = new_boundary_line.line_height;

    if(boundary_unused_line_vec.size() == 0)
    {
        std::cout << "BoundaryUnusedLine::getNearestUnusedLine : " << std::endl <<
          "Input :\n" <<
          "\tnew_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "]" << std::endl <<
          "boundary unused line vec is empty!" << std::endl;

        return false;
    }

    size_t start_position_on_unused_line_idx;
    if(haveThisUnusedPosition(new_boundary_line.line_start_position, start_position_on_unused_line_idx))
    {
        nearest_unused_boundary_line_idx = start_position_on_unused_line_idx;

        const BoundaryLine &start_position_on_unused_line =
          boundary_unused_line_vec[start_position_on_unused_line_idx];

        if(start_position_on_unused_line.line_end_position -
            start_position_on_unused_line.line_start_position <
            new_boundary_line.line_end_position - new_boundary_line.line_start_position)
        {
            nearest_unused_boundary_line = start_position_on_unused_line;

            return true;
        }

        if(new_boundary_line.line_end_position > start_position_on_unused_line.line_end_position)
        {
            nearest_unused_boundary_line.line_start_position = start_position_on_unused_line.line_end_position -
              (new_boundary_line.line_end_position - new_boundary_line.line_start_position);
            nearest_unused_boundary_line.line_end_position = start_position_on_unused_line.line_end_position;

            return true;
        }

        nearest_unused_boundary_line = new_boundary_line;

        return true;
    }

    float min_dist_to_unused_line = std::numeric_limits<float>::max();
    size_t min_dist_unused_line_idx = boundary_unused_line_vec.size();

    for(size_t i = 0; i < boundary_unused_line_vec.size(); ++i)
    {
        const BoundaryLine &search_unused_boundary_line = boundary_unused_line_vec[i];

        if(search_unused_boundary_line.line_start_position > new_boundary_line.line_start_position)
        {
            float current_dist =
              fabs(search_unused_boundary_line.line_start_position - new_boundary_line.line_start_position);

            if(current_dist < min_dist_to_unused_line)
            {
                min_dist_to_unused_line = current_dist;
                min_dist_unused_line_idx = i;
            }
        }
        else
        {
            float current_dist =
              fabs(search_unused_boundary_line.line_end_position - new_boundary_line.line_start_position);

            if(current_dist < min_dist_to_unused_line)
            {
                min_dist_to_unused_line = current_dist;
                min_dist_unused_line_idx = i;
            }
        }
    }

    nearest_unused_boundary_line_idx = min_dist_unused_line_idx;

    const BoundaryLine &search_nearest_unused_boundary_line =
      boundary_unused_line_vec[min_dist_unused_line_idx];

    if(search_nearest_unused_boundary_line.line_end_position - search_nearest_unused_boundary_line.line_start_position <
        new_boundary_line.line_end_position - new_boundary_line.line_start_position)
    {
        nearest_unused_boundary_line = search_nearest_unused_boundary_line;

        return true;
    }

    if(new_boundary_line.line_start_position < search_nearest_unused_boundary_line.line_start_position)
    {
        nearest_unused_boundary_line.line_start_position = search_nearest_unused_boundary_line.line_start_position;
        nearest_unused_boundary_line.line_end_position = search_nearest_unused_boundary_line.line_start_position +
          (new_boundary_line.line_end_position - new_boundary_line.line_start_position);

        return true;
    }

    nearest_unused_boundary_line.line_end_position = search_nearest_unused_boundary_line.line_end_position;
    nearest_unused_boundary_line.line_start_position = search_nearest_unused_boundary_line.line_end_position -
      (nearest_unused_boundary_line.line_end_position - nearest_unused_boundary_line.line_start_position);

    return true;
}

bool BoundaryUnusedLine::splitBoundaryLine(
    const BoundaryLine &new_boundary_line)
{
    BoundaryLine nearest_unused_boundary_line;
    size_t nearest_unused_boundary_line_idx;

    if(!getNearestUnusedLine(
          new_boundary_line,
          nearest_unused_boundary_line,
          nearest_unused_boundary_line_idx))
    {
        std::cout << "BoundaryUnusedLine::splitBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "\tnew_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "]" << std::endl <<
          "getNearestUnusedLine for new boundary line failed!" << std::endl;

        return false;
    }

    if(nearest_unused_boundary_line.line_start_position != new_boundary_line.line_start_position ||
        nearest_unused_boundary_line.line_end_position != new_boundary_line.line_end_position)
    {
        std::cout << "BoundaryUnusedLine::splitBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "\tnew_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "]" << std::endl <<
          "this boundary line not total unused!" << std::endl;

        return false;
    }

    BoundaryLine &on_unused_boundary_line =
      boundary_unused_line_vec[nearest_unused_boundary_line_idx];

    if(nearest_unused_boundary_line.line_start_position ==
        on_unused_boundary_line.line_start_position)
    {
        if(nearest_unused_boundary_line.line_end_position ==
            on_unused_boundary_line.line_end_position)
        {
            boundary_unused_line_vec.erase(boundary_unused_line_vec.begin() + nearest_unused_boundary_line_idx);

            return true;
        }

        BoundaryLine new_sub_unused_boundary_line;
        new_sub_unused_boundary_line.line_start_position = nearest_unused_boundary_line.line_end_position;
        new_sub_unused_boundary_line.line_end_position = on_unused_boundary_line.line_end_position;
        boundary_unused_line_vec.emplace_back(new_sub_unused_boundary_line);

        on_unused_boundary_line.line_start_position = nearest_unused_boundary_line.line_end_position;

        return true;
    }

    if(nearest_unused_boundary_line.line_end_position == on_unused_boundary_line.line_end_position)
    {
        BoundaryLine new_sub_unused_boundary_line;
        new_sub_unused_boundary_line.line_start_position = on_unused_boundary_line.line_start_position;
        new_sub_unused_boundary_line.line_end_position = nearest_unused_boundary_line.line_start_position;
        boundary_unused_line_vec.emplace_back(new_sub_unused_boundary_line);

        on_unused_boundary_line.line_end_position = nearest_unused_boundary_line.line_start_position;

        return true;
    }

    BoundaryLine new_sub_unused_boundary_line;
    new_sub_unused_boundary_line.line_start_position = nearest_unused_boundary_line.line_end_position;
    new_sub_unused_boundary_line.line_end_position = on_unused_boundary_line.line_end_position;
    boundary_unused_line_vec.emplace_back(new_sub_unused_boundary_line);

    on_unused_boundary_line.line_end_position = nearest_unused_boundary_line.line_start_position;

    return true;
}

bool BoundaryUnusedLine::generateWallRoomContainer(
    const float &roomcontainer_start_position,
    const float &roomcontainer_width,
    const float &roomcontainer_height)
{
    BoundaryLine new_boundary_line;
    new_boundary_line.line_start_position = roomcontainer_start_position;
    new_boundary_line.line_end_position = roomcontainer_start_position + roomcontainer_width;
    new_boundary_line.line_height = roomcontainer_height;

    BoundaryLine nearest_unused_boundary_line;
    size_t nearest_unused_boundary_line_idx;

    if(!getNearestUnusedLine(new_boundary_line, nearest_unused_boundary_line, nearest_unused_boundary_line_idx))
    {
        std::cout << "BoundaryUnusedLine::generateWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "getNearestUnusedLine for new boundary line failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldPlaceGenerator::reset()
{
    if(!world_controller_.reset())
    {
        std::cout << "WorldPlaceGenerator::reset : " <<
          "reset for world_controller_ failed!" << std::endl;

        return false;
    }

    wall_boundary_polygon_.point_list.clear();
    wall_boundary_length_vec_.clear();
    is_wall_boundary_polygon_set_ = false;

    person_num_ = 0;
    is_person_num_set_ = false;

    return true;
}

bool WorldPlaceGenerator::setWallBoundaryPolygon(
    const EasyPolygon2D &wall_boundary_polygon)
{
    wall_boundary_polygon_.point_list.clear();
    wall_boundary_length_vec_.clear();

    is_wall_boundary_polygon_set_ = false;

    if(wall_boundary_polygon.point_list.size() == 0)
    {
        std::cout << "WorldPlaceGenerator::setWallBoundaryPolygon : " << std::endl <<
          "wall boundary polygon is empty!" << std::endl;

        return false;
    }

    wall_boundary_polygon_ = wall_boundary_polygon;

    wall_boundary_length_vec_.resize(wall_boundary_polygon_.point_list.size(), -1);

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

bool WorldPlaceGenerator::setPersonNum(
    const size_t &person_num)
{
    person_num_ = 0;
    is_person_num_set_ = false;

    if(person_num == 0)
    {
        std::cout << "WorldPlaceGenerator::setPersonNum : " << std::endl <<
          "Input :\n" <<
          "\tperson_num = " << person_num << std::endl <<
          "perosn num not valid!" << std::endl;

        return false;
    }

    person_num_ = person_num;
    is_person_num_set_ = true;

    return true;
}

bool WorldPlaceGenerator::setRoomNum(
    const size_t &room_num)
{
    room_num_ = 0;
    is_room_num_set_ = false;

    if(room_num == 0)
    {
        std::cout << "WorldPlaceGenerator::setPersonNum : " << std::endl <<
          "Input :\n" <<
          "\troom_num = " << room_num << std::endl <<
          "perosn num not valid!" << std::endl;

        return false;
    }

    room_num_ = room_num;
    is_room_num_set_ = true;

    return true;
}

bool WorldPlaceGenerator::generateWorld()
{
    if(!isReadyToGenerate())
    {
        if(!is_wall_boundary_polygon_set_)
        {
            std::cout << "WorldSplitGenerator::generateWorld : " << std::endl <<
              "wall_boundary_polygon not set!" << std::endl;

            return false;
        }
        
        if(!is_person_num_set_)
        {
            std::cout << "WorldSplitGenerator::generateWorld : " << std::endl <<
              "person_num not set!" << std::endl;

            return false;
        }

        std::cout << "WorldSplitGenerator::generateWorld : " << std::endl <<
          "room_num not set!" << std::endl;

        return false;
    }

    if(!world_controller_.reset())
    {
        std::cout << "WorldSplitGenerator::generateWorld : " << std::endl <<
          "reset for world_controller_ failed!" << std::endl;

        return false;
    }

    if(!generateWall())
    {
        std::cout << "WorldSplitGenerator::generateWorld : " << std::endl <<
          "generateWall failed!" << std::endl;

        return false;
    }

    if(!generateRoom())
    {
        std::cout << "WorldSplitGenerator::generateWorld : " << std::endl <<
          "generateWallRoom failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldPlaceGenerator::isReadyToGenerate()
{
    if(is_wall_boundary_polygon_set_ &&
        is_person_num_set_ &&
        is_room_num_set_)
    {
        return true;
    }

    return false;
}

bool WorldPlaceGenerator::generateWall()
{
    if(!world_controller_.createWorld(1, 1))
    {
        std::cout << "WorldPlaceGenerator::generateWall : " << std::endl <<
          "createWorld failed!" << std::endl;

        return false;
    }

    if(!world_controller_.createWall(0, NodeType::OuterWall))
    {
        std::cout << "WorldPlaceGenerator::generateWall : " << std::endl <<
          "createWall failed!" << std::endl;

        return false;
    }

    if(!world_controller_.setWallBoundaryPolygon(0, NodeType::OuterWall, wall_boundary_polygon_))
    {
        std::cout << "WorldPlaceGenerator::generateWall : " << std::endl <<
          "setWallBoundaryPolygon failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldPlaceGenerator::generateRoom()
{
    return true;
}

