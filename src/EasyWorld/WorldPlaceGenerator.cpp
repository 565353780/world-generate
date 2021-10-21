#include "WorldPlaceGenerator.h"

bool BoundaryLine::reset()
{
    place_idx = 0;
    line_start_position = -1;
    line_end_position = -1;
    line_width = -1;
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
      line_start << "\tline_target_size = [" << line_width << "," <<
      line_height << "]" << std::endl <<
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

    if(valid_boundary_line.line_start_position >= valid_boundary_line.line_end_position)
    {
        // std::cout << "BoundaryLineListManager::insertBoundaryLine : " << std::endl <<
        //   "Input :\n" <<
        //   "boundary_idx = " << boundary_idx << std::endl <<
        //   "new_boundary_line = [" << new_boundary_line.line_start_position << "," <<
        //   new_boundary_line.line_end_position << "]" << std::endl <<
        //   "valid boundary line width is zero!" << std::endl;

        return true;
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

bool PointMatrix::reset()
{
    boundary_start_x_ = -1;
    boundary_start_y_ = -1;
    boundary_width_ = -1;
    boundary_height_ = -1;
    is_boundary_position_set_ = false;

    split_edge_length_ = -1;
    is_split_edge_length_set_ = false;

    x_direction_point_num_ = 0;
    y_direction_point_num_ = 0;

    point_matrix_.clear();

    return true;
}

bool PointMatrix::setBoundaryPosition(
    const float &boundary_start_x,
    const float &boundary_start_y,
    const float &boundary_width,
    const float &boundary_height)
{
    boundary_start_x_ = -1;
    boundary_start_y_ = -1;
    boundary_width_ = -1;
    boundary_height_ = -1;
    is_boundary_position_set_ = false;

    if(boundary_width < 0 || boundary_height < 0)
    {
        std::cout << "PointMatrix::setBoundarySize : " << std::endl <<
          "Input :\n" <<
          "\tboundary_start_position = [" << boundary_start_x << "," <<
          boundary_start_y << "]" << std::endl <<
          "\tboundary_size = [" << boundary_width << "," <<
          boundary_height << "]" << std::endl <<
          "boundary size not valid!" << std::endl;

        return false;
    }

    boundary_start_x_ = boundary_start_x;
    boundary_start_y_ = boundary_start_y;
    boundary_width_ = boundary_width;
    boundary_height_ = boundary_height;
    is_boundary_position_set_ = true;

    if(isValid())
    {
        x_direction_point_num_ = size_t(boundary_width_ / split_edge_length_) + 1;
        y_direction_point_num_ = size_t(boundary_height_ / split_edge_length_) + 1;

        point_matrix_.resize(x_direction_point_num_);
        for(std::vector<PointOccupancyState> &point_row : point_matrix_)
        {
            point_row.resize(y_direction_point_num_, PointOccupancyState::PointFree);
        }
    }

    return true;
}

bool PointMatrix::setBoundaryPolygon(
    const EasyPolygon2D &boundary_polygon)
{
    const float &boundary_polygon_x_min = boundary_polygon.rect.x_min;
    const float &boundary_polygon_y_min = boundary_polygon.rect.y_min;
    const float &boundary_polygon_width = boundary_polygon.rect.x_diff;
    const float &boundary_polygon_height = boundary_polygon.rect.y_diff;

    if(!setBoundaryPosition(
          boundary_polygon_x_min,
          boundary_polygon_y_min,
          boundary_polygon_width,
          boundary_polygon_height))
    {
        std::cout << "PointMatrix::setBoundaryPolygon : " << std::endl <<
          "setBoundaryPosition failed!" << std::endl;

        return false;
    }

    return true;
}

bool PointMatrix::setSplitEdgeLength(
    const float &split_edge_length)
{
    split_edge_length_ = -1;
    is_split_edge_length_set_ = false;

    if(split_edge_length == 0)
    {
        std::cout << "PointMatrix::setSplitEdgeLength : " << std::endl <<
          "Input :\n" <<
          "\tsplit_edge_num = " << split_edge_length << std::endl <<
          "split edge num is 0!" << std::endl;

        return false;
    }

    split_edge_length_ = split_edge_length;
    is_split_edge_length_set_ = true;

    if(isValid())
    {
        x_direction_point_num_ = size_t(boundary_width_ / split_edge_length_) + 1;
        y_direction_point_num_ = size_t(boundary_height_ / split_edge_length_) + 1;

        point_matrix_.resize(x_direction_point_num_);
        for(std::vector<PointOccupancyState> &point_row : point_matrix_)
        {
            point_row.resize(y_direction_point_num_, PointOccupancyState::PointFree);
        }
    }

    return true;
}

bool PointMatrix::getPointPosition(
    const size_t &point_x_idx,
    const size_t &point_y_idx,
    EasyPoint2D &point_position)
{
    point_position.setPosition(-1, -1);

    if(!isValid())
    {
        std::cout << "PointMatrix::getPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tpoint_idx = [" << point_x_idx << "," << point_y_idx << "]" << std::endl <<
          "point matrix not valid!" << std::endl;

        return false;
    }

    if(point_x_idx >= x_direction_point_num_ || point_y_idx >= y_direction_point_num_)
    {
        std::cout << "PointMatrix::getPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tpoint_idx = [" << point_x_idx << "," << point_y_idx << "]" << std::endl <<
          "point idx out of range!" << std::endl;

        return false;
    }

    point_position.setPosition(
        boundary_start_x_ + point_x_idx * split_edge_length_,
        boundary_start_y_ + point_y_idx * split_edge_length_);

    return true;
}

bool PointMatrix::setAllPointOccupancyState(
    const PointOccupancyState &point_occupancy_state)
{
    if(!isValid())
    {
        std::cout << "PointMatrix::setAllPointOccupancyState : " << std::endl <<
          "\tpoint_occupancy_state = " << point_occupancy_state << std::endl <<
          "point matrix not valid!" << std::endl;

        return false;
    }

    for(std::vector<PointOccupancyState> &point_row : point_matrix_)
    {
        for(PointOccupancyState &point_state : point_row)
        {
            point_state = point_occupancy_state;
        }
    }

    return true;
}

bool PointMatrix::setPartPointOccupancyState(
    const size_t &point_x_idx_start,
    const size_t &point_x_idx_end,
    const size_t &point_y_idx_start,
    const size_t &point_y_idx_end,
    const PointOccupancyState &point_occupancy_state)
{
    if(!isValid())
    {
        std::cout << "PointMatrix::setAllPointOccupancyState : " << std::endl <<
          "point matrix not valid!" << std::endl;

        return false;
    }

    if(point_x_idx_start >= x_direction_point_num_ ||
        point_x_idx_end < point_x_idx_start ||
        point_y_idx_start >= y_direction_point_num_ ||
        point_y_idx_end < point_y_idx_start)
    {
        std::cout << "PointMatrix::setPartPointOccupancyState : " << std::endl <<
          "Input :\n" <<
          "\tpoint_x_idx_range = [" << point_x_idx_start << "," <<
          point_x_idx_end << "]" << std::endl <<
          "\tpoint_y_idx_range = [" << point_y_idx_start << "," <<
          point_y_idx_end << "]" << std::endl <<
          "\tpoint_occupancy_state = " << point_occupancy_state << std::endl <<
          "point range not valid!" << std::endl;

        return false;
    }

    for(size_t i = point_x_idx_start; i <= point_x_idx_end; ++i)
    {
        std::vector<PointOccupancyState> &point_row = point_matrix_[i];

        for(size_t j = point_y_idx_start; j <= point_y_idx_end; ++j)
        {
            point_row[j] = point_occupancy_state;
        }
    }

    return true;
}

bool PointMatrix::getPointIdxRangeFromRect(
    const float &rect_start_position_x,
    const float &rect_start_position_y,
    const float &rect_width,
    const float &rect_height,
    size_t &point_x_idx_start,
    size_t &point_x_idx_end,
    size_t &point_y_idx_start,
    size_t &point_y_idx_end)
{
    point_x_idx_start = 1;
    point_x_idx_end = 0;
    point_y_idx_start = 1;
    point_y_idx_end = 0;

    if(!isValid())
    {
        std::cout << "PointMatrix::getPointIdxRangeFromRect : " << std::endl <<
          "Input :\n" <<
          "\trect_start_position = [" << rect_start_position_x << "," <<
          rect_start_position_y << "]" << std::endl <<
          "\trect_size = [" << rect_width << "," <<
          rect_height << "]" << std::endl <<
          "point matrix not valid!" << std::endl;

        return false;
    }

    point_x_idx_start = size_t((rect_start_position_x - boundary_start_x_) / split_edge_length_);
    point_x_idx_end = size_t((rect_start_position_x + rect_width - boundary_start_x_) / split_edge_length_) + 1;
    point_y_idx_start = size_t((rect_start_position_y - boundary_start_y_) / split_edge_length_);
    point_y_idx_end = size_t((rect_start_position_y + rect_height - boundary_start_y_) / split_edge_length_) + 1;

    point_x_idx_start = std::fmax(point_x_idx_start, 0);
    point_x_idx_end = std::fmin(point_x_idx_end, x_direction_point_num_ - 1);
    point_y_idx_start = std::fmax(point_y_idx_start, 0);
    point_y_idx_end = std::fmin(point_y_idx_end, y_direction_point_num_ - 1);

    if(point_x_idx_start > point_x_idx_end || point_y_idx_start > point_y_idx_end)
    {
        std::cout << "PointMatrix::getPointIdxRangeFromRect : " << std::endl <<
          "Input :\n" <<
          "\trect_start_position = [" << rect_start_position_x << "," <<
          rect_start_position_y << "]" << std::endl <<
          "\trect_size = [" << rect_width << "," <<
          rect_height << "]" << std::endl <<
          "rect out of range!" << std::endl;

        return false;
    }

    return true;
}

bool PointMatrix::setRectPointOccupancyState(
    const float &rect_start_position_x,
    const float &rect_start_position_y,
    const float &rect_width,
    const float &rect_height,
    const PointOccupancyState &point_occupancy_state)
{
    size_t point_x_idx_start;
    size_t point_x_idx_end;
    size_t point_y_idx_start;
    size_t point_y_idx_end;

    if(!getPointIdxRangeFromRect(
          rect_start_position_x,
          rect_start_position_y,
          rect_width,
          rect_height,
          point_x_idx_start,
          point_x_idx_end,
          point_y_idx_start,
          point_y_idx_end))
    {
        std::cout << "PointMatrix::setRectPointOccupancyState : " << std::endl <<
          "Input :\n" <<
          "\trect_start_position = [" << rect_start_position_x << "," <<
          rect_start_position_y << "]" << std::endl <<
          "\trect_size = [" << rect_width << "," <<
          rect_height << "]" << std::endl <<
          "\tpoint_occupancy_state = " << point_occupancy_state << std::endl <<
          "getPointIdxRangeFromRect failed!" << std::endl;

        return false;
    }

    if(!setPartPointOccupancyState(
          point_x_idx_start,
          point_x_idx_end,
          point_y_idx_start,
          point_y_idx_end,
          point_occupancy_state))
    {
        std::cout << "PointMatrix::setRectPointOccupancyState : " << std::endl <<
          "Input :\n" <<
          "\trect_start_position = [" << rect_start_position_x << "," <<
          rect_start_position_y << "]" << std::endl <<
          "\trect_size = [" << rect_width << "," <<
          rect_height << "]" << std::endl <<
          "\tpoint_occupancy_state = " << point_occupancy_state << std::endl <<
          "setPartPointOccupancyState failed!" << std::endl;

        return false;
    }

    return true;
}

bool PointMatrix::getMaxMinDistPointToPolygonVec(
    const std::vector<EasyPolygon2D> &polygon_vec,
    size_t &max_min_dist_point_x_idx,
    size_t &max_min_dist_point_y_idx)
{
    max_min_dist_point_x_idx = x_direction_point_num_;
    max_min_dist_point_y_idx = y_direction_point_num_;

    if(polygon_vec.size() == 0)
    {
        std::cout << "PointMatrix::getMaxMinDistPointToPolygonVec : " << std::endl <<
          "polygon_vec is empty!" << std::endl;

        return false;
    }

    float max_min_dist = 0;

    EasyPoint2D current_point_in_matrix;

    for(size_t i = 0; i < x_direction_point_num_; ++i)
    {
        current_point_in_matrix.x = boundary_start_x_ + i * split_edge_length_;

        const std::vector<PointOccupancyState> &point_row = point_matrix_[i];

        for(size_t j = 0; j < y_direction_point_num_; ++j)
        {
            current_point_in_matrix.y = boundary_start_y_ + j * split_edge_length_;

            const PointOccupancyState &point_state = point_row[j];

            if(point_state == PointOccupancyState::PointUsed)
            {
                continue;
            }

            float current_min_dist_to_polygon = std::numeric_limits<float>::max();

            for(const EasyPolygon2D &polygon : polygon_vec)
            {
                const float current_dist_to_polygon =
                  EasyComputation::getPointDistToRect(current_point_in_matrix, polygon.rect);

                if(current_dist_to_polygon < current_min_dist_to_polygon)
                {
                    current_min_dist_to_polygon = current_dist_to_polygon;
                }
            }

            if(current_min_dist_to_polygon > max_min_dist)
            {
                max_min_dist = current_min_dist_to_polygon;
                max_min_dist_point_x_idx = i;
                max_min_dist_point_y_idx = j;
            }
        }
    }

    if(max_min_dist_point_x_idx >= x_direction_point_num_ ||
        max_min_dist_point_y_idx >= y_direction_point_num_)
    {
        // std::cout << "PointMatrix::getMaxMinDistPointToPolygonVec : " << std::endl <<
        //   "no point is free!" << std::endl;

        return false;
    }

    return true;
}

bool PointMatrix::getMaxFreeRect(
    const std::vector<EasyPolygon2D> &polygon_vec,
    float &max_free_rect_start_position_x,
    float &max_free_rect_start_position_y,
    float &max_free_rect_width,
    float &max_free_rect_height)
{
    size_t max_min_dist_point_x_idx;
    size_t max_min_dist_point_y_idx;

    if(!getMaxMinDistPointToPolygonVec(
          polygon_vec,
          max_min_dist_point_x_idx,
          max_min_dist_point_y_idx))
    {
        // std::cout << "PointMatrix::getMaxFreeRect : " << std::endl <<
        //   "getMaxMinDistPointToPolygonVec failed!" << std::endl;

        return false;
    }

    bool is_x_left_bigger = true;
    bool is_x_right_bigger = true;
    bool is_y_left_bigger = true;
    bool is_y_right_bigger = true;
    size_t x_left_search_length = 0;
    size_t x_right_search_length = 0;
    size_t y_left_search_length = 0;
    size_t y_right_search_length = 0;
    while(is_x_left_bigger || is_x_right_bigger || is_y_left_bigger || is_y_right_bigger)
    {
        is_x_left_bigger = false;
        is_x_right_bigger = false;
        is_y_left_bigger = false;
        is_y_right_bigger = false;

        if(max_min_dist_point_x_idx - x_left_search_length > 0)
        {
            bool current_bigger_success = true;
            size_t next_x_left_idx = max_min_dist_point_x_idx - x_left_search_length - 1;
            for(size_t j = max_min_dist_point_y_idx - y_left_search_length;
                j <= max_min_dist_point_y_idx + y_right_search_length; ++j)
            {
                if(point_matrix_[next_x_left_idx][j] == PointOccupancyState::PointUsed)
                {
                    current_bigger_success = false;

                    break;
                }
            }

            if(current_bigger_success)
            {
                ++x_left_search_length;
                is_x_left_bigger = true;
            }
        }

        if(max_min_dist_point_y_idx - y_left_search_length > 0)
        {
            bool current_bigger_success = true;
            size_t next_y_left_idx = max_min_dist_point_y_idx - y_left_search_length - 1;
            for(size_t i = max_min_dist_point_x_idx - x_left_search_length;
                i <= max_min_dist_point_x_idx + x_right_search_length; ++i)
            {
                if(point_matrix_[i][next_y_left_idx] == PointOccupancyState::PointUsed)
                {
                    current_bigger_success = false;

                    break;
                }
            }

            if(current_bigger_success)
            {
                ++y_left_search_length;
                is_y_left_bigger = true;
            }
        }

        if(max_min_dist_point_x_idx + x_right_search_length < x_direction_point_num_ - 1)
        {
            bool current_bigger_success = true;
            size_t next_x_right_idx = max_min_dist_point_x_idx + x_right_search_length + 1;
            for(size_t j = max_min_dist_point_y_idx - y_left_search_length;
                j <= max_min_dist_point_y_idx + y_right_search_length; ++j)
            {
                if(point_matrix_[next_x_right_idx][j] == PointOccupancyState::PointUsed)
                {
                    current_bigger_success = false;

                    break;
                }
            }

            if(current_bigger_success)
            {
                ++x_right_search_length;
                is_x_right_bigger = true;
            }
        }

        if(max_min_dist_point_y_idx + y_right_search_length < y_direction_point_num_ - 1)
        {
            bool current_bigger_success = true;
            size_t next_y_right_idx = max_min_dist_point_y_idx + y_right_search_length + 1;
            for(size_t i = max_min_dist_point_x_idx - x_left_search_length;
                i <= max_min_dist_point_x_idx + x_right_search_length; ++i)
            {
                if(point_matrix_[i][next_y_right_idx] == PointOccupancyState::PointUsed)
                {
                    current_bigger_success = false;

                    break;
                }
            }

            if(current_bigger_success)
            {
                ++y_right_search_length;
                is_y_right_bigger = true;
            }
        }
    }


    max_free_rect_start_position_x =
      boundary_start_x_ + (max_min_dist_point_x_idx - x_left_search_length) * split_edge_length_;
    max_free_rect_start_position_y =
      boundary_start_y_ + (max_min_dist_point_y_idx - y_left_search_length) * split_edge_length_;
    max_free_rect_width = (x_left_search_length + x_right_search_length) * split_edge_length_;
    max_free_rect_height = (y_left_search_length + y_right_search_length) * split_edge_length_;

    return true;
}

bool PointMatrix::isValid()
{
    if(!is_boundary_position_set_)
    {
        // std::cout << "PointMatrix::isValid : " << std::endl <<
        //   "boundary position not valid!" << std::endl;

        return false;
    }

    if(!is_split_edge_length_set_)
    {
        // std::cout << "PointMatrix::isValid : " << std::endl <<
        //   "split edge length not valid!" << std::endl;

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

    if(!point_matrix_.reset())
    {
        std::cout << "WorldPlaceGenerator::reset : " <<
          "reset for point_matrix_ failed!" << std::endl;

        return false;
    }

    wall_boundary_polygon_.point_list.clear();
    is_wall_boundary_polygon_set_ = false;

    free_room_error_max_ = 1;

    current_new_room_id_ = 0;

    team_x_direction_person_num_ = 0;
    team_y_direction_person_num_ = 0;
    team_dist_ = -1;
    person_edge_ = -1;

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

    point_matrix_.setSplitEdgeLength(free_room_error_max_);

    if(!point_matrix_.setBoundaryPolygon(wall_boundary_polygon_))
    {
        std::cout << "WorldPlaceGenerator::setWallBoundaryPolygon : " << std::endl <<
          "setBoundaryPolygon for point matrix failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldPlaceGenerator::generateWorld()
{
    if(!isReadyToGenerate())
    {
        std::cout << "WorldPlaceGenerator::generateWorld : " << std::endl <<
          "wall_boundary_polygon not set!" << std::endl;

        return false;
    }

    if(!world_controller_.reset())
    {
        std::cout << "WorldPlaceGenerator::generateWorld : " << std::endl <<
          "reset for world_controller_ failed!" << std::endl;

        return false;
    }

    current_new_room_id_ = 0;

    if(!boundary_line_list_manager_.reset())
    {
        std::cout << "WorldPlaceGenerator::generateWorld : " << std::endl <<
          "reset for boundary_line_list_manager_ failed!" << std::endl;

        return false;
    }

    if(!generateWall())
    {
        std::cout << "WorldPlaceGenerator::generateWorld : " << std::endl <<
          "generateWall failed!" << std::endl;

        return false;
    }

    if(!generateRoom())
    {
        std::cout << "WorldPlaceGenerator::generateWorld : " << std::endl <<
          "generateRoom failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldPlaceGenerator::placeWallRoomContainer(
    const size_t &boundary_idx,
    const float &roomcontainer_start_position,
    const float &roomcontainer_width,
    const float &roomcontainer_height)
{
    const float person_edge = 2;

    BoundaryLine new_boundary_line;
    new_boundary_line.line_start_position = roomcontainer_start_position;
    new_boundary_line.line_end_position = roomcontainer_start_position + roomcontainer_width;
    new_boundary_line.line_width = roomcontainer_width;
    new_boundary_line.line_height = roomcontainer_height;

    BoundaryLine valid_boundary_line;

    if(!boundary_line_list_manager_.insertBoundaryLine(
          boundary_idx,
          new_boundary_line,
          valid_boundary_line))
    {
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "insertBoundaryLine for new boundary line failed!" << std::endl;

        return false;
    }

    if(valid_boundary_line.line_real_height <= 0)
    {
        // std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
        //   "Input :\n" <<
        //   "\t boundary_idx = " << boundary_idx << std::endl <<
        //   "\t boundary_start_position = " << boundary_start_position << std::endl <<
        //   "\t roomcontainer_size = [" << roomcontainer_width << "," <<
        //   roomcontainer_height << "]" << std::endl <<
        //   "valid boundary line real height not valid!" << std::endl;

        return false;
    }

    const float valid_roomcontainer_start_position = valid_boundary_line.line_start_position;
    const float valid_roomcontainer_width = valid_boundary_line.line_end_position - valid_boundary_line.line_start_position;
    const float valid_roomcontainer_height = valid_boundary_line.line_real_height;

    EasyAxis2D axis;
    axis.setXDirection(1, 0);
    axis.setCenter(valid_roomcontainer_start_position, 0);

    if(valid_roomcontainer_width == 0 || valid_roomcontainer_height == 0)
    {
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "valid roomcontainer size not valid!" << std::endl;

        return false;
    }

    size_t room_num = size_t(1.0 * valid_roomcontainer_width / valid_roomcontainer_height);
    if(room_num == 0)
    {
        room_num = 1;
    }

    if(!world_controller_.createWallRoomContainerForWall(
          0,
          NodeType::OuterWall,
          boundary_idx,
          valid_roomcontainer_width,
          valid_roomcontainer_height,
          axis,
          room_num))
    {
        std::cout << "valid roomcontainer size = " << valid_roomcontainer_width << "," <<
          valid_roomcontainer_height << std::endl;
        std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\tboundary_idx = " << boundary_idx << std::endl <<
          "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
          "\troomcontainer_size = [" << roomcontainer_width << "," <<
          roomcontainer_height << "]" << std::endl <<
          "createWallRoomContainerForWall failed!" << std::endl;

        return false;
    }

    const float room_width = 1.0 * valid_roomcontainer_width / room_num;
    const float room_height = valid_roomcontainer_height;

    const float team_dist = 1.0 * person_edge;

    for(size_t i = 0; i < room_num; ++i)
    {
        size_t person_x_direction_num = 0;
        size_t person_y_direction_num = 0;

        if(room_width >= team_dist)
        {
            person_x_direction_num = size_t((room_width - 0.5 * team_dist) / person_edge);

            if(person_x_direction_num == 0)
            {
                person_x_direction_num = 1;
            }
        }
        if(room_height >= team_dist)
        {
            person_y_direction_num = size_t((room_height - 0.5 * team_dist) / person_edge);

            if(person_y_direction_num == 0)
            {
                person_y_direction_num = 1;
            }
        }

        if(person_x_direction_num == 0 || person_y_direction_num == 0)
        {
            ++current_new_room_id_;

            return true;
        }

        const float team_width = 1.0 * person_x_direction_num * person_edge;
        const float team_height = 1.0 * person_y_direction_num * person_edge;

        const float team_center_x = (room_width - team_width) / 2.0;
        const float team_center_y = (room_height - team_height) / 2.0;

        const bool is_face_horizontal = (std::rand() % 2) == 1;

        axis.setCenter(team_center_x, team_center_y);

        if(!world_controller_.createTeamForRoom(
              current_new_room_id_,
              NodeType::WallRoom,
              team_width,
              team_height,
              axis,
              person_x_direction_num,
              person_y_direction_num,
              false))
        {
            std::cout << "WorldPlaceGenerator::placeWallRoomContainer : " << std::endl <<
              "Input :\n" <<
              "\tboundary_idx = " << boundary_idx << std::endl <<
              "\troomcontainer_start_position = " << roomcontainer_start_position << std::endl <<
              "\troomcontainer_size = [" << roomcontainer_width << "," <<
              roomcontainer_height << "]" << std::endl <<
              "createTeamForRoom failed!" << std::endl;

            return false;
        }

        ++current_new_room_id_;
    }

    return true;
}

bool WorldPlaceGenerator::generateFreeRoomContainer(
    const size_t &team_x_direction_person_num,
    const size_t &team_y_direction_person_num,
    const float &team_dist,
    const float &person_edge)
{
    if(!point_matrix_.setAllPointOccupancyState(PointOccupancyState::PointFree))
    {
        std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
          team_y_direction_person_num << "]" << std::endl <<
          "\tteam_dist = " << team_dist << std::endl <<
          "\tperson_edge = " << person_edge << std::endl <<
          "setAllPointOccupancyState failed!" << std::endl;

        return false;
    }

    EasyNode* wall_node = world_controller_.findNode(0, NodeType::OuterWall);

    if(wall_node == nullptr)
    {
        std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
          team_y_direction_person_num << "]" << std::endl <<
          "\tteam_dist = " << team_dist << std::endl <<
          "\tperson_edge = " << person_edge << std::endl <<
          "find wall node failed!" << std::endl;

        return false;
    }

    std::vector<EasyPolygon2D> polygon_vec_in_wall_node;

    std::vector<EasyNode*> roomcontainer_node_vec;
    world_controller_.getRoomContainerNodeVec(roomcontainer_node_vec);

    for(EasyNode* roomcontainer_node : roomcontainer_node_vec)
    {
        EasyNode* roomcontainer_space_node = roomcontainer_node->findChild(0, NodeType::Space);

        if(roomcontainer_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &roomcontainer_space_polygon =
          roomcontainer_space_node->getBoundaryPolygon();

        EasyPolygon2D roomcontainer_polygon_in_wall_node;

        for(const EasyPoint2D &roomcontainer_boundary_point : roomcontainer_space_polygon.point_list)
        {
            EasyPoint2D roomcontainer_boundary_point_in_world;

            if(!roomcontainer_space_node->getPointInWorld(
                  roomcontainer_boundary_point,
                  roomcontainer_boundary_point_in_world))
            {
                std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
                  "Input :\n" <<
                  "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
                  team_y_direction_person_num << "]" << std::endl <<
                  "\tteam_dist = " << team_dist << std::endl <<
                  "\tperson_edge = " << person_edge << std::endl <<
                  "getPointInWorld failed!" << std::endl;

                return false;
            }

            EasyPoint2D roomcontainer_boundary_point_in_wall_node;

            if(!wall_node->getPointInNode(
                  roomcontainer_boundary_point_in_world,
                  roomcontainer_boundary_point_in_wall_node))
            {
                std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
                  "Input :\n" <<
                  "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
                  team_y_direction_person_num << "]" << std::endl <<
                  "\tteam_dist = " << team_dist << std::endl <<
                  "\tperson_edge = " << person_edge << std::endl <<
                  "getPointInNode failed!" << std::endl;

                return false;
            }

            roomcontainer_polygon_in_wall_node.addPoint(roomcontainer_boundary_point_in_wall_node);
        }

        polygon_vec_in_wall_node.emplace_back(roomcontainer_polygon_in_wall_node);
    }

    for(const EasyPolygon2D &polygon_in_wall_node : polygon_vec_in_wall_node)
    {
        const float &boundary_polygon_x_min = polygon_in_wall_node.rect.x_min;
        const float &boundary_polygon_y_min = polygon_in_wall_node.rect.y_min;
        const float &boundary_polygon_width = polygon_in_wall_node.rect.x_diff;
        const float &boundary_polygon_height = polygon_in_wall_node.rect.y_diff;

        if(!point_matrix_.setRectPointOccupancyState(
              boundary_polygon_x_min,
              boundary_polygon_y_min,
              boundary_polygon_width,
              boundary_polygon_height,
              PointOccupancyState::PointUsed))
        {
            std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
              "Input :\n" <<
              "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
              team_y_direction_person_num << "]" << std::endl <<
              "\tteam_dist = " << team_dist << std::endl <<
              "\tperson_edge = " << person_edge << std::endl <<
              "setRectPointOccupancyState failed!" << std::endl;

            return false;
        }
    }

    for(size_t i = 0; i < wall_boundary_polygon_.point_list.size(); ++i)
    {
        const EasyPoint2D &current_point = wall_boundary_polygon_.point_list[i];
        const EasyPoint2D &next_point = wall_boundary_polygon_.point_list[
          (i + 1) % wall_boundary_polygon_.point_list.size()];

        EasyPolygon2D new_boundary_line_polygon;
        new_boundary_line_polygon.addPoint(current_point);
        new_boundary_line_polygon.addPoint(next_point);

        polygon_vec_in_wall_node.emplace_back(new_boundary_line_polygon);
    }

    size_t current_freeroom_id_start = 0;
    bool is_new_roomcontainer_valid = true;

    while(is_new_roomcontainer_valid)
    {
        is_new_roomcontainer_valid = false;

        float max_free_roomcontainer_start_position_x;
        float max_free_roomcontainer_start_position_y;
        float max_free_roomcontainer_width;
        float max_free_roomcontainer_height;

        if(!point_matrix_.getMaxFreeRect(
              polygon_vec_in_wall_node,
              max_free_roomcontainer_start_position_x,
              max_free_roomcontainer_start_position_y,
              max_free_roomcontainer_width,
              max_free_roomcontainer_height))
        {
            // std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
            //   "Input :\n" <<
            //   "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
            //   team_y_direction_person_num << "]" << std::endl <<
            //   "\tteam_dist = " << team_dist << std::endl <<
            //   "\tperson_edge = " << person_edge << std::endl <<
            //   "getMaxFreeRect failed!" << std::endl;

            continue;
        }

        size_t x_direction_room_num = 
          max_free_roomcontainer_width / (team_x_direction_person_num * person_edge + team_dist);

        size_t y_direction_room_num = 
          max_free_roomcontainer_height / (team_y_direction_person_num * person_edge + team_dist);

        if(x_direction_room_num == 0)
        {
            x_direction_room_num = 1;
        }
        if(y_direction_room_num == 0)
        {
            y_direction_room_num = 1;
        }

        const float room_width = max_free_roomcontainer_width / x_direction_room_num;
        const float room_height = max_free_roomcontainer_height / y_direction_room_num;

        size_t person_x_direction_num = 0;
        size_t person_y_direction_num = 0;

        if(room_width >= team_dist)
        {
            person_x_direction_num = size_t((room_width - team_dist) / person_edge);

            if(person_x_direction_num == 0)
            {
                ++person_x_direction_num;
            }
        }
        if(room_height >= team_dist)
        {
            person_y_direction_num = size_t((room_height - team_dist) / person_edge);

            if(person_y_direction_num == 0)
            {
                ++person_y_direction_num;
            }
        }

        if(person_x_direction_num < 2 || person_y_direction_num < 2)
        {
            continue;
        }

        is_new_roomcontainer_valid = true;

        const bool is_face_horizontal = (std::rand() % 2) == 1;

        const float team_width = 1.0 * person_x_direction_num * person_edge;
        const float team_height = 1.0 * person_y_direction_num * person_edge;

        const float team_center_x = (room_width - team_width) / 2.0;
        const float team_center_y = (room_height - team_height) / 2.0;

        EasyAxis2D team_axis;
        team_axis.setXDirection(1, 0);
        team_axis.setCenter(team_center_x, team_center_y);

        EasyAxis2D room_axis;
        room_axis.setXDirection(1, 0);

        for(size_t i = 0; i < x_direction_room_num; ++i)
        {
            for(size_t j = 0; j < y_direction_room_num; ++j)
            {
                room_axis.setCenter(
                    max_free_roomcontainer_start_position_x + i * room_width,
                    max_free_roomcontainer_start_position_y + j * room_height);

                world_controller_.createFreeRoomContainerForWall(
                    0,
                    NodeType::OuterWall,
                    0,
                    room_width,
                    room_height,
                    room_axis,
                    1);

                world_controller_.createTeamForRoom(
                    current_freeroom_id_start,
                    NodeType::FreeRoom,
                    team_width,
                    team_height,
                    team_axis,
                    person_x_direction_num,
                    person_y_direction_num,
                    true);

                ++current_freeroom_id_start;
            }
        }

        EasyPolygon2D new_room_polygon;
        new_room_polygon.addPoint(
            max_free_roomcontainer_start_position_x,
            max_free_roomcontainer_start_position_y);
        new_room_polygon.addPoint(
            max_free_roomcontainer_start_position_x + max_free_roomcontainer_width,
            max_free_roomcontainer_start_position_y);
        new_room_polygon.addPoint(
            max_free_roomcontainer_start_position_x + max_free_roomcontainer_width,
            max_free_roomcontainer_start_position_y + max_free_roomcontainer_height);
        new_room_polygon.addPoint(
            max_free_roomcontainer_start_position_x,
            max_free_roomcontainer_start_position_y + max_free_roomcontainer_height);
        new_room_polygon.setAntiClockWise();
        polygon_vec_in_wall_node.emplace_back(new_room_polygon);

        if(!point_matrix_.setRectPointOccupancyState(
              max_free_roomcontainer_start_position_x,
              max_free_roomcontainer_start_position_y,
              max_free_roomcontainer_start_position_x + max_free_roomcontainer_width,
              max_free_roomcontainer_start_position_y + max_free_roomcontainer_height,
              PointOccupancyState::PointUsed))
        {
            std::cout << "WorldPlaceGenerator::generateFreeRoomContainer : " << std::endl <<
              "Input :\n" <<
              "\tteam_person_num_size = [" << team_x_direction_person_num << "," <<
              team_y_direction_person_num << "]" << std::endl <<
              "\tteam_dist = " << team_dist << std::endl <<
              "\tperson_edge = " << person_edge << std::endl <<
              "setRectPointOccupancyState failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool WorldPlaceGenerator::isReadyToGenerate()
{
    if(is_wall_boundary_polygon_set_)
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
    const size_t roomcontainer_num = 3;

    const float roomcontainer_width_min = 6;
    const float roomcontainer_width_max = 24;
    const float roomcontainer_height_min = 6;
    const float roomcontainer_height_max = 8;

    for(size_t i = 0; i < roomcontainer_num; ++i)
    {
        const size_t random_boundary_idx = std::rand() % wall_boundary_polygon_.point_list.size();
        const float random_boundary_start_position = 1.0 * (std::rand() %
            size_t(boundary_line_list_manager_.boundary_line_list_vec_[random_boundary_idx].boundary_length_));

        const float random_width =
          1.0 * (std::rand() % size_t(roomcontainer_width_max - roomcontainer_width_min)) + roomcontainer_width_min;
        const float random_height =
          1.0 * (std::rand() % size_t(roomcontainer_height_max - roomcontainer_height_min)) + roomcontainer_height_min;

        if(!placeWallRoomContainer(
              random_boundary_idx,
              random_boundary_start_position,
              random_width,
              random_height))
        {
            continue;
        }
    }

    if(!generateFreeRoomContainer(
          team_x_direction_person_num_,
          team_y_direction_person_num_,
          team_dist_,
          person_edge_))
    {
        std::cout << "WorldPlaceGenerator::generateRoom : " << std::endl <<
          "generateFreeRoomContainer failed!" << std::endl;

        return false;
    }

    return true;
}

