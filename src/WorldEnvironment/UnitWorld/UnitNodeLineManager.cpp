#include "UnitNodeLineManager.h"

bool UnitNodePosition::reset()
{
    node_id = 0;
    node_type = NodeType::NodeFree;
    target_left_param = -1;
    target_right_param = -1;
    target_height = -1;
    real_left_param = -1;
    real_right_param = -1;
    real_height = -1;

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
      line_start << "\t node_id = " << node_id << std::endl <<
      line_start << "\t node_type = " << node_type << std::endl <<
      line_start << "\t target_param = [" << target_left_param << "," <<
      target_right_param << "]\n" <<
      line_start << "\t target_height = " << target_height << std::endl <<
      line_start << "\t real_param = [" << real_left_param << "," <<
      real_right_param << "]\n" <<
      line_start << "\t real_height = " << real_height << std::endl;

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
        nearest_unused_right_param = 2;

        return true;
    }

    float real_target_position_left_param = target_position.target_left_param;
    float real_target_position_right_param = target_position.target_right_param;

    if(real_target_position_left_param > real_target_position_right_param)
    {
        real_target_position_right_param += 1;
    }

    float current_unused_left_param = 0;
    float current_unused_right_param;
    float min_dist_to_unused_position = std::numeric_limits<float>::max();

    UnitNodePosition* last_position = position_line;
    if(last_position != nullptr)
    {
        while(last_position->next_position != nullptr)
        {
            last_position = last_position->next_position;
        }

        if(last_position->real_right_param > 1)
        {
            current_unused_left_param = last_position->real_right_param - 1;
        }
    }

    UnitNodePosition* search_position = position_line;

    while(search_position != nullptr)
    {
        current_unused_right_param = search_position->real_left_param;

        if(current_unused_right_param <= current_unused_left_param)
        {
            search_position = search_position->next_position;

            continue;
        }

        const float current_min_dist_to_unused_line_left =
          std::abs(current_unused_left_param - real_target_position_left_param);

        if(current_min_dist_to_unused_line_left < min_dist_to_unused_position)
        {
            min_dist_to_unused_position = current_min_dist_to_unused_line_left;

            nearest_unused_left_param = current_unused_left_param;
            nearest_unused_right_param = current_unused_right_param;
        }

        const float current_min_dist_to_unused_line_right =
          std::abs(current_unused_right_param - real_target_position_left_param);

        if(current_min_dist_to_unused_line_right < min_dist_to_unused_position)
        {
            min_dist_to_unused_position = current_min_dist_to_unused_line_right;

            nearest_unused_left_param = current_unused_left_param;
            nearest_unused_right_param = current_unused_right_param;
        }

        if(real_target_position_left_param < current_unused_right_param)
        {
            return true;
        }

        current_unused_left_param = search_position->real_right_param;

        search_position = search_position->next_position;
    }

    if(last_position != nullptr)
    {
        if(last_position->real_right_param >= 1)
        {
            current_unused_right_param = last_position->real_left_param;
        }
        else
        {
            current_unused_right_param = 1;
        }
    }

    nearest_unused_left_param = current_unused_left_param;
    nearest_unused_right_param = current_unused_right_param;

    if(nearest_unused_left_param >= 1)
    {
        nearest_unused_left_param -= 1;
    }

    return true;
}

bool UnitNodeLine::updatePosition(
    UnitNodePosition& target_position)
{
    float nearest_unused_left_param;
    float nearest_unused_right_param;

    if(!findNearestUnusedPosition(
          target_position,
          nearest_unused_left_param,
          nearest_unused_right_param))
    {
        std::cout << "UnitNodeLine::updatePosition :\n" <<
          "Input :\n" <<
          "\t target_position = [" << target_position.target_left_param << "," <<
          target_position.target_right_param << "]\n" <<
          "findNearestUnusedPosition for new position failed!" << std::endl;

        return false;
    }

    float real_target_right_param = target_position.target_right_param;

    if(target_position.target_left_param > real_target_right_param)
    {
        real_target_right_param += 1;
    }

    if(nearest_unused_right_param - nearest_unused_left_param <
        real_target_right_param - target_position.target_left_param)
    {
        target_position.real_left_param = nearest_unused_left_param;
        target_position.real_right_param = nearest_unused_right_param;
    }
    else if(real_target_right_param > nearest_unused_right_param)
    {
        target_position.real_right_param = nearest_unused_right_param;
        target_position.real_left_param = nearest_unused_right_param -
          (real_target_right_param - target_position.target_left_param);
    }
    else if(target_position.target_left_param < nearest_unused_left_param)
    {
        target_position.real_left_param = nearest_unused_left_param;
        target_position.real_right_param = nearest_unused_left_param +
          (real_target_right_param - target_position.target_left_param);
    }
    else
    {
        target_position.real_left_param = target_position.target_left_param;
        target_position.real_right_param = real_target_right_param;
    }

    if(target_position.real_right_param >= 1)
    {
        target_position.real_right_param -= 1;
    }

    return true;
}

bool UnitNodeLine::insertValidPosition(
    const UnitNodePosition &valid_position)
{
    UnitNodePosition* insert_position = new UnitNodePosition();
    insert_position->node_id = valid_position.node_id;
    insert_position->node_type = valid_position.node_type;
    insert_position->target_left_param = valid_position.target_left_param;
    insert_position->target_right_param = valid_position.target_right_param;
    insert_position->target_height = valid_position.target_height;
    insert_position->real_left_param = valid_position.real_left_param;
    insert_position->real_right_param = valid_position.real_right_param;
    insert_position->real_height = valid_position.real_height;

    if(insert_position->real_left_param > insert_position->real_right_param)
    {
        insert_position->real_right_param += 1.0;
    }

    if(position_line == nullptr)
    {
        position_line = insert_position;
        return true;
    }

    UnitNodePosition* search_position = position_line;
    UnitNodePosition* prev_search_position = search_position->prev_position;

    while(search_position != nullptr)
    {
        if(insert_position->real_right_param <= search_position->real_left_param)
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

    if(target_wall_type != NodeType::OuterWall &&
        target_wall_type != NodeType::InnerWall)
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
    UnitNodePosition& target_position)
{
    if(!wall_boundary_line.updatePosition(target_position))
    {
        std::cout << "WallUnitNodeLine::insertPosition :\n" <<
          "updatePosition failed!\n";

        return false;
    }

    if(!wall_boundary_line.insertValidPosition(target_position))
    {
        std::cout << "WallUnitNodeLine::insertPosition :\n" <<
          "insertValidPosition failed!\n";

        return false;
    }

    return true;
}

bool UnitNodeLineManager::reset()
{
    for(WallUnitNodeLine& wall_line : wall_line_vec)
    {
        wall_line.reset();
    }

    wall_line_vec.clear();

    valid_boundary_polygon_vec.clear();

    return true;
}

bool UnitNodeLineManager::resetButRemainWall()
{
    for(WallUnitNodeLine& wall_line : wall_line_vec)
    {
        wall_line.reset();
    }

    valid_boundary_polygon_vec.clear();

    return true;
}

bool UnitNodeLineManager::haveThisWallLine(
    const size_t& wall_id,
    const NodeType& wall_type)
{
    if(wall_line_vec.size() == 0)
    {
        return false;
    }

    for(const WallUnitNodeLine& wall_line : wall_line_vec)
    {
        if(wall_line.wall_id == wall_id && wall_line.wall_type == wall_type)
        {
            return true;
        }
    }

    return false;
}

bool UnitNodeLineManager::getWallLineIdx(
    const size_t& wall_id,
    const NodeType& wall_type,
    size_t& wall_line_idx)
{
    wall_line_idx = 0;

    if(wall_line_vec.size() == 0)
    {
        std::cout << "UnitNodeLineManager::getWallLineIdx :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "wall_line_vec is empty!\n";

        return false;
    }

    for(size_t i = 0; i < wall_line_vec.size(); ++i)
    {
        const WallUnitNodeLine& wall_line = wall_line_vec[i];

        if(wall_line.wall_id != wall_id ||
            wall_line.wall_type != wall_type)
        {
            continue;
        }

        wall_line_idx = i;

        return true;
    }

    std::cout << "UnitNodeLineManager::getWallLineIdx :\n" <<
      "Input :\n" <<
      "\t wall_id = " << wall_id << std::endl <<
      "\t wall_type = " << wall_type << std::endl <<
      "this wall not exist!\n";

    return false;
}

bool UnitNodeLineManager::createWallLine(
    const size_t& wall_id,
    const NodeType& wall_type)
{
    if(haveThisWallLine(wall_id, wall_type))
    {
        std::cout << "UnitNodeLineManager::createWallLine :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "this wall already exist!\n";

        return false;
    }

    WallUnitNodeLine new_wall_line;

    if(!new_wall_line.setWall(wall_id, wall_type))
    {
        std::cout << "UnitNodeLineManager::createWallLine :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "setWall failed!\n";

        return false;
    }

    wall_line_vec.emplace_back(new_wall_line);

    return true;
}

bool UnitNodeLineManager::setBoundaryPolygon(
    const size_t &wall_id,
    const NodeType &wall_type,
    const EasyPolygon2D &boundary_polygon)
{
    if(wall_line_vec.size() == 0)
    {
        std::cout << "UnitNodeLineManager::setBoundaryPolygon :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "wall_line_vec is empty!\n";

        return false;
    }

    size_t wall_line_idx;

    if(!getWallLineIdx(wall_id, wall_type, wall_line_idx))
    {
        std::cout << "UnitNodeLineManager::setBoundaryPolygon :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "getWallLineIdx failed!\n";

        return false;
    }

    WallUnitNodeLine& wall_line = wall_line_vec[wall_line_idx];

    if(!wall_line.setBoundaryPolygon(boundary_polygon))
    {
        std::cout << "UnitNodeLineManager::setBoundaryPolygon :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "setBoundaryPolygon failed!\n";

        return false;
    }

    return true;
}

bool UnitNodeLineManager::getMaxHeight(
    const size_t &wall_id,
    const NodeType &wall_type,
    const UnitNodePosition& target_position,
    float &max_height)
{
    max_height = std::numeric_limits<float>::max();

    const float error_max = 0.0001;

    size_t wall_line_idx;

    if(!getWallLineIdx(wall_id, wall_type, wall_line_idx))
    {
        std::cout << "UnitNodeLineManager::getMaxHeight :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "\t target_position = [" << target_position.target_left_param << "," <<
          target_position.target_right_param << "]\n" <<
          "getWallLineIdx failed!\n";

        return false;
    }

    WallUnitNodeLine& wall_line = wall_line_vec[wall_line_idx];

    if(target_position.real_right_param - target_position.real_left_param < error_max)
    {
        max_height = 0;
        return true;
    }

    EasyLine2D base_line;
    EasyPolygonPoint2D base_line_start_point, base_line_end_point;

    if(!base_line_start_point.updateByPolygonParam(
          wall_line.wall_boundary_polygon,
          target_position.real_left_param))
    {
        std::cout << "UnitNodeLineManager::getMaxHeight :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "\t target_position = [" << target_position.target_left_param << "," <<
          target_position.target_right_param << "]\n" <<
          "updateByPolygonParam for left polygon point failed!\n";

        return false;
    }

    if(!base_line_end_point.updateByPolygonParam(
          wall_line.wall_boundary_polygon,
          target_position.real_right_param))
    {
        std::cout << "UnitNodeLineManager::getMaxHeight :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "\t target_position = [" << target_position.target_left_param << "," <<
          target_position.target_right_param << "]\n" <<
          "updateByPolygonParam for right polygon point failed!\n";

        return false;
    }

    base_line.setPosition(base_line_start_point.position, base_line_end_point.position);

    for(const WallUnitNodeLine& wall_line : wall_line_vec)
    {
        const EasyPolygon2D& wall_boundary_polygon = wall_line.wall_boundary_polygon;

        if(wall_line.wall_id != wall_id || wall_line.wall_type != wall_type)
        {
            const float polygon_dist_to_line = EasyComputation::getPolygonDistToLine(
                wall_boundary_polygon, base_line);

            max_height = std::min(max_height, polygon_dist_to_line);

            continue;
        }

        for(size_t i = 0; i < wall_boundary_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &currnet_point = wall_boundary_polygon.point_list[i];
            const EasyPoint2D &next_point = wall_boundary_polygon.point_list[
              (i + 1) % wall_boundary_polygon.point_list.size()];

            EasyLine2D polygon_line;
            polygon_line.setPosition(currnet_point, next_point);

            const float polygon_line_dist_to_line = EasyComputation::getLineDistToLine(
                base_line, polygon_line);

            if(polygon_line_dist_to_line < error_max)
            {
                continue;
            }

            max_height = std::min(max_height, polygon_line_dist_to_line);
        }
    }

    for(const EasyPolygon2D &valid_boundary_polygon : valid_boundary_polygon_vec)
    {
        const float polygon_dist_to_line = EasyComputation::getPolygonDistToLine(
            valid_boundary_polygon, base_line);

        max_height = std::min(max_height, polygon_dist_to_line);
    }

    return true;
}

bool UnitNodeLineManager::removePosition(
    const size_t& node_id,
    const NodeType& node_type)
{
    for(WallUnitNodeLine& wall_line : wall_line_vec)
    {
        UnitNodePosition* position = wall_line.wall_boundary_line.position_line;

        while(position != nullptr)
        {
            if(position->node_id != node_id || position->node_type != node_type)
            {
                position = position->next_position;
                continue;
            }

            if(position->prev_position != nullptr)
            {
                if(position->next_position != nullptr)
                {
                    position->prev_position->next_position = position->next_position;
                    position->next_position->prev_position = position->prev_position;

                    delete(position);

                    return true;
                }

                position->prev_position->next_position = nullptr;

                delete(position);

                return true;
            }

            if(position->next_position != nullptr)
            {
                wall_line.wall_boundary_line.position_line = position->next_position;
                position->next_position->prev_position = nullptr;

                delete(position);

                return true;
            }

            wall_line.wall_boundary_line.position_line = nullptr;

            delete(position);

            return true;
        }
    }

    // std::cout << "UnitNodeLineManager::removePosition :\n" <<
      // "Input :\n" <<
      // "\t node_id = " << node_id << std::endl <<
      // "\t node_type = " << node_type << std::endl <<
      // "this node not found!\n";

    return false;
}

bool UnitNodeLineManager::insertPosition(
    const size_t &wall_id,
    const NodeType &wall_type,
    UnitNodePosition& target_position)
{
    removePosition(target_position.node_id, target_position.node_type);

    size_t wall_line_idx;

    if(!getWallLineIdx(wall_id, wall_type, wall_line_idx))
    {
        std::cout << "UnitNodeLineManager::insertPosition :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "getWallLineIdx failed!\n";

        return false;
    }

    WallUnitNodeLine& wall_line = wall_line_vec[wall_line_idx];

    if(!wall_line.wall_boundary_line.updatePosition(target_position))
    {
        std::cout << "UnitNodeLineManager::insertPosition :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "updatePosition failed!\n";

        return false;
    }

    float max_height;

    if(!getMaxHeight(wall_id, wall_type, target_position, max_height))
    {
        std::cout << "UnitNodeLineManager::insertPosition :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "getMaxHeight failed!\n";

        return false;
    }

    target_position.real_height = std::min(max_height, target_position.target_height);

    if(!wall_line.wall_boundary_line.insertValidPosition(target_position))
    {
        std::cout << "UnitNodeLineManager::insertPosition :\n" <<
          "Input :\n" <<
          "\t wall_id = " << wall_id << std::endl <<
          "\t wall_type = " << wall_type << std::endl <<
          "insertValidPosition failed!\n";

        return false;
    }

    return true;
}

