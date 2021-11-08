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
    current_place_idx_ = 0;

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

    if(boundary_line.line_start_position == boundary_line.line_end_position)
    {
        max_height = 0;
        return true;
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
          "current line length < 0!" << std::endl;

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
    const BoundaryLine &new_boundary_line,
    BoundaryLine &valid_boundary_line)
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

    if(valid_boundary_line.line_start_position > valid_boundary_line.line_end_position)
    {
        std::cout << "BoundaryLineListManager::insertBoundaryLine : " << std::endl <<
          "Input :\n" <<
          "boundary_idx = " << boundary_idx << std::endl <<
          "new_boundary_line = [" << new_boundary_line.line_start_position << "," <<
          new_boundary_line.line_end_position << "]" << std::endl <<
          "valid boundary line width < 0!" << std::endl;

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
    valid_boundary_line.place_idx = current_place_idx_;
    ++current_place_idx_;

    if(!boundary_line_list_vec_[boundary_idx].insertValidBoundaryLine(valid_boundary_line))
    {
        --current_place_idx_;

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

bool BoundaryLineManager::reset()
{
    return true;
}

