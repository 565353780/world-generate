#include "UnitNodeLineManager.h"

bool UnitNodePosition::reset()
{
    target_left_param = -1;
    target_right_param = -1;
    real_left_param = -1;
    real_right_param = -1;

    if(next_position != nullptr)
    {
        next_position->reset();

        delete(next_position);
        next_position = nullptr;
    }

    return true;
}

bool UnitNodePosition::outputInfo(
    const size_t &info_level) const
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "UnitNodePosition :\n" <<
      line_start << "\t target_param = [" << target_left_param << "," <<
      target_right_param << "]\n" <<
      line_start << "\t real_param = [" << real_left_param << "," <<
      real_right_param << "]" << std::endl;

    return true;
}

UnitNodeLine::~UnitNodeLine()
{
    reset();
}

bool UnitNodeLine::reset()
{
    if(position_line != nullptr)
    {
        position_line->reset();

        delete(position_line);
        position_line = nullptr;
    }

    return true;
}

bool UnitNodeLine::findNearestUnusedPosition(
    const UnitNodePosition& target_position,
    float &nearest_unused_left_param,
    float &nearest_unused_right_param)
{
    if(position_line == nullptr)
    {
        nearest_unused_left_param = 0;
        nearest_unused_right_param = 1;

        return true;
    }

    UnitNodePosition* search_position = position_line;
    float current_unused_left_param = 0;
    float current_unused_right_param;
    float min_dist_to_unused_position = std::numeric_limits<float>::max();

    while(search_position != nullptr)
    {
        current_unused_right_param = search_position->real_left_param;

        if(current_unused_right_param > current_unused_left_param)
        {
            float current_min_dist_to_unused_line_start =
              std::fabs(current_unused_left_param - target_position.real_left_param);

            if(current_min_dist_to_unused_line_start < min_dist_to_unused_position)
            {
                min_dist_to_unused_position = current_min_dist_to_unused_line_start;

                nearest_unused_left_param = current_unused_left_param;
                nearest_unused_right_param = current_unused_right_param;
            }

            float current_min_dist_to_unused_line_end =
              std::fabs(current_unused_right_param - target_position.real_left_param);

            if(current_min_dist_to_unused_line_end < min_dist_to_unused_position)
            {
                min_dist_to_unused_position = current_min_dist_to_unused_line_end;

                nearest_unused_left_param = current_unused_left_param;
                nearest_unused_right_param = current_unused_right_param;
            }
        }

        if(target_position.real_left_param < current_unused_right_param)
        {
            return true;
        }

        current_unused_left_param = search_position->real_right_param;

        search_position = search_position->next_position;
    }

    current_unused_right_param = 1.0;

    nearest_unused_left_param = current_unused_left_param;
    nearest_unused_right_param = current_unused_right_param;

    return true;
}

bool UnitNodeLine::findNearestValidPosition(
    const UnitNodePosition& target_position,
    UnitNodePosition& valid_position)
{
    float nearest_unused_left_param;
    float nearest_unused_right_param;

    if(!findNearestUnusedPosition(
          target_position,
          nearest_unused_left_param,
          nearest_unused_right_param))
    {
        std::cout << "UnitNodeLine::findNearestValidPosition :\n" <<
          "Input :\n" <<
          "\t target_position = [" << target_position.target_left_param << "," <<
          target_position.target_right_param << "]\n" <<
          "findNearestUnusedPosition for new position failed!" << std::endl;

        return false;
    }

    valid_position = target_position;

    if(nearest_unused_right_param - nearest_unused_left_param <
        target_position.target_right_param - target_position.target_left_param)
    {
        valid_position.real_left_param = nearest_unused_left_param;
        valid_position.real_right_param = nearest_unused_right_param;
    }
    else if(target_position.target_right_param > nearest_unused_right_param)
    {
        valid_position.real_right_param = nearest_unused_right_param;
        valid_position.real_left_param = nearest_unused_right_param -
          (target_position.target_right_param - target_position.target_left_param);
    }
    else if(target_position.target_left_param < nearest_unused_left_param)
    {
        valid_position.real_left_param = nearest_unused_left_param;
        valid_position.real_right_param = nearest_unused_left_param +
          (target_position.target_right_param - target_position.target_left_param);
    }

    return true;
}

bool UnitNodeLine::insertValidPosition(
    const UnitNodePosition &valid_position)
{
    UnitNodePosition* insert_position = new UnitNodePosition();
    insert_position->target_left_param = valid_position.target_left_param;
    insert_position->target_right_param = valid_position.target_right_param;
    insert_position->real_left_param = valid_position.real_left_param;
    insert_position->real_right_param = valid_position.real_right_param;

    if(position_line == nullptr)
    {
        position_line = insert_position;
        return true;
    }

    UnitNodePosition* search_position = position_line;
    UnitNodePosition* prev_search_position = search_position->prev_position;

    while(search_position != nullptr)
    {
        if(valid_position.real_right_param <= search_position->real_left_param)
        {
            insert_position->next_position = search_position;
            search_position->prev_position = insert_position;

            if(prev_search_position == nullptr)
            {
                position_line = insert_position;

                return true;
            }

            prev_search_position->next_position = insert_position;
            insert_position->prev_position = prev_search_position;

            return true;
        }

        prev_search_position = search_position;
        search_position = search_position->next_position;
    }

    prev_search_position->next_position = insert_position;
    insert_position->prev_position = prev_search_position;

    return true;
}

bool WallUnitNodeLine::resetPositionLine()
{
    wall_boundary_line.reset();

    return true;
}

bool WallUnitNodeLine::reset()
{
    wall_id = 0;
    wall_type = NodeType::NodeFree;

    resetPositionLine();

    return true;
}

bool WallUnitNodeLine::setWall(
    const size_t &target_wall_id,
    const NodeType &target_wall_type)
{
    wall_id = 0;
    wall_type = NodeType::NodeFree;

    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "WallUnitNodeLine::setWall :\n" <<
          "Input :\n" <<
          "\t wall_id = " << target_wall_id << std::endl <<
          "\t wall_type = " << target_wall_type << std::endl <<
          "wall_type is not the wall type!" << std::endl;

        return false;
    }

    wall_id = target_wall_id;
    wall_type = target_wall_type;

    return true;
}

bool WallUnitNodeLine::setBoundaryPolygon(
    const EasyPolygon2D &boundary_polygon)
{
    resetPositionLine();

    if(boundary_polygon.point_list.size() == 0)
    {
        std::cout << "WallUnitNodeLine::setBoundaryPolygon :\n" <<
          "boundary polygon is empty!" << std::endl;

        return false;
    }

    wall_boundary_polygon = boundary_polygon;

    return true;
}

bool WallUnitNodeLine::insertPosition(
    const UnitNodePosition& target_position,
    UnitNodePosition& valid_position)
{
    valid_position.reset();

    if(!wall_boundary_line.findNearestValidPosition(target_position, valid_position))
    {
        std::cout << "WallUnitNodeLine::insertPosition :\n" <<
          "findNearestValidPosition failed!\n";

        return false;
    }

    if(!wall_boundary_line.insertValidPosition(valid_position))
    {
        std::cout << "WallUnitNodeLine::insertPosition :\n" <<
          "insertValidPosition failed!\n";

        return false;
    }

    return true;
}

bool UnitNodeLineManager::reset()
{
    return true;
}

