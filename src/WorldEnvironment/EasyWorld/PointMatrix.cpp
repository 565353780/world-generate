#include "PointMatrix.h"

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

    // point_x_idx_start = std::fmin(point_x_idx_start, x_direction_point_num_ - 1);
    point_x_idx_start = std::fmax(point_x_idx_start, 0);
    // point_x_idx_end = std::fmax(point_x_idx_end, 0);
    point_x_idx_end = std::fmin(point_x_idx_end, x_direction_point_num_ - 1);
    // point_y_idx_start = std::fmin(point_y_idx_start, y_direction_point_num_ - 1);
    point_y_idx_start = std::fmax(point_y_idx_start, 0);
    // point_y_idx_end = std::fmax(point_y_idx_end, 0);
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

    float area_max = -1;

    bool is_x_left_bigger = true;
    bool is_x_right_bigger = true;
    bool is_y_left_bigger = true;
    bool is_y_right_bigger = true;
    size_t x_left_search_length = 0;
    size_t x_right_search_length = 0;
    size_t y_left_search_length = 0;
    size_t y_right_search_length = 0;

    size_t safe_x_left_search_length = 0;
    size_t safe_x_right_search_length = 0;
    size_t safe_y_left_search_length = 0;
    size_t safe_y_right_search_length = 0;

    // case 1 : x direction first
    while(is_x_left_bigger || is_x_right_bigger)
    {
        is_x_left_bigger = false;
        is_x_right_bigger = false;

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
    }

    while(is_y_left_bigger || is_y_right_bigger)
    {
        is_y_left_bigger = false;
        is_y_right_bigger = false;

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

    safe_y_left_search_length = y_left_search_length;
    safe_y_right_search_length = y_right_search_length;

    float current_width = x_left_search_length + x_right_search_length;
    float current_height = y_left_search_length + y_right_search_length;
    float current_area = current_width * current_height;

    if(current_area > area_max)
    {
        area_max = current_area;

        max_free_rect_start_position_x =
          boundary_start_x_ + (max_min_dist_point_x_idx - x_left_search_length) * split_edge_length_;
        max_free_rect_start_position_y =
          boundary_start_y_ + (max_min_dist_point_y_idx - y_left_search_length) * split_edge_length_;
        max_free_rect_width = (x_left_search_length + x_right_search_length) * split_edge_length_;
        max_free_rect_height = (y_left_search_length + y_right_search_length) * split_edge_length_;
    }

    is_x_left_bigger = true;
    is_x_right_bigger = true;
    is_y_left_bigger = true;
    is_y_right_bigger = true;
    x_left_search_length = 0;
    x_right_search_length = 0;
    y_left_search_length = 0;
    y_right_search_length = 0;

    // case 2 : y direction first
    while(is_y_left_bigger || is_y_right_bigger)
    {
        is_y_left_bigger = false;
        is_y_right_bigger = false;

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

    while(is_x_left_bigger || is_x_right_bigger)
    {
        is_x_left_bigger = false;
        is_x_right_bigger = false;

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
    }

    safe_x_left_search_length = x_left_search_length;
    safe_x_right_search_length = x_right_search_length;

    current_width = x_left_search_length + x_right_search_length;
    current_height = y_left_search_length + y_right_search_length;
    current_area = current_width * current_height;

    if(current_area > area_max)
    {
        area_max = current_area;

        max_free_rect_start_position_x =
          boundary_start_x_ + (max_min_dist_point_x_idx - x_left_search_length) * split_edge_length_;
        max_free_rect_start_position_y =
          boundary_start_y_ + (max_min_dist_point_y_idx - y_left_search_length) * split_edge_length_;
        max_free_rect_width = (x_left_search_length + x_right_search_length) * split_edge_length_;
        max_free_rect_height = (y_left_search_length + y_right_search_length) * split_edge_length_;
    }

    is_x_left_bigger = true;
    is_x_right_bigger = true;
    is_y_left_bigger = true;
    is_y_right_bigger = true;
    x_left_search_length = safe_x_left_search_length;
    x_right_search_length = safe_x_right_search_length;
    y_left_search_length = safe_y_left_search_length;
    y_right_search_length = safe_y_right_search_length;

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

    current_width = x_left_search_length + x_right_search_length;
    current_height = y_left_search_length + y_right_search_length;
    current_area = current_width * current_height;

    if(current_area > area_max)
    {
        area_max = current_area;

        max_free_rect_start_position_x =
          boundary_start_x_ + (max_min_dist_point_x_idx - x_left_search_length) * split_edge_length_;
        max_free_rect_start_position_y =
          boundary_start_y_ + (max_min_dist_point_y_idx - y_left_search_length) * split_edge_length_;
        max_free_rect_width = (x_left_search_length + x_right_search_length) * split_edge_length_;
        max_free_rect_height = (y_left_search_length + y_right_search_length) * split_edge_length_;
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

