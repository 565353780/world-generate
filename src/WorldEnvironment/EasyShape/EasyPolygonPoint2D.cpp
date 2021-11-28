#include "EasyPolygonPoint2D.h"

bool EasyPolygonPoint2D::reset()
{
    is_valid = false;

    param_on_polygon = -1;

    line_idx = 0;
    param_on_line = -1;

    length = -1;

    position.setPosition(0, 0);

    right_direction.setPosition(0, 0);
    left_direction.setPosition(0, 0);

    return true;
}

bool EasyPolygonPoint2D::updateByPolygonParam(
    const EasyPolygon2D& polygon,
    const float& point_param_on_polygon)
{
    reset();

    if(polygon.point_list.size() == 0)
    {
        std::cout << "EasyPolygonPoint2D::updateByPolygonParam :\n" <<
          "Input :\n" <<
          "\t point_param_on_polygon = " << point_param_on_polygon << std::endl <<
          "polygon is empty!\n";

        return false;
    }

    if(point_param_on_polygon < 0 || point_param_on_polygon > 1)
    {
        std::cout << "EasyPolygonPoint2D::updateByPolygonParam :\n" <<
          "Input :\n" <<
          "\t point_param_on_polygon = " << point_param_on_polygon << std::endl <<
          "point_param_on_polygon out of range!\n";

        return false;
    }

    if(polygon.perimeter == 0)
    {
        param_on_polygon = point_param_on_polygon;

        line_idx = 0;
        param_on_line = 0;

        length = 0;

        position = polygon.point_list[0];

        right_direction.setPosition(1, 0);
        left_direction.setPosition(0, 1);

        is_valid = true;

        return true;
    }

    param_on_polygon = point_param_on_polygon;

    length = point_param_on_polygon * polygon.perimeter;

    line_idx = 0;
    for(const float& polygon_point_length : polygon.point_length_vec)
    {
        if(length < polygon_point_length)
        {
            break;
        }

        ++line_idx;
    }
    if(line_idx == 0)
    {
        std::cout << "EasyPolygonPoint2D::updateByPolygonParam :\n" <<
          "Input :\n" <<
          "\t point_param_on_polygon = " << point_param_on_polygon << std::endl <<
          "line_idx is not found!\n";

        return false;
    }
    --line_idx;

    const float point_length_remain = length - polygon.point_length_vec[line_idx];
    const float current_line_length = polygon.point_length_vec[line_idx + 1] - polygon.point_length_vec[line_idx];
    param_on_line = point_length_remain / current_line_length;

    const EasyPoint2D& current_point = polygon.point_list[line_idx];
    const EasyPoint2D& next_point = polygon.point_list[(line_idx + 1) % polygon.point_list.size()];

    const float unit_line_x_diff = (next_point.x - current_point.x) / current_line_length;
    const float unit_line_y_diff = (next_point.y - current_point.y) / current_line_length;

    position.setPosition(
        current_point.x + unit_line_x_diff * param_on_line * current_line_length,
        current_point.y + unit_line_y_diff * param_on_line * current_line_length);

    if(param_on_line == 0)
    {
        right_direction.setPosition(unit_line_x_diff, unit_line_y_diff);

        const size_t prev_point_idx = (line_idx - 1 + polygon.point_list.size()) % polygon.point_list.size();
        const float prev_line_length = polygon.point_length_vec[prev_point_idx + 1] - polygon.point_length_vec[prev_point_idx];
        const EasyPoint2D& prev_point = polygon.point_list[prev_point_idx];

        const float unit_prev_line_x_diff = (current_point.x - prev_point.x) / prev_line_length;
        const float unit_prev_line_y_diff = (current_point.y - prev_point.y) / prev_line_length;

        left_direction.setPosition(unit_prev_line_x_diff, unit_prev_line_y_diff);
    }
    else if(param_on_line == 1)
    {
        left_direction.setPosition(unit_line_x_diff, unit_line_y_diff);

        const size_t next_next_point_idx = (line_idx + 2) % polygon.point_list.size();
        const float next_line_length = polygon.point_length_vec[next_next_point_idx + 1] - polygon.point_length_vec[next_next_point_idx];
        const EasyPoint2D& next_next_point = polygon.point_list[next_next_point_idx];

        const float unit_next_line_x_diff = (next_next_point.x - next_point.x) / next_line_length;
        const float unit_next_line_y_diff = (next_next_point.y - next_point.y) / next_line_length;

        right_direction.setPosition(unit_next_line_x_diff, unit_next_line_y_diff);
    }
    else
    {
        right_direction.setPosition(unit_line_x_diff, unit_line_y_diff);
        left_direction.setPosition(unit_line_x_diff, unit_line_y_diff);
    }

    is_valid = true;

    return true;
}

bool EasyPolygonPoint2D::updateByLineParam(
    const EasyPolygon2D& polygon,
    const size_t& point_line_idx,
    const float& point_param_on_line)
{
    if(polygon.point_list.size() == 0)
    {
        std::cout << "EasyPolygonPoint2D::updateByLineParam :\n" <<
          "Input :\n" <<
          "\t point_line_idx = " << point_line_idx << std::endl <<
          "\t point_param_on_line = " << point_param_on_line << std::endl <<
          "polygon is empty!\n";

        return false;
    }

    if(point_line_idx >= polygon.point_list.size())
    {
        std::cout << "EasyPolygonPoint2D::updateByLineParam :\n" <<
          "Input :\n" <<
          "\t point_line_idx = " << point_line_idx << std::endl <<
          "\t point_param_on_line = " << point_param_on_line << std::endl <<
          "point_line_idx out of range!\n";

        return false;
    }

    if(point_param_on_line < 0 || point_param_on_line > 1)
    {
        std::cout << "EasyPolygonPoint2D::updateByLineParam :\n" <<
          "Input :\n" <<
          "\t point_line_idx = " << point_line_idx << std::endl <<
          "\t point_param_on_line = " << point_param_on_line << std::endl <<
          "point_param_on_line out of range!\n";

        return false;
    }

    const float current_line_length = polygon.point_length_vec[point_line_idx + 1] - polygon.point_length_vec[point_line_idx];

    const float point_length = polygon.point_length_vec[point_line_idx] + current_line_length * point_param_on_line;

    if(polygon.perimeter == 0)
    {
        return updateByPolygonParam(polygon, 0);
    }

    const float point_param_on_polygon = point_length / polygon.perimeter;

    return updateByPolygonParam(polygon, point_param_on_polygon);
}

bool EasyPolygonPoint2D::updateByLength(
    const EasyPolygon2D& polygon,
    const float& point_length)
{
    if(polygon.point_list.size() == 0)
    {
        std::cout << "EasyPolygonPoint2D::updateByLength :\n" <<
          "Input :\n" <<
          "\t point_length = " << point_length << std::endl <<
          "polygon is empty!\n";

        return false;
    }

    if(point_length > polygon.perimeter)
    {
        std::cout << "EasyPolygonPoint2D::updateByLength :\n" <<
          "Input :\n" <<
          "\t point_length = " << point_length << std::endl <<
          "point_length out of range!\n";

        return false;
    }

    if(polygon.perimeter == 0)
    {
        return updateByPolygonParam(polygon, 0);
    }

    const float point_param_on_polygon = point_length / polygon.perimeter;

    return updateByPolygonParam(polygon, point_param_on_polygon);
}

bool EasyPolygonPoint2D::updateByPosition(
    const EasyPolygon2D& polygon,
    const EasyPoint2D& point_position)
{
    if(polygon.point_list.size() == 0)
    {
        std::cout << "EasyPolygonPoint2D::updateByPosition :\n" <<
          "Input :\n" <<
          "\t point_position = [" << point_position.x << "," <<
          point_position.y << "]\n" <<
          "polygon is empty!\n";

        return false;
    }

    if(polygon.perimeter == 0)
    {
        return updateByPolygonParam(polygon, 0);
    }

    float min_dist2_to_polygon_line = std::numeric_limits<float>::max();
    size_t min_dist_line_idx;

    EasyPoint2D nearest_point_on_line;

    for(size_t i = 0; i < polygon.point_list.size(); ++i)
    {
        const EasyPoint2D &current_point = polygon.point_list[i];
        const EasyPoint2D &next_point = polygon.point_list[(i + 1) % polygon.point_list.size()];

        EasyLine2D current_line;
        current_line.setPosition(current_point, next_point);

        const EasyPoint2D current_nearest_point_on_line = EasyComputation::getNearestPointOnLine(
            current_line, point_position);

        const float current_dist2_to_line = EasyComputation::pointDist2(current_nearest_point_on_line, point_position);

        if(current_dist2_to_line < min_dist2_to_polygon_line)
        {
            min_dist2_to_polygon_line = current_dist2_to_line;
            min_dist_line_idx = i;
            nearest_point_on_line = current_nearest_point_on_line;
        }
    }

    const float point_length =
      polygon.point_length_vec[min_dist_line_idx] +
      EasyComputation::pointDist(nearest_point_on_line, polygon.point_list[min_dist_line_idx]);

    const float point_param_on_polygon = point_length / polygon.perimeter;

    std::cout <<
      "point_length = " << point_length << std::endl <<
      "point_param_on_polygon = " << point_param_on_polygon << std::endl;

    return updateByPolygonParam(polygon, point_param_on_polygon);
}

