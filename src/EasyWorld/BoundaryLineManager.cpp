#include "BoundaryLineManager.h"

bool BoundaryLine::reset()
{
    place_idx = 0;
    line_start_position = -1;
    line_end_position = -1;
    line_width = -1;
    line_height = -1;
    line_real_height = -1;

    line_room_num = 0;
    room_name_vec.clear();

    if(next_line != nullptr)
    {
        next_line->reset();

        delete(next_line);
        next_line = nullptr;
    }

    return true;
}

bool BoundaryLine::outputInfo(
    const size_t &info_level) const
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "BoundaryLine :" << std::endl <<
      line_start << "\tline_position = [" << line_start_position << "," <<
      line_end_position << "]" << std::endl <<
      line_start << "\tline_target_size = [" << line_width << "," <<
      line_height << "]" << std::endl <<
      line_start << "\tline_real_height = " << line_real_height << std::endl <<
      line_start << "\tline_room_num = " << line_room_num << std::endl <<
      line_start << "\troom_name_vec = ";

    if(room_name_vec.size() == 0)
    {
        std::cout << "NULL" << std::endl;
    }
    else
    {
        for(const std::string &room_name : room_name_vec)
        {
            std::cout << room_name << " ";
        }

        std::cout << std::endl;
    }

    return true;
}

BoundaryLineList::~BoundaryLineList()
{
    reset();
}

bool BoundaryLineList::reset()
{
    if(boundary_line_list_ != nullptr)
    {
        boundary_line_list_->reset();

        delete(boundary_line_list_);
        boundary_line_list_ = nullptr;
    }

    return true;
}

bool BoundaryLineList::setBoundaryLength(
    const float &boundary_length)
{
    if(boundary_length <= 0)
    {
        std::cout << "BoundaryLineList::setBoundaryLength : " << std::endl <<
          "Input :\n" <<
          "\tboundary_length = " << boundary_length << std::endl <<
          "boundary length not valid!" << std::endl;

        return false;
    }

    boundary_length_ = boundary_length;

    return true;
}

bool BoundaryLineList::findNearestUnusedBoundaryLine(
    const BoundaryLine &new_boundary_line,
    float &nearest_unused_start_position,
    float &nearest_unused_end_position)
{
    if(boundary_line_list_ == nullptr)
    {
        nearest_unused_start_position = 0;
        nearest_unused_end_position = boundary_length_;

        return true;
    }

    BoundaryLine* search_boundary_line = boundary_line_list_;
    float current_unused_start_position = 0;
    float current_unused_end_position;
    float min_dist_to_unused_line = std::numeric_limits<float>::max();

    while(search_boundary_line != nullptr)
    {
        current_unused_end_position = search_boundary_line->line_start_position;

        if(current_unused_end_position > current_unused_start_position)
        {
            float current_min_dist_to_unused_line_start =
              std::fabs(current_unused_start_position - new_boundary_line.line_start_position);

            if(current_min_dist_to_unused_line_start < min_dist_to_unused_line)
            {
                min_dist_to_unused_line = current_min_dist_to_unused_line_start;

                nearest_unused_start_position = current_unused_start_position;
                nearest_unused_end_position = current_unused_end_position;
            }

            float current_min_dist_to_unused_line_end =
              std::fabs(current_unused_end_position - new_boundary_line.line_start_position);

            if(current_min_dist_to_unused_line_end < min_dist_to_unused_line)
            {
                min_dist_to_unused_line = current_min_dist_to_unused_line_end;

                nearest_unused_start_position = current_unused_start_position;
                nearest_unused_end_position = current_unused_end_position;
            }
        }

        if(new_boundary_line.line_start_position < current_unused_end_position)
        {
            return true;
        }

        current_unused_start_position = search_boundary_line->line_end_position;

        search_boundary_line = search_boundary_line->next_line;
    }

    current_unused_end_position = boundary_length_;

    nearest_unused_start_position = current_unused_start_position;
    nearest_unused_end_position = current_unused_end_position;

    return true;
}

bool BoundaryLineList::findNearestValidBoundaryLine(
    const BoundaryLine &new_boundary_line,
    BoundaryLine &valid_boundary_line)
{
    float nearest_unused_start_position;
    float nearest_unused_end_position;

    if(!findNearestUnusedBoundaryLine(
          new_boundary_line,
          nearest_unused_start_position,
          nearest_unused_end_position))
    {
        std::cout << "BoundaryLineList::findNearestValidBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "new_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "]" << std::endl <<
          "findNearestUnusedBoundaryLine for new boundary line failed!" << std::endl;

        return false;
    }

    valid_boundary_line = new_boundary_line;

    if(nearest_unused_end_position - nearest_unused_start_position <
        new_boundary_line.line_width)
    {
        valid_boundary_line.line_start_position = nearest_unused_start_position;
        valid_boundary_line.line_end_position = nearest_unused_end_position;
    }
    else if(new_boundary_line.line_end_position > nearest_unused_end_position)
    {
        valid_boundary_line.line_end_position = nearest_unused_end_position;
        valid_boundary_line.line_start_position = nearest_unused_end_position -
          (new_boundary_line.line_end_position - new_boundary_line.line_start_position);
    }
    else if(new_boundary_line.line_start_position < nearest_unused_start_position)
    {
        valid_boundary_line.line_start_position = nearest_unused_start_position;
        valid_boundary_line.line_end_position = nearest_unused_start_position +
          (new_boundary_line.line_end_position - new_boundary_line.line_start_position);
    }

    return true;
}

bool BoundaryLineList::insertValidBoundaryLine(
    const BoundaryLine &valid_boundary_line)
{
    BoundaryLine* insert_boundary_line = new BoundaryLine();
    insert_boundary_line->place_idx = valid_boundary_line.place_idx;
    insert_boundary_line->line_start_position = valid_boundary_line.line_start_position;
    insert_boundary_line->line_end_position = valid_boundary_line.line_end_position;
    insert_boundary_line->line_width = valid_boundary_line.line_width;
    insert_boundary_line->line_height = valid_boundary_line.line_height;
    insert_boundary_line->line_real_height = valid_boundary_line.line_real_height;
    insert_boundary_line->line_room_num = valid_boundary_line.line_room_num;
    insert_boundary_line->room_name_vec = valid_boundary_line.room_name_vec;

    if(boundary_line_list_ == nullptr)
    {
        boundary_line_list_ = insert_boundary_line;

        return true;
    }

    BoundaryLine* search_boundary_line = boundary_line_list_;
    BoundaryLine* prev_search_boundary_line = search_boundary_line->prev_line;

    while(search_boundary_line != nullptr)
    {
        if(valid_boundary_line.line_end_position <= search_boundary_line->line_start_position)
        {
            insert_boundary_line->next_line = search_boundary_line;
            search_boundary_line->prev_line = insert_boundary_line;

            if(prev_search_boundary_line == nullptr)
            {
                boundary_line_list_ = insert_boundary_line;

                return true;
            }

            prev_search_boundary_line->next_line = insert_boundary_line;
            insert_boundary_line->prev_line = prev_search_boundary_line;

            return true;
        }

        prev_search_boundary_line = search_boundary_line;
        search_boundary_line = search_boundary_line->next_line;
    }

    prev_search_boundary_line->next_line = insert_boundary_line;
    insert_boundary_line->prev_line = prev_search_boundary_line;

    return true;
}

bool BoundaryLineList::outputInfo(
    const size_t &info_level) const
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "BoundaryLineList :" << std::endl <<
      line_start << "\tboundary_length = " << boundary_length_ << std::endl;

    BoundaryLine* search_boundary_line = boundary_line_list_;
    while(search_boundary_line != nullptr)
    {
        search_boundary_line->outputInfo(info_level + 1);

        search_boundary_line = search_boundary_line->next_line;
    }

    return true;
}

bool WallBoundaryLineList::resetBoundaryLine()
{
    for(BoundaryLineList &boundary_line_list : boundary_line_list_vec_)
    {
        boundary_line_list.reset();
    }

    return true;
}

bool WallBoundaryLineList::reset()
{
    wall_id_ = 0;
    wall_type_ = NodeType::NodeFree;

    resetBoundaryLine();

    return true;
}

bool WallBoundaryLineList::setWall(
    const size_t &wall_id,
    const NodeType &wall_type)
{
    wall_id_ = 0;
    wall_type_ = NodeType::NodeFree;

    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "WallBoundaryLineList::setWall : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "wall_type is not the wall type!" << std::endl;

        return false;
    }

    wall_id_ = wall_id;
    wall_type_ = wall_type;

    return true;
}

bool WallBoundaryLineList::setBoundaryPolygon(
    const EasyPolygon2D &boundary_polygon)
{
    resetBoundaryLine();

    if(boundary_polygon.point_list.size() == 0)
    {
        std::cout << "WallBoundaryLineList::setBoundaryPolygon : " << std::endl <<
          "boundary polygon is empty!" << std::endl;

        return false;
    }

    boundary_line_list_vec_.resize(boundary_polygon.point_list.size());

    for(size_t i = 0; i < boundary_polygon.point_list.size(); ++i)
    {
        const EasyPoint2D &current_point = boundary_polygon.point_list[i];
        const EasyPoint2D &next_point = boundary_polygon.point_list[
        (i + 1) % boundary_polygon.point_list.size()];

        const float current_line_length = EasyComputation::pointDist(current_point, next_point);

        if(!boundary_line_list_vec_[i].setBoundaryLength(current_line_length))
        {
            std::cout << "WallBoundaryLineList::setBoundaryPolygon : " << std::endl <<
              "setBoundaryLength for line-" << i << " failed!" << std::endl;

            return false;
        }
    }

    wall_boundary_polygon_ = boundary_polygon;

    return true;
}

bool WallBoundaryLineList::insertBoundaryLine(
    const size_t &boundary_idx,
    const BoundaryLine &valid_boundary_line)
{
    if(boundary_idx >= boundary_line_list_vec_.size())
    {
        std::cout << "WallBoundaryLineList::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl;
        valid_boundary_line.outputInfo(1);
        std::cout << "boundary_idx out of range!" << std::endl;

        return false;
    }

    if(!boundary_line_list_vec_[boundary_idx].insertValidBoundaryLine(valid_boundary_line))
    {
        std::cout << "WallBoundaryLineList::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl;
        valid_boundary_line.outputInfo(1);
        std::cout << "insertValidBoundaryLine failed!" << std::endl;

        return false;
    }

    return true;
}

bool WallBoundaryLineList::getBoundaryPoint(
    const size_t &boundary_idx,
    const float &boundary_position,
    const float &point_height,
    EasyPoint2D &boundary_point)
{
    if(boundary_idx >= boundary_line_list_vec_.size())
    {
        std::cout << "WallBoundaryLineList::getBoundaryPoint : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tboundary_position = " << boundary_position << std::endl <<
          "\tpoint_height = " << point_height << std::endl <<
          "boundary_idx out of range!" << std::endl;

        return false;
    }

    const BoundaryLineList &boundary_line_list = boundary_line_list_vec_[boundary_idx];

    const float &boundary_length = boundary_line_list.boundary_length_;

    if(boundary_length == 0)
    {
        std::cout << "WallBoundaryLineList::getBoundaryPoint : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tboundary_position = " << boundary_position << std::endl <<
          "\tpoint_height = " << point_height << std::endl <<
          "boundary length is 0!" << std::endl;

        return false;
    }

    const EasyPoint2D &boundary_start_point = wall_boundary_polygon_.point_list[boundary_idx];

    const EasyPoint2D &boundary_end_point = wall_boundary_polygon_.point_list[
    (boundary_idx + 1) % wall_boundary_polygon_.point_list.size()];

    EasyPoint2D boundary_unit_direction;
    boundary_unit_direction.setPosition(
        (boundary_end_point.x - boundary_start_point.x) / boundary_length,
        (boundary_end_point.y - boundary_start_point.y) / boundary_length);

    boundary_point.setPosition(
        boundary_start_point.x + boundary_position * boundary_unit_direction.x - point_height * boundary_unit_direction.y,
        boundary_start_point.y + boundary_position * boundary_unit_direction.y + point_height * boundary_unit_direction.x);

    return true;
}

bool WallBoundaryLineList::getBoundaryLinePolygon(
    const size_t &boundary_idx,
    const float &line_start_position,
    const float &line_width,
    const float &line_height,
    EasyPolygon2D &boundary_line_polygon)
{
    boundary_line_polygon.reset();

    if(boundary_idx >= boundary_line_list_vec_.size())
    {
        std::cout << "WallBoundaryLineList::getBoundaryLinePolygon : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tline_start_position = " << line_start_position << std::endl <<
          "\tline_size = [" << line_width << "," << line_height << "]" << std::endl <<
          "boundary_idx out of range!" << std::endl;

        return false;
    }

    EasyPoint2D boundary_point;

    if(!getBoundaryPoint(boundary_idx, line_start_position, 0, boundary_point))
    {
        std::cout << "WallBoundaryLineList::getBoundaryLinePolygon : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tline_start_position = " << line_start_position << std::endl <<
          "\tline_size = [" << line_width << "," << line_height << "]" << std::endl <<
          "getBoundaryPoint failed!" << std::endl;

        return false;
    }
    boundary_line_polygon.addPoint(boundary_point);

    if(!getBoundaryPoint(boundary_idx, line_start_position + line_width, 0, boundary_point))
    {
        std::cout << "WallBoundaryLineList::getBoundaryLinePolygon : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tline_start_position = " << line_start_position << std::endl <<
          "\tline_size = [" << line_width << "," << line_height << "]" << std::endl <<
          "getBoundaryPoint failed!" << std::endl;

        return false;
    }
    boundary_line_polygon.addPoint(boundary_point);

    if(!getBoundaryPoint(boundary_idx, line_start_position + line_width, line_height, boundary_point))
    {
        std::cout << "WallBoundaryLineList::getBoundaryLinePolygon : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tline_start_position = " << line_start_position << std::endl <<
          "\tline_size = [" << line_width << "," << line_height << "]" << std::endl <<
          "getBoundaryPoint failed!" << std::endl;

        return false;
    }
    boundary_line_polygon.addPoint(boundary_point);

    if(!getBoundaryPoint(boundary_idx, line_start_position, line_height, boundary_point))
    {
        std::cout << "WallBoundaryLineList::getBoundaryLinePolygon : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tline_start_position = " << line_start_position << std::endl <<
          "\tline_size = [" << line_width << "," << line_height << "]" << std::endl <<
          "getBoundaryPoint failed!" << std::endl;

        return false;
    }
    boundary_line_polygon.addPoint(boundary_point);

    return true;
}

bool WallBoundaryLineList::outputInfo(
    const size_t &info_level) const
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "WallBoundaryLineListVec:" << std::endl <<
      line_start << "\twall_id = " << wall_id_ << std::endl <<
      line_start << "\twall_type = " << wall_type_ << std::endl;
    for(const BoundaryLineList &boundary_line_list : boundary_line_list_vec_)
    {
        boundary_line_list.outputInfo(info_level + 1);
    }

    return true;
}

bool BoundaryLineManager::reset()
{
    for(WallBoundaryLineList &wall_boundary_line_list : wall_boundary_line_list_vec_)
    {
        wall_boundary_line_list.reset();
    }

    wall_boundary_line_list_vec_.clear();

    current_place_idx_ = 0;

    valid_boundary_polygon_vec_.clear();

    return true;
}

bool BoundaryLineManager::addBoundaryPolygon(
    const size_t &wall_id,
    const NodeType &wall_type,
    const EasyPolygon2D &boundary_polygon)
{
    WallBoundaryLineList new_wall_boundary_line_list;

    if(!new_wall_boundary_line_list.setWall(wall_id, wall_type))
    {
        std::cout << "BoundaryLineManager::addBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "setWall failed!" << std::endl;

        return false;
    }

    if(!new_wall_boundary_line_list.setBoundaryPolygon(
          boundary_polygon))
    {
        std::cout << "BoundaryLineManager::addBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "setBoundaryPolygon failed!" << std::endl;

        return false;
    }

    wall_boundary_line_list_vec_.emplace_back(new_wall_boundary_line_list);

    return true;
}

bool BoundaryLineManager::setBoundaryPolygon(
    const size_t &wall_id,
    const NodeType &wall_type,
    const EasyPolygon2D &boundary_polygon)
{
    if(wall_boundary_line_list_vec_.size() == 0)
    {
        std::cout << "BoundaryLineManager::setBoundaryPolygon :" << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "wall_boundary_line_list_vec_ is empty!" << std::endl;

        return false;
    }

    size_t wall_boundary_line_list_idx;

    if(!getWallBoundaryLineListIdx(wall_id, wall_type, wall_boundary_line_list_idx))
    {
        std::cout << "BoundaryLineManager::setBoundaryPolygon :" << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "getWallBoundaryLineListIdx failed!" << std::endl;

        return false;
    }

    WallBoundaryLineList &wall_boundary_line_list =
      wall_boundary_line_list_vec_[wall_boundary_line_list_idx];

    if(!wall_boundary_line_list.setBoundaryPolygon(boundary_polygon))
    {
        std::cout << "BoundaryLineManager::setBoundaryPolygon :" << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "setBoundaryPolygon failed!" << std::endl;

        return false;
    }

    return true;
}

bool BoundaryLineManager::insertBoundaryLine(
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &boundary_idx,
    const BoundaryLine &new_boundary_line,
    BoundaryLine &valid_boundary_line)
{
    size_t wall_boundary_line_list_idx;

    if(!getWallBoundaryLineListIdx(wall_id, wall_type, wall_boundary_line_list_idx))
    {
        std::cout << "BoundaryLineManager::insertBoundaryLine :" << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tnew_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "], height = " << new_boundary_line.line_height << std::endl <<
          "getWallBoundaryLineListIdx failed!" << std::endl;

        return false;
    }

    WallBoundaryLineList &wall_boundary_line_list =
      wall_boundary_line_list_vec_[wall_boundary_line_list_idx];

    if(boundary_idx >= wall_boundary_line_list.boundary_line_list_vec_.size())
    {
        std::cout << "WallBoundaryLineList::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tnew_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "], height = " << new_boundary_line.line_height << std::endl <<
          "boundary idx out of range!" << std::endl;

        return false;
    }

    if(!wall_boundary_line_list.boundary_line_list_vec_[boundary_idx].findNearestValidBoundaryLine(
          new_boundary_line,
          valid_boundary_line))
    {
        std::cout << "WallBoundaryLineList::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tnew_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "], height = " << new_boundary_line.line_height << std::endl <<
          "findNearestUnusedBoundaryLine failed!" << std::endl;

        return false;
    }

    if(valid_boundary_line.line_start_position > valid_boundary_line.line_end_position)
    {
        std::cout << "WallBoundaryLineList::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tnew_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "], height = " << new_boundary_line.line_height << std::endl <<
          "valid boundary line width < 0!" << std::endl;

        return false;
    }

    float max_height;
    if(!getMaxHeight(wall_id, wall_type, boundary_idx, valid_boundary_line, max_height))
    {
        std::cout << "WallBoundaryLineList::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tnew_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "], height = " << new_boundary_line.line_height << std::endl <<
          "getMaxHeight failed!" << std::endl;

        return false;
    }

    valid_boundary_line.line_real_height =
      std::fmin(max_height, valid_boundary_line.line_height);
    valid_boundary_line.place_idx = current_place_idx_;
    ++current_place_idx_;

    if(!wall_boundary_line_list.insertBoundaryLine(boundary_idx, valid_boundary_line))
    {
        --current_place_idx_;

        std::cout << "WallBoundaryLineList::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tnew_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "], height = " << new_boundary_line.line_height << std::endl <<
          "insertBoundaryLine failed!" << std::endl;

        return false;
    }

    EasyPolygon2D new_valid_boundary_polygon;
    if(!wall_boundary_line_list_vec_[boundary_idx].getBoundaryLinePolygon(
          boundary_idx,
          valid_boundary_line.line_start_position,
          valid_boundary_line.line_width,
          valid_boundary_line.line_real_height,
          new_valid_boundary_polygon))
    {
        std::cout << "WallBoundaryLineList::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\tnew_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "], height = " << new_boundary_line.line_height << std::endl <<
          "getBoundaryLinePolygon failed!" << std::endl;

        return false;
    }

    valid_boundary_polygon_vec_.emplace_back(new_valid_boundary_polygon);

    return true;
}

bool BoundaryLineManager::getWallBoundaryLineListIdx(
    const size_t &wall_id,
    const NodeType &wall_type,
    size_t &wall_boundary_line_list_idx)
{
    wall_boundary_line_list_idx = 0;

    if(wall_boundary_line_list_vec_.size() == 0)
    {
        std::cout << "BoundaryLineManager::getWallBoundaryLineListIdx : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "wall_boundary_line_list_vec_ is empty!" << std::endl;

        return false;
    }

    for(size_t i = 0; i < wall_boundary_line_list_vec_.size(); ++i)
    {
        WallBoundaryLineList &wall_boundary_line_list = wall_boundary_line_list_vec_[i];
        if(wall_boundary_line_list.wall_id_ != wall_id ||
            wall_boundary_line_list.wall_type_ != wall_type)
        {
            continue;
        }

        wall_boundary_line_list_idx = i;

        return true;
    }

    std::cout << "BoundaryLineManager::getWallBoundaryLineListIdx : " << std::endl <<
      "Input :\n" <<
      "\twall_id = " << wall_id << std::endl <<
      "\twall_type = " << wall_type << std::endl <<
      "this wall not exist!" << std::endl;

    return false;
}

bool BoundaryLineManager::getMaxHeight(
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &boundary_idx,
    const BoundaryLine &boundary_line,
    float &max_height)
{
    max_height = std::numeric_limits<float>::max();

    size_t wall_boundary_line_list_idx;

    if(!getWallBoundaryLineListIdx(wall_id, wall_type, wall_boundary_line_list_idx))
    {
        std::cout << "BoundaryLineManager::getMaxHeight :" << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "boundary_idx = " << boundary_idx << std::endl <<
          "boundary_line = [" << boundary_line.line_start_position << "," <<
          boundary_line.line_end_position << "], height = " << boundary_line.line_height << std::endl <<
          "getWallBoundaryLineListIdx failed!" << std::endl;

        return false;
    }

    WallBoundaryLineList &wall_boundary_line_list =
      wall_boundary_line_list_vec_[wall_boundary_line_list_idx];

    if(boundary_idx >= wall_boundary_line_list.boundary_line_list_vec_.size())
    {
        std::cout << "WallBoundaryLineList::getMaxHeight : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "boundary_idx = " << boundary_idx << std::endl <<
          "boundary_line = [" << boundary_line.line_start_position << "," <<
          boundary_line.line_end_position << "], height = " << boundary_line.line_height << std::endl <<
          "boundary idx out of range!" << std::endl;

        return false;
    }

    if(boundary_line.line_start_position == boundary_line.line_end_position)
    {
        max_height = 0;
        return true;
    }

    std::cout << "IN1-1-1-1" << std::endl;
    EasyLine2D base_line;
    EasyPoint2D base_line_start_point, base_line_end_point;
    if(!wall_boundary_line_list.getBoundaryPoint(boundary_idx, boundary_line.line_start_position, 0, base_line_start_point))
    {
        std::cout << "WallBoundaryLineList::getMaxHeight : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "boundary_idx = " << boundary_idx << std::endl <<
          "boundary_line = [" << boundary_line.line_start_position << "," <<
          boundary_line.line_end_position << "], height = " << boundary_line.line_height << std::endl <<
          "getBoundaryPoint for base_line_start_point failed!" << std::endl;

        return false;
    }
    if(!wall_boundary_line_list.getBoundaryPoint(boundary_idx, boundary_line.line_end_position, 0, base_line_end_point))
    {
        std::cout << "WallBoundaryLineList::getMaxHeight : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "boundary_idx = " << boundary_idx << std::endl <<
          "boundary_line = [" << boundary_line.line_start_position << "," <<
          boundary_line.line_end_position << "], height = " << boundary_line.line_height << std::endl <<
          "getBoundaryPoint for base_line_end_point failed!" << std::endl;

        return false;
    }
    std::cout << "IN1-1-1-2" << std::endl;

    base_line.setPosition(base_line_start_point, base_line_end_point);

    for(const WallBoundaryLineList &wall_boundary_line_list : wall_boundary_line_list_vec_)
    {
        if(wall_boundary_line_list.wall_type_ != NodeType::InnerWall)
        {
            continue;
        }

        const EasyPolygon2D &innerwall_boundary_polygon = wall_boundary_line_list.wall_boundary_polygon_;

        const float polygon_dist_to_line = EasyComputation::getPolygonDistToLine(
            innerwall_boundary_polygon, base_line);

        max_height = std::fmin(max_height, polygon_dist_to_line);
    }

    for(const EasyPolygon2D &valid_boundary_polygon : valid_boundary_polygon_vec_)
    {
        const float polygon_dist_to_line = EasyComputation::getPolygonDistToLine(
            valid_boundary_polygon, base_line);

        max_height = std::fmin(max_height, polygon_dist_to_line);
    }

    return true;
}

bool BoundaryLineManager::outputInfo(
    const size_t &info_level) const
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "WallBoundaryLineVec:" << std::endl;
    for(const WallBoundaryLineList &wall_boundary_line_list : wall_boundary_line_list_vec_)
    {
        wall_boundary_line_list.outputInfo(info_level + 1);
    }

    return true;
}

