#include "WorldPlaceGenerator.h"

bool BoundaryLine::reset()
{
    line_start_position = -1;
    line_end_position = -1;
    line_height = -1;
    line_real_height = -1;

    if(next_line != nullptr)
    {
        next_line->reset();

        delete(next_line);
        next_line = nullptr;
    }

    return true;
}

bool BoundaryLine::outputInfo(
    const size_t &info_level)
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "BoundaryLine :" << std::endl <<
      line_start << "\tline_position = [" << line_start_position << "," <<
      line_end_position << "]" << std::endl <<
      line_start << "\tline_height = " << line_height << std::endl <<
      line_start << "\tline_real_height = " << line_real_height << std::endl;

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
    // if(new_boundary_line.line_start_position > boundary_length_ ||
    //     new_boundary_line.line_end_position < 0)
    // {
    //     std::cout << "BoundaryLineList::isBoundaryLineValid : " << std::endl <<
    //       "Input :\n" <<
    //       "\t new_boundary_line = [" << new_boundary_line.line_start_position << "," <<
    //       new_boundary_line.line_end_position << "]" << std::endl <<
    //       "new boundary line out of range!" << std::endl;
    //
    //     return false;
    // }

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
        new_boundary_line.line_end_position - new_boundary_line.line_start_position)
    {
        valid_boundary_line.line_start_position = nearest_unused_start_position;
        valid_boundary_line.line_end_position = nearest_unused_end_position;
    }
    else if(new_boundary_line.line_end_position > nearest_unused_end_position)
    {
        valid_boundary_line.line_end_position = nearest_unused_end_position;
        valid_boundary_line.line_start_position = nearest_unused_end_position -
          (valid_boundary_line.line_end_position - valid_boundary_line.line_start_position);
    }
    else if(new_boundary_line.line_start_position < nearest_unused_start_position)
    {
        valid_boundary_line.line_start_position = nearest_unused_start_position;
        valid_boundary_line.line_end_position = nearest_unused_start_position +
          (valid_boundary_line.line_end_position - valid_boundary_line.line_start_position);
    }

    return true;
}

bool BoundaryLineList::insertValidBoundaryLine(
    const BoundaryLine &valid_boundary_line)
{
    BoundaryLine* insert_boundary_line = new BoundaryLine();
    insert_boundary_line->line_start_position = valid_boundary_line.line_start_position;
    insert_boundary_line->line_end_position = valid_boundary_line.line_end_position;
    insert_boundary_line->line_height = valid_boundary_line.line_height;
    insert_boundary_line->line_real_height = valid_boundary_line.line_real_height;

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
    const size_t &info_level)
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

bool BoundaryLineListManager::reset()
{
    for(BoundaryLineList &boundary_line_list : boundary_line_list_vec_)
    {
        boundary_line_list.reset();
    }

    return true;
}

bool BoundaryLineListManager::setBoundaryPolygon(
    const EasyPolygon2D &boundary_polygon)
{
    reset();

    if(boundary_polygon.point_list.size() == 0)
    {
        std::cout << "BoundaryLineListManager::setBoundaryPolygon : " << std::endl <<
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
            std::cout << "BoundaryLineListManager::setBoundaryPolygon : " << std::endl <<
              "setBoundaryLength for line-" << i << " failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool BoundaryLineListManager::getMaxHeight(
    const size_t &boundary_idx,
    const BoundaryLine &boundary_line,
    float &max_height)
{
    max_height = std::numeric_limits<float>::max();

    if(boundary_idx >= boundary_line_list_vec_.size())
    {
        std::cout << "BoundaryLineListManager::getMaxHeight : " << std::endl <<
          "Input :\n" <<
          "boundary_idx = " << boundary_idx << std::endl <<
          "boundary_line = [" << boundary_line.line_start_position << "," <<
          boundary_line.line_end_position << "], height = " << boundary_line.line_height << std::endl <<
          "boundary idx out of range!" << std::endl;

        return false;
    }

    EasyLine2D base_line;
    base_line.setPosition(boundary_line.line_start_position, 0, boundary_line.line_end_position, 0);

    const float current_line_length = boundary_line_list_vec_[boundary_idx].boundary_length_;

    if(current_line_length < 0)
    {
        std::cout << "BoundaryLineListManager::getMaxHeight : " << std::endl <<
          "Input :\n" <<
          "boundary_idx = " << boundary_idx << std::endl <<
          "boundary_line = [" << boundary_line.line_start_position << "," <<
          boundary_line.line_end_position << "], height = " << boundary_line.line_height << std::endl <<
          "current line length is 0!" << std::endl;

        return false;
    }

    BoundaryLineList &next_boundary_line_list = boundary_line_list_vec_[
      (boundary_idx + 1) % boundary_line_list_vec_.size()];
    BoundaryLineList &prev_boundary_line_list = boundary_line_list_vec_[
      (boundary_idx - 1 + boundary_line_list_vec_.size()) % boundary_line_list_vec_.size()];

    BoundaryLine* next_first_boundary_line = next_boundary_line_list.boundary_line_list_;
    if(next_first_boundary_line != nullptr)
    {
        EasyLine2D next_first_target_line;
        next_first_target_line.setPosition(
            current_line_length - next_first_boundary_line->line_real_height,
            next_first_boundary_line->line_start_position,
            current_line_length,
            next_first_boundary_line->line_real_height);

        const float next_first_target_line_dist = EasyComputation::getLineDistToLine(
            base_line, next_first_target_line);

        if(next_first_target_line_dist >= 0)
        {
            max_height = std::fmin(max_height, next_first_target_line_dist);
        }
    }

    BoundaryLine* prev_last_boundary_line = prev_boundary_line_list.boundary_line_list_;
    if(prev_last_boundary_line != nullptr)
    {
        while(prev_last_boundary_line->next_line != nullptr)
        {
            prev_last_boundary_line = prev_last_boundary_line->next_line;
        }

        const float prev_line_length = prev_boundary_line_list.boundary_length_;
        EasyLine2D prev_last_target_line;
        prev_last_target_line.setPosition(
            0,
            prev_line_length - prev_last_boundary_line->line_end_position,
            prev_last_boundary_line->line_real_height,
            prev_line_length - prev_last_boundary_line->line_end_position);

        const float prev_last_target_line_dist = EasyComputation::getLineDistToLine(
            base_line, prev_last_target_line);

        if(prev_last_target_line_dist >= 0)
        {
            max_height = std::fmin(max_height, prev_last_target_line_dist);
        }
    }

    return true;
}

bool BoundaryLineListManager::insertBoundaryLine(
    const size_t &boundary_idx,
    const BoundaryLine &new_boundary_line)
{
    if(boundary_idx >= boundary_line_list_vec_.size())
    {
        std::cout << "BoundaryLineListManager::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "boundary_idx = " << boundary_idx << std::endl <<
          "new_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "]" << std::endl <<
          "boundary idx out of range!" << std::endl;

        return false;
    }

    BoundaryLine valid_boundary_line;

    if(!boundary_line_list_vec_[boundary_idx].findNearestValidBoundaryLine(
          new_boundary_line,
          valid_boundary_line))
    {
        std::cout << "BoundaryLineListManager::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "boundary_idx = " << boundary_idx << std::endl <<
          "new_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "]" << std::endl <<
          "findNearestUnusedBoundaryLine failed!" << std::endl;

        return false;
    }

    float max_height;
    if(!getMaxHeight(boundary_idx, valid_boundary_line, max_height))
    {
        std::cout << "BoundaryLineListManager::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "boundary_idx = " << boundary_idx << std::endl <<
          "new_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "]" << std::endl <<
          "getMaxHeight failed!" << std::endl;

        return false;
    }

    valid_boundary_line.line_real_height =
      std::fmin(max_height, valid_boundary_line.line_height);

    if(!boundary_line_list_vec_[boundary_idx].insertValidBoundaryLine(valid_boundary_line))
    {
        std::cout << "BoundaryLineListManager::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "boundary_idx = " << boundary_idx << std::endl <<
          "new_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "]" << std::endl <<
          "insertValidBoundaryLine failed!" << std::endl;

        return false;
    }

    return true;
}

bool BoundaryLineListManager::outputInfo(
    const size_t &info_level)
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "BoundaryLineListVec:" << std::endl;
    for(BoundaryLineList &boundary_line_list : boundary_line_list_vec_)
    {
        boundary_line_list.outputInfo(info_level + 1);
    }

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

    if(!boundary_line_list_manager_.reset())
    {
        std::cout << "WorldPlaceGenerator::reset : " <<
          "reset for boundary_line_list_manager_ failed!" << std::endl;

        return false;
    }

    wall_boundary_polygon_.point_list.clear();
    is_wall_boundary_polygon_set_ = false;

    person_num_ = 0;
    is_person_num_set_ = false;

    return true;
}

bool WorldPlaceGenerator::setWallBoundaryPolygon(
    const EasyPolygon2D &wall_boundary_polygon)
{
    wall_boundary_polygon_.point_list.clear();

    is_wall_boundary_polygon_set_ = false;

    if(wall_boundary_polygon.point_list.size() == 0)
    {
        std::cout << "WorldPlaceGenerator::setWallBoundaryPolygon : " << std::endl <<
          "wall boundary polygon is empty!" << std::endl;

        return false;
    }

    wall_boundary_polygon_ = wall_boundary_polygon;

    is_wall_boundary_polygon_set_ = true;

    if(!boundary_line_list_manager_.setBoundaryPolygon(wall_boundary_polygon_))
    {
        std::cout << "WorldPlaceGenerator::setWallBoundaryPolygon : " << std::endl <<
          "setBoundaryPolygon for boundary line list manager failed!" << std::endl;

        return false;
    }

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

    if(!boundary_line_list_manager_.reset())
    {
        std::cout << "WorldSplitGenerator::generateWorld : " << std::endl <<
          "reset for boundary_line_list_manager_ failed!" << std::endl;

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
    for(size_t i = 0; i < room_num_; ++i)
    {
        const size_t random_boundary_idx = std::rand() % wall_boundary_polygon_.point_list.size();
        const float random_boundary_start_position = 1.0 * (std::rand() %
            size_t(boundary_line_list_manager_.boundary_line_list_vec_[random_boundary_idx].boundary_length_));

        const float random_width = 1.0 * (std::rand() % 4) + 4;
        const float random_height = 1.0 * (std::rand() % 4) + 4;

        BoundaryLine new_boundary_line;
        new_boundary_line.line_start_position = random_boundary_start_position;
        new_boundary_line.line_end_position = random_boundary_start_position + random_width;
        new_boundary_line.line_height = random_height;

        if(!boundary_line_list_manager_.insertBoundaryLine(random_boundary_idx, new_boundary_line))
        {
            std::cout << "WorldPlaceGenerator::generateRoom : " << std::endl <<
              "insertBoundaryLine for new boundary line failed!" << std::endl;
        }
    }

    boundary_line_list_manager_.outputInfo(0);

    return true;
}

