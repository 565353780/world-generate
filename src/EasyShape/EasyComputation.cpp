#include "EasyComputation.h"

float EasyComputation::dot(
    const float &x_1,
    const float &y_1,
    const float &x_2,
    const float &y_2)
{
    return x_1 * x_2 + y_1 * y_2;
}

float EasyComputation::dot(
    const EasyLine2D &line_1,
    const EasyLine2D &line_2)
{
    return dot(line_1.x_diff, line_1.y_diff, line_2.x_diff, line_2.y_diff);
}

float EasyComputation::cross(
    const float &x_1,
    const float &y_1,
    const float &x_2,
    const float &y_2)
{
    return x_1 * y_2 - x_2 * y_1;
}

float EasyComputation::cross(
    const EasyLine2D &line_1,
    const EasyLine2D &line_2)
{
    return cross(line_1.x_diff, line_1.y_diff, line_2.x_diff, line_2.y_diff);
}

float EasyComputation::pointDist2(
    const EasyPoint2D &point_1,
    const EasyPoint2D &point_2)
{
    float dist_2 =
      (point_1.x - point_2.x) * (point_1.x - point_2.x) +
      (point_1.y - point_2.y) * (point_1.y - point_2.y);

    return dist_2;
}

float EasyComputation::pointDist(
    const EasyPoint2D &point_1,
    const EasyPoint2D &point_2)
{
    return sqrt(pointDist2(point_1, point_2));
}

float EasyComputation::getPointDistToRect(
    const EasyPoint2D &point,
    const EasyRect2D &rect)
{
    if(isPointInRect(point, rect))
    {
        return 0;
    }

    float point_dist2_to_rect = 0;

    if(point.x < rect.x_min)
    {
        point_dist2_to_rect += (point.x - rect.x_min) * (point.x - rect.x_min);
    }
    else if(point.x > rect.x_max)
    {
        point_dist2_to_rect += (point.x - rect.x_max) * (point.x - rect.x_max);
    }
    else
    {
        float point_dist_min_to_rect =
          std::fmin(fabs(point.y - rect.y_min), fabs(point.y - rect.y_max));

        return point_dist_min_to_rect;
    }

    if(point.y < rect.y_min)
    {
        point_dist2_to_rect += (point.y - rect.y_min) * (point.y - rect.y_min);
    }
    else if(point.y > rect.y_max)
    {
        point_dist2_to_rect += (point.y - rect.y_max) * (point.y - rect.y_max);
    }
    else
    {
        float point_dist_min_to_rect =
          std::fmin(fabs(point.x - rect.x_min), fabs(point.x - rect.x_max));

        return point_dist_min_to_rect;
    }

    float point_dist_min_to_rect = sqrt(point_dist2_to_rect);

    return point_dist_min_to_rect;
}

float EasyComputation::lineLength2(
    const EasyLine2D &line)
{
    float length_2 = (line.x_diff * line.x_diff) + (line.y_diff * line.y_diff);

    return length_2;
}

float EasyComputation::lineLength(
    const EasyLine2D &line)
{
    return sqrt(lineLength2(line));
}

float EasyComputation::angle(
    const EasyLine2D &line_1,
    const EasyLine2D &line_2)
{
    int sign = 1;

    float cross_value = cross(line_1, line_2);

    if(cross_value == 0)
    {
        return 0;
    }

    if(cross_value < 0)
    {
        sign = -1;
    }

    float dot_value = dot(line_1, line_2);

    float line_1_length = lineLength(line_1);
    float line_2_length = lineLength(line_2);

    float cos_value = dot_value / (line_1_length * line_2_length);

    float angle_value = sign * acos(cos_value);

    return angle_value;
}

float EasyComputation::getClockWiseAngle(
    const EasyLine2D &line_1,
    const EasyLine2D &line_2)
{
    float cross_value = cross(line_1, line_2);

    float anti_clock_small_angle = angle(line_1, line_2);

    if(cross_value > 0)
    {
        return 2.0 * M_PI - anti_clock_small_angle;
    }

    if(cross_value == 0)
    {
        if(line_1.x_diff != 0)
        {
            float x_diff_mul = line_1.x_diff * line_2.x_diff;

            if(x_diff_mul < 0)
            {
                return M_PI;
            }

            return 0;
        }

        if(line_1.y_diff != 0)
        {
            float y_diff_mul = line_1.y_diff * line_2.y_diff;

            if(y_diff_mul < 0)
            {
                return M_PI;
            }

            return 0;
        }

        return 0;
    }

    return - anti_clock_small_angle;
}

float EasyComputation::getAntiClockWiseAngle(
    const EasyLine2D &line_1,
    const EasyLine2D &line_2)
{
    float cross_value = cross(line_1, line_2);

    float anti_clock_small_angle = angle(line_1, line_2);

    if(cross_value < 0)
    {
        return 2.0 * M_PI + anti_clock_small_angle;
    }

    if(cross_value == 0)
    {
        if(line_1.x_diff != 0)
        {
            float x_diff_mul = line_1.x_diff * line_2.x_diff;

            if(x_diff_mul < 0)
            {
                return M_PI;
            }

            return 0;
        }

        if(line_1.y_diff != 0)
        {
            float y_diff_mul = line_1.y_diff * line_2.y_diff;

            if(y_diff_mul < 0)
            {
                return M_PI;
            }

            return 0;
        }

        return 0;
    }

    return anti_clock_small_angle;
}

float EasyComputation::getLineDistToLine(
    const EasyLine2D &base_line,
    const EasyLine2D &target_line)
{
    const float base_line_length = lineLength(base_line);

    if(base_line_length == 0)
    {
        std::cout << "EasyComputation::getLineDistToLine : " << std::endl <<
          "Input :\n" <<
          "\tbase_line = [" << base_line.point_1.x << "," << base_line.point_1.y << "]->[" <<
          base_line.point_2.x << "," << base_line.point_2.y << "]" << std::endl <<
          "\ttarget_line = [" << target_line.point_1.x << "," << target_line.point_1.y << "]->[" <<
          target_line.point_2.x << "," << target_line.point_2.y << "]" << std::endl <<
          "base_line length is 0!" << std::endl;

        return -1;
    }

    if(isLineCross(base_line, target_line))
    {
        return 0;
    }

    EasyLine2D unit_base_line;
    unit_base_line.setPosition(
        base_line.point_1.x,
        base_line.point_1.y,
        base_line.point_1.x + base_line.x_diff / base_line_length,
        base_line.point_1.y + base_line.y_diff / base_line_length);

    EasyLine2D unit_base_line_point_1_to_target_line_point_1_line;
    unit_base_line_point_1_to_target_line_point_1_line.setPosition(
        unit_base_line.point_1, target_line.point_1);

    EasyLine2D unit_base_line_point_1_to_target_line_point_2_line;
    unit_base_line_point_1_to_target_line_point_2_line.setPosition(
        unit_base_line.point_1, target_line.point_2);

    float target_line_point_1_position = dot(
        unit_base_line, unit_base_line_point_1_to_target_line_point_1_line);

    float target_line_point_2_position = dot(
        unit_base_line, unit_base_line_point_1_to_target_line_point_2_line);

    float target_line_point_1_dist = cross(
        unit_base_line, unit_base_line_point_1_to_target_line_point_1_line);

    float target_line_point_2_dist = cross(
        unit_base_line, unit_base_line_point_1_to_target_line_point_2_line);

    if(target_line_point_1_position > target_line_point_2_position)
    {
        float temp_exchange_data = target_line_point_1_position;
        target_line_point_1_position = target_line_point_2_position;
        target_line_point_2_position = temp_exchange_data;
        temp_exchange_data = target_line_point_1_dist;
        target_line_point_1_dist = target_line_point_2_dist;
        target_line_point_2_dist = temp_exchange_data;
    }

    if(target_line_point_2_position < 0 || target_line_point_1_position > base_line_length)
    {
        return std::numeric_limits<float>::max();
    }

    if(target_line_point_1_dist < 0 && target_line_point_2_dist < 0)
    {
        return std::numeric_limits<float>::max();
    }

    float min_dist = std::numeric_limits<float>::max();

    if(target_line_point_1_dist >= 0)
    {
        if(0 <= target_line_point_1_position && target_line_point_1_position <= base_line_length)
        {
            min_dist = std::fmin(min_dist, target_line_point_1_dist);

            if(target_line_point_2_dist >= 0)
            {
                if(0 <= target_line_point_2_position && target_line_point_2_position <= base_line_length)
                {
                    min_dist = std::fmin(min_dist, target_line_point_2_dist);
                    return min_dist;
                }
            }

            if(target_line_point_2_position < 0)
            {
                min_dist = std::fmin(min_dist, target_line_point_1_dist - target_line_point_1_position *
                    (target_line_point_1_dist - target_line_point_2_dist) /
                    (target_line_point_1_position - target_line_point_2_position));

                return min_dist;
            }

            min_dist = std::fmin(min_dist, target_line_point_1_dist +
                (base_line_length - target_line_point_1_position) *
                (target_line_point_1_dist - target_line_point_2_dist) /
                (target_line_point_1_position - target_line_point_2_position));

            return min_dist;
        }

        if(target_line_point_2_dist >= 0)
        {
            if(0 <= target_line_point_2_position && target_line_point_2_position <= base_line_length)
            {
                min_dist = std::fmin(min_dist, target_line_point_2_dist);

                if(target_line_point_1_position < 0)
                {
                    min_dist = std::fmin(min_dist, target_line_point_1_dist - target_line_point_1_position *
                        (target_line_point_1_dist - target_line_point_2_dist) /
                        (target_line_point_1_position - target_line_point_2_position));

                    return min_dist;
                }

                min_dist = std::fmin(min_dist, target_line_point_1_dist +
                    (base_line_length - target_line_point_1_position) *
                    (target_line_point_1_dist - target_line_point_2_dist) /
                    (target_line_point_1_position - target_line_point_2_position));

                return min_dist;
            }
        }
    }

    if(0 <= target_line_point_2_position && target_line_point_2_position <= base_line_length)
    {
        min_dist = std::fmin(min_dist, target_line_point_2_dist);

        if(target_line_point_1_position < 0)
        {
            min_dist = std::fmin(min_dist, target_line_point_1_dist - target_line_point_1_position *
                (target_line_point_1_dist - target_line_point_2_dist) /
                (target_line_point_1_position - target_line_point_2_position));

            return min_dist;
        }

        min_dist = std::fmin(min_dist, target_line_point_1_dist +
            (base_line_length - target_line_point_1_position) *
            (target_line_point_1_dist - target_line_point_2_dist) /
            (target_line_point_1_position - target_line_point_2_position));

        return min_dist;
    }

    min_dist = std::fmin(min_dist, target_line_point_1_dist - target_line_point_1_position *
        (target_line_point_1_dist - target_line_point_2_dist) /
        (target_line_point_1_position - target_line_point_2_position));

    min_dist = std::fmin(min_dist, target_line_point_1_dist +
        (base_line_length - target_line_point_1_position) *
        (target_line_point_1_dist - target_line_point_2_dist) /
        (target_line_point_1_position - target_line_point_2_position));

    return min_dist;
}

bool EasyComputation::isSamePoint(
    const EasyPoint2D &point_1,
    const EasyPoint2D &point_2)
{
    if(point_1.x == point_2.x && point_1.y == point_2.y)
    {
        return true;
    }

    return false;
}

bool EasyComputation::isPointInRect(
    const EasyPoint2D &point,
    const EasyRect2D &rect)
{
    if(point.x < rect.x_min)
    {
        return false;
    }

    if(point.x > rect.x_max)
    {
        return false;
    }

    if(point.y < rect.y_min)
    {
        return false;
    }

    if(point.y > rect.y_max)
    {
        return false;
    }

    return true;
}

bool EasyComputation::isPointInLineRect(
    const EasyPoint2D &point,
    const EasyLine2D &line)
{
    if(point.x < line.rect.x_min)
    {
        return false;
    }

    if(point.x > line.rect.x_max)
    {
        return false;
    }

    if(point.y < line.rect.y_min)
    {
        return false;
    }

    if(point.y > line.rect.y_max)
    {
        return false;
    }

    return true;
}

bool EasyComputation::isRectCross(
    const EasyLine2D &line_1,
    const EasyLine2D &line_2)
{
    if(line_1.rect.x_max < line_2.rect.x_min)
    {
        return false;
    }

    if(line_1.rect.x_min > line_2.rect.x_max)
    {
        return false;
    }

    if(line_1.rect.y_max < line_2.rect.y_min)
    {
        return false;
    }

    if(line_1.rect.y_min > line_2.rect.y_max)
    {
        return false;
    }

    return true;
}

bool EasyComputation::isRectCross(
    const EasyRect2D &rect_1,
    const EasyRect2D &rect_2)
{
    if(rect_1.x_max < rect_2.x_min)
    {
        return false;
    }

    if(rect_1.x_min > rect_2.x_max)
    {
        return false;
    }

    if(rect_1.y_max < rect_2.y_min)
    {
        return false;
    }

    if(rect_1.y_min > rect_2.y_max)
    {
        return false;
    }

    return true;
}

bool EasyComputation::isLineCross(
    const EasyLine2D &line_1,
    const EasyLine2D &line_2)
{
    if(!isRectCross(line_1, line_2))
    {
        return false;
    }

    EasyLine2D line_22_to_11;
    EasyLine2D line_22_to_12;

    line_22_to_11.setPosition(
        line_2.point_2,
        line_1.point_1);
    line_22_to_12.setPosition(
        line_2.point_2,
        line_1.point_2);

    float line_1_point_1_cross_line_2 =
      cross(line_22_to_11, line_2);
    float line_1_point_2_corss_line_2 =
      cross(line_22_to_12, line_2);

    if(line_1_point_1_cross_line_2 == 0)
    {
        if(line_1_point_2_corss_line_2 == 0)
        {
            return true;
        }

        return isPointInLineRect(line_1.point_1, line_2);
    }

    if(line_1_point_2_corss_line_2 == 0)
    {
        return isPointInLineRect(line_1.point_2, line_2);
    }

    if(line_1_point_1_cross_line_2 * line_1_point_2_corss_line_2 < 0)
    {
        return true;
    }

    return false;
}

bool EasyComputation::isLineParallel(
    const EasyLine2D &line_1,
    const EasyLine2D &line_2)
{
    if(cross(line_1, line_2) == 0)
    {
        return true;
    }

    return false;
}

bool EasyComputation::isPointOnOpenBoundedLine(
    const EasyPoint2D &point,
    const EasyLine2D &line)
{
    if(line.point_1.x != line.point_2.x)
    {
        if(point.x > line.rect.x_min && point.x < line.rect.x_max)
        {
            return true;
        }
    }
    else if(line.point_1.y != line.point_2.y)
    {
        if(point.y > line.rect.y_min && point.y < line.rect.y_max)
        {
            return true;
        }
    }

    return false;
}

int EasyComputation::isPointInPolygon(
    const EasyPoint2D &point,
    const EasyPolygon2D &polygon)
{
    float angle_value_sum = 0;

    for(size_t i = 0; i < polygon.point_list.size(); ++i)
    {
        const EasyPoint2D &current_point = polygon.point_list[i];

        if(current_point.x == point.x &&
            current_point.y == point.y)
        {
            return 2;
        }

        const EasyPoint2D &next_point = polygon.point_list[
        (i + 1) % polygon.point_list.size()];

        EasyLine2D line_1;
        EasyLine2D line_2;
        line_1.setPosition(
            point,
            current_point);
        line_2.setPosition(
            point,
            next_point);

        angle_value_sum += angle(line_1, line_2);
    }

    float angle_value_sum_to_0 = fabs(angle_value_sum);
    float angle_value_sum_to_pi = fabs(angle_value_sum_to_0 - M_PI);
    float angle_value_sum_to_2pi = fabs(angle_value_sum - 2.0 * M_PI);

    if(angle_value_sum_to_0 < angle_value_sum_to_pi)
    {
        return 0;
    }

    if(angle_value_sum_to_2pi < angle_value_sum_to_pi)
    {
        return 1;
    }

    return 2;
}

bool EasyComputation::isPolygonCross(
    EasyPolygon2D &polygon_1,
    EasyPolygon2D &polygon_2)
{
    EasyRect2D pylygon_1_rect;
    EasyRect2D polygon_2_rect;

    polygon_1.getPolygonRect(pylygon_1_rect);
    polygon_2.getPolygonRect(polygon_2_rect);

    if(!isRectCross(pylygon_1_rect, polygon_2_rect))
    {
        return false;
    }

    std::vector<size_t> polygon_2_point_on_polygon_1_boundary_idx_vec;
    std::vector<size_t> polygon_1_point_on_polygon_2_boundary_idx_vec;

    for(size_t i = 0; i < polygon_2.point_list.size(); ++i)
    {
        const EasyPoint2D &point = polygon_2.point_list[i];

        int point_state = isPointInPolygon(point, polygon_1);

        if(point_state == 1)
        {
            return true;
        }
        else if(point_state == 2)
        {
            polygon_2_point_on_polygon_1_boundary_idx_vec.emplace_back(i);
        }
    }

    for(size_t i = 0; i < polygon_1.point_list.size(); ++i)
    {
        const EasyPoint2D &point = polygon_1.point_list[i];

        int point_state = isPointInPolygon(point, polygon_2);

        if(point_state == 1)
        {
            return true;
        }
        else if(point_state == 2)
        {
            polygon_1_point_on_polygon_2_boundary_idx_vec.emplace_back(i);
        }
    }

    if(polygon_2_point_on_polygon_1_boundary_idx_vec.size() == 0 &&
        polygon_1_point_on_polygon_2_boundary_idx_vec.size() == 0)
    {
        return false;
    }

    if(polygon_2_point_on_polygon_1_boundary_idx_vec.size() > 0)
    {
    }

    return false;
}

PointState EasyComputation::getPointStateOfLine(
    const EasyPoint2D &point,
    const EasyLine2D &line)
{
    const EasyPoint2D &line_point_1 = line.point_1;

    if(point.x == line_point_1.x &&
        point.y == line_point_1.y)
    {
        return PointState::PointOnVertex;
    }

    const EasyPoint2D &line_point_2 = line.point_2;

    if(point.x == line_point_2.x &&
        point.y == line_point_2.y)
    {
        return PointState::PointOnVertex;
    }

    if(line_point_1.x == line_point_2.x)
    {
        if(line_point_1.y == line_point_2.y)
        {
            return PointState::PointOutside;
        }

        if(point.x != line_point_1.x)
        {
            return PointState::PointOutside;
        }

        if(point.y == line_point_1.y ||
            point.y == line_point_2.y)
        {
            return PointState::PointOutside;
        }

        if((line_point_1.y < point.y && point.y < line_point_2.y) ||
            (line_point_2.y < point.y && point.y < line_point_1.y))
        {
            return PointState::PointOnEdge;
        }

        return PointState::PointOutside;
    }

    if(line_point_1.y == line_point_2.y)
    {
        if(point.y != line_point_1.y)
        {
            return PointState::PointOutside;
        }

        if(point.x == line_point_1.x ||
            point.x == line_point_2.x)
        {
            return PointState::PointOutside;
        }

        if((line_point_1.x < point.x && point.x < line_point_2.x) ||
            (line_point_2.x < point.x && point.x < line_point_1.x))
        {
            return PointState::PointOnEdge;
        }

        return PointState::PointOutside;
    }

    if((point.y - line_point_1.y) / (point.x - line_point_1.x) !=
        (line_point_2.y - line_point_1.y) / (line_point_2.x - line_point_1.x))
    {
        return PointState::PointOutside;
    }

    if((line_point_1.x < point.x && point.x < line_point_2.x) ||
        (line_point_2.x < point.x && point.x < line_point_1.x))
    {
        return PointState::PointOnEdge;
    }

    return PointState::PointOutside;
}

PointState EasyComputation::getPointStateOfPolygon(
    const EasyPoint2D &point,
    const EasyPolygon2D &polygon)
{
    float angle_value_sum = 0;

    for(size_t i = 0; i < polygon.point_list.size(); ++i)
    {
        const EasyPoint2D &current_point = polygon.point_list[i];

        if(current_point.x == point.x &&
            current_point.y == point.y)
        {
            return PointState::PointOnVertex;
        }

        const EasyPoint2D &next_point = polygon.point_list[
        (i + 1) % polygon.point_list.size()];

        EasyLine2D line_1;
        EasyLine2D line_2;
        line_1.setPosition(
            point,
            current_point);
        line_2.setPosition(
            point,
            next_point);

        angle_value_sum += angle(line_1, line_2);
    }

    float angle_value_sum_to_0 = fabs(angle_value_sum);
    float angle_value_sum_to_pi = fabs(angle_value_sum_to_0 - M_PI);
    float angle_value_sum_to_2pi = fabs(angle_value_sum - 2.0 * M_PI);

    if(angle_value_sum_to_0 < angle_value_sum_to_pi)
    {
        return PointState::PointOutside;
    }

    if(angle_value_sum_to_2pi < angle_value_sum_to_pi)
    {
        return PointState::PointInside;
    }

    return PointState::PointOnEdge;
}

LineState EasyComputation::getLineStateOfLine(
    const EasyLine2D &line_1,
    const EasyLine2D &line_2)
{
}

LineState EasyComputation::getLineStateOfPolygon(
    const EasyLine2D &line,
    const EasyPolygon2D &polygon)
{
    const PointState line_point_1_state =
      getPointStateOfPolygon(line.point_1, polygon);

    const PointState line_point_2_state =
      getPointStateOfPolygon(line.point_2, polygon);

    if(line_point_1_state == PointState::PointInside)
    {
        if(line_point_2_state == PointState::PointInside)
        {
            return LineState::LineInside;
        }

        if(line_point_2_state == PointState::PointOnVertex)
        {
            return LineState::LineCrossVertex;
        }

        if(line_point_2_state == PointState::PointOnEdge)
        {
            return LineState::LineCrossEdge;
        }
    }
}

bool EasyComputation::getLineCrossPoint(
    const EasyLine2D &line_1,
    const EasyLine2D &line_2,
    EasyPoint2D &line_cross_point)
{
    float line_cross = cross(line_1, line_2);

    if(line_cross == 0)
    {
        std::cout << "EasyPolygon2D::getLineCrossPoint : lines are parallel!" << std::endl;
        return false;
    }

    float line_1_weight =
      (line_2.point_2.y - line_2.point_1.y) * line_2.point_1.x +
      (line_2.point_1.x - line_2.point_2.x) * line_2.point_1.y;

    float line_2_weight =
      (line_1.point_2.y - line_1.point_1.y) * line_1.point_1.x +
      (line_1.point_1.x - line_1.point_2.x) * line_1.point_1.y;

    float line_cross_point_x_weight =
      line_1_weight * (line_1.point_2.x - line_1.point_1.x) -
      line_2_weight * (line_2.point_2.x - line_2.point_1.x);

    float line_cross_point_y_weight =
      line_1_weight * (line_1.point_2.y - line_1.point_1.y) -
      line_2_weight * (line_2.point_2.y - line_2.point_1.y);

    line_cross_point.x = line_cross_point_x_weight / line_cross;
    line_cross_point.y = line_cross_point_y_weight / line_cross;

    return true;
}

bool EasyComputation::getBoundedLineCrossPointVec(
    const EasyLine2D &line_1,
    const EasyLine2D &line_2,
    std::vector<EasyPoint2D> &line_cross_point_vec)
{
    line_cross_point_vec.clear();

    if(!isLineCross(line_1, line_2))
    {
        return true;
    }

    if(isLineParallel(line_1, line_2))
    {
        if(isSamePoint(line_1.point_1, line_2.point_1))
        {
            line_cross_point_vec.emplace_back(line_1.point_1);

            if(isSamePoint(line_1.point_2, line_2.point_2))
            {
                line_cross_point_vec.emplace_back(line_1.point_2);
            }
        }
        else if(isSamePoint(line_1.point_2, line_2.point_1))
        {
            line_cross_point_vec.emplace_back(line_1.point_2);

            if(isSamePoint(line_1.point_1, line_2.point_2))
            {
                line_cross_point_vec.emplace_back(line_1.point_1);
            }
        }

        if(isPointOnOpenBoundedLine(line_1.point_1, line_2))
        {
            line_cross_point_vec.emplace_back(line_1.point_1);
        }
        if(isPointOnOpenBoundedLine(line_1.point_2, line_2))
        {
            line_cross_point_vec.emplace_back(line_1.point_2);
        }
        if(isPointOnOpenBoundedLine(line_2.point_1, line_1))
        {
            line_cross_point_vec.emplace_back(line_2.point_1);
        }
        if(isPointOnOpenBoundedLine(line_2.point_2, line_1))
        {
            line_cross_point_vec.emplace_back(line_2.point_2);
        }

        return true;
    }

    EasyPoint2D line_cross_point;

    getLineCrossPoint(line_1, line_2, line_cross_point);

    line_cross_point_vec.emplace_back(line_cross_point);

    return true;
}

bool EasyComputation::getPolygonIntersection(
    std::vector<EasyPolygon2D> &polygon_vec,
    std::vector<EasyIntersection2D> &intersection_vec)
{
    intersection_vec.clear();

    if(polygon_vec.size() < 2)
    {
        return true;
    }

    for(size_t i = 1; i < polygon_vec.size(); ++i)
    {
        EasyPolygon2D &polygon_1 = polygon_vec[i];

        for(size_t j = 0; j < i; ++j)
        {
            EasyPolygon2D &polygon_2 = polygon_vec[j];

            for(size_t k = 0; k < polygon_1.point_list.size(); ++k)
            {
                EasyLine2D polygon_1_line;
                polygon_1_line.setPosition(
                    polygon_1.point_list[k],
                    polygon_1.point_list[(k + 1) % polygon_1.point_list.size()]);

                for(size_t l = 0; l < polygon_2.point_list.size(); ++l)
                {
                    EasyLine2D polygon_2_line;
                    polygon_2_line.setPosition(
                        polygon_2.point_list[l],
                        polygon_2.point_list[(l + 1) % polygon_2.point_list.size()]);

                    std::vector<EasyPoint2D> line_cross_point_vec;
                    getBoundedLineCrossPointVec(
                        polygon_1_line,
                        polygon_2_line,
                        line_cross_point_vec);

                    if(line_cross_point_vec.size() == 0)
                    {
                        continue;
                    }

                    for(const EasyPoint2D &line_cross_point : line_cross_point_vec)
                    {
                        bool cross_point_exist = false;

                        for(EasyIntersection2D &exist_intersection : intersection_vec)
                        {
                            if(isSamePoint(exist_intersection.point, line_cross_point))
                            {
                                exist_intersection.addPolygonPointIdx(i, k);
                                exist_intersection.addPolygonPointIdx(j, l);
                                cross_point_exist = true;

                                break;
                            }
                        }

                        if(!cross_point_exist)
                        {
                            EasyIntersection2D intersection;

                            intersection.setPosition(line_cross_point);

                            intersection.addPolygonPointIdx(i, k);
                            intersection.addPolygonPointIdx(j, l);

                            intersection_vec.emplace_back(intersection);
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool EasyComputation::getSortedIntersectionOnPolygonLine(
    const EasyPolygon2D &polygon,
    const std::vector<EasyIntersection2D> &intersection_vec,
    const size_t &polygon_idx,
    const size_t &point_idx,
    std::vector<size_t> &sorted_intersection_idx_on_polygon_line_vec)
{
    sorted_intersection_idx_on_polygon_line_vec.clear();

    if(intersection_vec.size() == 0)
    {
        return true;
    }

    std::vector<size_t> intersection_idx_on_polygon_line_vec;

    for(size_t i = 0; i < intersection_vec.size(); ++i)
    {
        const EasyIntersection2D &intersection = intersection_vec[i];

        if(intersection.haveThisPointIdx(polygon_idx, point_idx))
        {
            intersection_idx_on_polygon_line_vec.emplace_back(i);
        }
    }

    const EasyPoint2D &point_start = polygon.point_list[point_idx];
    const EasyPoint2D &point_end = polygon.point_list[(point_idx + 1) % polygon.point_list.size()];

    std::vector<float> intersection_to_point_start_diff_vec;
    intersection_to_point_start_diff_vec.resize(intersection_idx_on_polygon_line_vec.size());

    std::vector<bool> intersection_idx_selected_vec;
    intersection_idx_selected_vec.resize(intersection_idx_on_polygon_line_vec.size(), false);

    if(point_start.x != point_end.x)
    {
        float line_x_diff = point_end.x - point_start.x;

        for(size_t i = 0; i < intersection_idx_on_polygon_line_vec.size(); ++i)
        {
            intersection_to_point_start_diff_vec[i] =
              (intersection_vec[intersection_idx_on_polygon_line_vec[i]].point.x - point_start.x) /
              line_x_diff;
        }

        for(size_t i = 0; i < intersection_idx_on_polygon_line_vec.size(); ++i)
        {
            float min_dist = -1;
            int min_dist_intersection_idx = -1;

            for(size_t j = 0; j < intersection_idx_on_polygon_line_vec.size(); ++j)
            {
                if(intersection_idx_selected_vec[j])
                {
                    continue;
                }

                if(min_dist_intersection_idx == -1 ||
                    intersection_to_point_start_diff_vec[j] < min_dist)
                {
                    min_dist = intersection_to_point_start_diff_vec[j];
                    min_dist_intersection_idx = j;
                }
            }

            intersection_idx_selected_vec[min_dist_intersection_idx] = true;

            sorted_intersection_idx_on_polygon_line_vec.emplace_back(
                intersection_idx_on_polygon_line_vec[min_dist_intersection_idx]);
        }

        return true;
    }

    float line_y_diff = point_end.y - point_start.y;

    for(size_t i = 0; i < intersection_idx_on_polygon_line_vec.size(); ++i)
    {
        intersection_to_point_start_diff_vec[i] =
          (intersection_vec[intersection_idx_on_polygon_line_vec[i]].point.y - point_start.y) /
          line_y_diff;
    }

    for(size_t i = 0; i < intersection_idx_on_polygon_line_vec.size(); ++i)
    {
        float min_dist = -1;
        int min_dist_intersection_idx = -1;

        for(size_t j = 0; j < intersection_idx_on_polygon_line_vec.size(); ++j)
        {
            if(intersection_idx_selected_vec[j])
            {
                continue;
            }

            if(min_dist_intersection_idx == -1 ||
                intersection_to_point_start_diff_vec[j] < min_dist)
            {
                min_dist = intersection_to_point_start_diff_vec[j];
                min_dist_intersection_idx = j;
            }
        }

        intersection_idx_selected_vec[min_dist_intersection_idx] = true;

        sorted_intersection_idx_on_polygon_line_vec.emplace_back(
            intersection_idx_on_polygon_line_vec[min_dist_intersection_idx]);
    }

    return true;
}

bool EasyComputation::getSplitPolygonAndIntersectionPosition(
    const EasyPolygon2D &polygon,
    const std::vector<EasyIntersection2D> &intersection_vec,
    const size_t &polygon_idx,
    EasyPolygon2D &split_polygon,
    std::vector<std::pair<size_t, size_t>> &intersection_idx_polygon_point_idx_pair_vec)
{
    intersection_idx_polygon_point_idx_pair_vec.clear();

    if(intersection_vec.size() == 0)
    {
        return true;
    }

    size_t current_new_point_idx = 0;

    for(size_t i = 0; i < polygon.point_list.size(); ++i)
    {
        split_polygon.addPoint(polygon.point_list[i]);

        ++current_new_point_idx;

        std::vector<size_t> sorted_intersection_idx_on_polygon_line_vec;
        getSortedIntersectionOnPolygonLine(
            polygon,
            intersection_vec,
            polygon_idx,
            i,
            sorted_intersection_idx_on_polygon_line_vec);

        if(sorted_intersection_idx_on_polygon_line_vec.size() == 0)
        {
            continue;
        }

        for(const size_t &sorted_intersection_idx : sorted_intersection_idx_on_polygon_line_vec)
        {
            if(isSamePoint(
                  polygon.point_list[i],
                  intersection_vec[sorted_intersection_idx].point))
            {
                std::pair<size_t, size_t> intersection_idx_polygon_point_idx_pair;
                intersection_idx_polygon_point_idx_pair.first = sorted_intersection_idx;
                intersection_idx_polygon_point_idx_pair.second = current_new_point_idx - 1;
                intersection_idx_polygon_point_idx_pair_vec.emplace_back(
                    intersection_idx_polygon_point_idx_pair);

                continue;
            }

            if(isSamePoint(
                  polygon.point_list[(i + 1) % polygon.point_list.size()],
                  intersection_vec[sorted_intersection_idx].point))
            {
                continue;
            }

            split_polygon.addPoint(intersection_vec[sorted_intersection_idx].point);

            std::pair<size_t, size_t> intersection_idx_polygon_point_idx_pair;
            intersection_idx_polygon_point_idx_pair.first = sorted_intersection_idx;
            intersection_idx_polygon_point_idx_pair.second = current_new_point_idx;
            intersection_idx_polygon_point_idx_pair_vec.emplace_back(
                intersection_idx_polygon_point_idx_pair);

            ++current_new_point_idx;
        }
    }

    return true;
}

bool EasyComputation::splitPolygonsByIntersection(
    const std::vector<EasyIntersection2D> &intersection_vec,
    const std::vector<EasyPolygon2D> &polygon_vec,
    std::vector<EasyIntersection2D> &split_intersection_vec,
    std::vector<EasyPolygon2D> &split_polygon_vec)
{
    split_intersection_vec.clear();
    split_polygon_vec.clear();

    if(intersection_vec.size() == 0)
    {
        split_polygon_vec = polygon_vec;
        return true;
    }

    for(const EasyIntersection2D &intersection : intersection_vec)
    {
        const EasyPoint2D &intersection_point = intersection.point;

        EasyIntersection2D empty_split_intersection;
        empty_split_intersection.setPosition(intersection_point);
        split_intersection_vec.emplace_back(empty_split_intersection);
    }

    for(size_t i = 0; i < polygon_vec.size(); ++i)
    {
        const EasyPolygon2D &polygon = polygon_vec[i];

        EasyPolygon2D split_polygon;
        std::vector<std::pair<size_t, size_t>> intersection_idx_polygon_point_idx_pair_vec;

        getSplitPolygonAndIntersectionPosition(
            polygon,
            intersection_vec,
            i,
            split_polygon,
            intersection_idx_polygon_point_idx_pair_vec);

        split_polygon_vec.emplace_back(split_polygon);

        for(const std::pair<size_t, size_t> &intersection_idx_polygon_point_idx_pair :
            intersection_idx_polygon_point_idx_pair_vec)
        {
            split_intersection_vec[intersection_idx_polygon_point_idx_pair.first].addPolygonPointIdx(
                i,
                intersection_idx_polygon_point_idx_pair.second);
        }
    }

    return true;
}

bool EasyComputation::getIntersectionIdxOnPolygonPoint(
    const std::vector<EasyPolygon2D> &polygon_vec,
    const std::vector<EasyIntersection2D> &intersection_vec,
    const size_t &polygon_idx,
    const size_t &point_idx,
    size_t &intersection_idx)
{
    if(intersection_vec.size() == 0)
    {
        return false;
    }

    for(size_t i = 0; i < intersection_vec.size(); ++i)
    {
        if(isSamePoint(intersection_vec[i].point, polygon_vec[polygon_idx].point_list[point_idx]))
        {
            intersection_idx = i;

            return true;
        }
    }

    return false;
}

bool EasyComputation::updatePolygonIntersectionPointConnectedState(
    const EasyIntersection2D &intersection,
    std::vector<std::vector<bool>> &polygon_point_connected_vec_vec)
{
    for(const std::pair<size_t, std::vector<size_t>> &polygon_point_idx_vec_pair :
        intersection.polygon_point_idx_vec_pair_vec)
    {
        for(const size_t polygon_point_idx : polygon_point_idx_vec_pair.second)
        {
            polygon_point_connected_vec_vec[polygon_point_idx_vec_pair.first][polygon_point_idx] = true;
        }
    }

    return true;
}

bool EasyComputation::updatePolygonNotIntersectionPointConnectedState(
    const std::vector<EasyPolygon2D> &polygon_vec,
    const EasyPolygon2D &union_polygon,
    std::vector<std::vector<bool>> &polygon_point_connected_vec_vec)
{
    for(size_t i = 0; i < polygon_vec.size(); ++i)
    {
        const EasyPolygon2D &polygon = polygon_vec[i];

        for(size_t j = 0; j < polygon.point_list.size(); ++j)
        {
            if(polygon_point_connected_vec_vec[i][j])
            {
                continue;
            }

            const EasyPoint2D &polygon_point = polygon.point_list[j];

            if(isPointInPolygon(polygon_point, union_polygon))
            {
                polygon_point_connected_vec_vec[i][j] = true;
            }
        }
    }

    return true;
}

bool EasyComputation::addNewPolygonPoint(
    const std::vector<EasyPolygon2D> &polygon_vec,
    const size_t &polygon_idx,
    const size_t &start_point_idx,
    EasyPolygon2D &union_polygon,
    std::vector<std::vector<bool>> &polygon_point_connected_vec_vec)
{
    if(polygon_idx >= polygon_vec.size())
    {
        std::cout << "EasyComputation::addNewPolygonPoint : polygon_idx out of range!" << std::endl;
        return false;
    }

    union_polygon.addPoint(
        polygon_vec[polygon_idx].point_list[start_point_idx]);

    polygon_point_connected_vec_vec[polygon_idx][start_point_idx] = true;

    return true;
}

bool EasyComputation::getMinimalAnglePolygonPointIdx(
    const std::vector<EasyPolygon2D> &polygon_vec,
    const std::vector<EasyIntersection2D> &intersection_vec,
    const size_t &polygon_idx,
    const size_t &start_point_idx,
    const size_t &start_intersection_idx,
    std::pair<size_t, size_t> &minimal_angle_polygon_point_idx)
{
    if(intersection_vec.size() == 0)
    {
        std::cout << "EasyComputation::getMinimalAnglePolygonPointIdx : intersection is empty!" << std::endl;
        return false;
    }

    float minimal_angle = 2.0 * M_PI;

    const size_t polygon_prev_point_idx =
      (start_point_idx - 1 + polygon_vec[polygon_idx].point_list.size()) %
      polygon_vec[polygon_idx].point_list.size();

    EasyLine2D line_intersection_to_polygon_prev_point;
    line_intersection_to_polygon_prev_point.setPosition(
        intersection_vec[start_intersection_idx].point,
        polygon_vec[polygon_idx].point_list[polygon_prev_point_idx]);

    for(const std::pair<size_t, std::vector<size_t>> &polygon_point_idx_vec_pair :
        intersection_vec[start_intersection_idx].polygon_point_idx_vec_pair_vec)
    {
        for(const size_t &polygon_point_idx : polygon_point_idx_vec_pair.second)
        {
            const size_t polygon_next_point_idx =
              (polygon_point_idx + 1) %
              polygon_vec[polygon_point_idx_vec_pair.first].point_list.size();

            EasyLine2D line_intersection_to_polygon_next_point;
            line_intersection_to_polygon_next_point.setPosition(
                intersection_vec[start_intersection_idx].point,
                polygon_vec[polygon_point_idx_vec_pair.first].point_list[polygon_next_point_idx]);

            float current_angle = getAntiClockWiseAngle(
                line_intersection_to_polygon_prev_point,
                line_intersection_to_polygon_next_point);

            if(current_angle == 0)
            {
                continue;
            }

            if(current_angle < minimal_angle)
            {
                minimal_angle = current_angle;
                minimal_angle_polygon_point_idx.first = polygon_point_idx_vec_pair.first;
                minimal_angle_polygon_point_idx.second = polygon_next_point_idx;
            }
        }
    }

    if(minimal_angle == 2.0 * M_PI)
    {
        std::cout << "no new polygon point found!" << std::endl;
        return false;
    }

    return true;
}

bool EasyComputation::getUnionPolygonPoints(
    const std::vector<EasyPolygon2D> &polygon_vec,
    const std::vector<EasyIntersection2D> &intersection_vec,
    const size_t &start_polygon_idx,
    const size_t &start_point_idx,
    const size_t &current_start_polygon_idx,
    const size_t &current_start_point_idx,
    EasyPolygon2D &union_polygon,
    std::vector<std::vector<bool>> &polygon_point_connected_vec_vec)
{
    std::cout << "current running at p" << current_start_polygon_idx << current_start_point_idx << std::endl;
    size_t connected_polygon_point_num = 0;

    for(const std::vector<bool> &polygon_point_connected_vec :
        polygon_point_connected_vec_vec)
    {
        connected_polygon_point_num += count(
            polygon_point_connected_vec.cbegin(),
            polygon_point_connected_vec.cend(),
            true);
    }
    std::cout << "connected_polygon_point_num_ = " << connected_polygon_point_num_ << std::endl;
    std::cout << "connected_polygon_point_num = " << connected_polygon_point_num << std::endl;
    if(connected_polygon_point_num_ == connected_polygon_point_num)
    {
        std::cout << "force quit" << std::endl;

        if(true)
        {
            std::cout << "+++++++++++++++" << std::endl;
            for(size_t i = 0; i < polygon_vec.size(); ++i)
            {
                const EasyPolygon2D &split_polygon = polygon_vec[i];
                std::cout << "current polygon " << i << " :" << std::endl <<
                  "points :" << std::endl;
                for(size_t j = 0; j < split_polygon.point_list.size(); ++j)
                {
                    std::cout << "\t" << j << " : [" <<
                      split_polygon.point_list[j].x << "," <<
                      split_polygon.point_list[j].y << "]" << std::endl;
                }
            }
            std::cout << "current intersection:" << std::endl;
            for(size_t i = 0; i < intersection_vec.size(); ++i)
            {
                std::cout << "points :" << std::endl;
                std::cout << "\t" << i << " : [" <<
                  intersection_vec[i].point.x << "," <<
                  intersection_vec[i].point.y << "]" << std::endl;
                std::cout << "idx :" << std::endl;
                for(size_t j = 0;
                    j < intersection_vec[i].polygon_point_idx_vec_pair_vec.size();
                    ++j)
                {
                    const auto &polygon_line_idx_vec_pair =
                      intersection_vec[i].polygon_point_idx_vec_pair_vec[j];
                    std::cout << "\tpolygon id : " <<
                      polygon_line_idx_vec_pair.first << std::endl;
                    std::cout << "\tpolygon line idx :";
                    for(size_t k = 0; k < polygon_line_idx_vec_pair.second.size(); ++k)
                    {
                        std::cout << polygon_line_idx_vec_pair.second[k] << " , ";
                    }
                    std::cout << std::endl;
                }
            }
            std::cout << "+++++++++++++++" << std::endl;
        }

        exit(0);
    }
    connected_polygon_point_num_ = connected_polygon_point_num;

    if(current_start_polygon_idx == start_polygon_idx &&
        current_start_point_idx == start_point_idx)
    {
        return true;
    }

    size_t new_start_polygon_idx = current_start_polygon_idx;
    size_t new_start_point_idx = current_start_point_idx;

    addNewPolygonPoint(
        polygon_vec,
        new_start_polygon_idx,
        new_start_point_idx,
        union_polygon,
        polygon_point_connected_vec_vec);

    size_t intersection_idx;

    if(getIntersectionIdxOnPolygonPoint(
          polygon_vec,
          intersection_vec,
          new_start_polygon_idx,
          new_start_point_idx,
          intersection_idx))
    {
        updatePolygonIntersectionPointConnectedState(
            intersection_vec[intersection_idx],
            polygon_point_connected_vec_vec);

        std::pair<size_t, size_t> minimal_angle_polygon_point_idx_pair;

        getMinimalAnglePolygonPointIdx(
            polygon_vec,
            intersection_vec,
            new_start_polygon_idx,
            new_start_point_idx,
            intersection_idx,
            minimal_angle_polygon_point_idx_pair);

        new_start_polygon_idx = minimal_angle_polygon_point_idx_pair.first;
        new_start_point_idx = minimal_angle_polygon_point_idx_pair.second;

        return getUnionPolygonPoints(
            polygon_vec,
            intersection_vec,
            start_polygon_idx,
            start_point_idx,
            new_start_polygon_idx,
            new_start_point_idx,
            union_polygon,
            polygon_point_connected_vec_vec);
    }

    new_start_point_idx =
      (new_start_point_idx + 1) % polygon_vec[new_start_polygon_idx].point_list.size();

    return getUnionPolygonPoints(
        polygon_vec,
        intersection_vec,
        start_polygon_idx,
        start_point_idx,
        new_start_polygon_idx,
        new_start_point_idx,
        union_polygon,
        polygon_point_connected_vec_vec);
}

bool EasyComputation::getUnionPolygonVec(
    std::vector<EasyPolygon2D> &polygon_vec,
    std::vector<EasyPolygon2D> &union_polygon_vec)
{
    union_polygon_vec.clear();

    std::vector<EasyPolygon2D> valid_polygon_vec;

    for(const EasyPolygon2D &polygon : polygon_vec)
    {
        if(polygon.point_list.size() > 0)
        {
            valid_polygon_vec.emplace_back(polygon);
        }
    }

    if(valid_polygon_vec.size() == 0)
    {
        return true;
    }

    if(valid_polygon_vec.size() == 1)
    {
        union_polygon_vec.emplace_back(valid_polygon_vec[0]);

        return true;
    }

    std::vector<EasyIntersection2D> intersection_vec;
    getPolygonIntersection(valid_polygon_vec, intersection_vec);

    std::vector<EasyPolygon2D> split_polygon_vec;
    std::vector<EasyIntersection2D> split_intersection_vec;

    splitPolygonsByIntersection(
        intersection_vec,
        valid_polygon_vec,
        split_intersection_vec,
        split_polygon_vec);

    size_t connected_polygon_point_num = 0;
    size_t total_polygon_point_num = 0;

    std::vector<std::vector<bool>> polygon_point_connected_vec_vec;
    polygon_point_connected_vec_vec.resize(split_polygon_vec.size());
    for(size_t i = 0; i < split_polygon_vec.size(); ++i)
    {
        polygon_point_connected_vec_vec[i].resize(split_polygon_vec[i].point_list.size(), false);
        total_polygon_point_num += split_polygon_vec[i].point_list.size();
    }

    while(connected_polygon_point_num < total_polygon_point_num)
    {
        EasyPolygon2D current_union_polygon;

        float x_min;
        float y_max;
        int current_start_polygon_idx = -1;
        int current_start_point_idx = -1;

        for(size_t i = 0; i < split_polygon_vec.size(); ++i)
        {
            EasyPolygon2D &split_polygon = split_polygon_vec[i];

            for(size_t j = 0; j < split_polygon.point_list.size(); ++j)
            {
                EasyPoint2D &polygon_point = split_polygon.point_list[j];

                if(!polygon_point_connected_vec_vec[i][j])
                {
                    if(current_start_polygon_idx == -1)
                    {
                        x_min = polygon_point.x;
                        y_max = polygon_point.y;
                        current_start_polygon_idx = i;
                        current_start_point_idx = j;
                    }
                    else if(polygon_point.x < x_min)
                    {
                        x_min = polygon_point.x;
                        current_start_polygon_idx = i;
                        current_start_point_idx = j;
                    }
                    else if(polygon_point.x == x_min)
                    {
                        if(polygon_point.y > y_max)
                        {
                            y_max = polygon_point.y;
                            current_start_polygon_idx = i;
                            current_start_point_idx = j;
                        }
                    }
                }
            }
        }

        if(true)
        {
            for(size_t i = 0; i < split_polygon_vec.size(); ++i)
            {
                const EasyPolygon2D &split_polygon = split_polygon_vec[i];
                std::cout << "current polygon " << i << " :" << std::endl <<
                  "points :" << std::endl;
                for(size_t j = 0; j < split_polygon.point_list.size(); ++j)
                {
                    std::cout << "\t" << j << " : [" <<
                      split_polygon.point_list[j].x << "," <<
                      split_polygon.point_list[j].y << "]" << std::endl;
                }
            }
            std::cout << "current intersection:" << std::endl;
            for(size_t i = 0; i < split_intersection_vec.size(); ++i)
            {
                std::cout << "points :" << std::endl;
                std::cout << "\t" << i << " : [" <<
                  split_intersection_vec[i].point.x << "," <<
                  split_intersection_vec[i].point.y << "]" << std::endl;
                std::cout << "idx :" << std::endl;
                for(size_t j = 0;
                    j < split_intersection_vec[i].polygon_point_idx_vec_pair_vec.size();
                    ++j)
                {
                    const auto &polygon_line_idx_vec_pair =
                      split_intersection_vec[i].polygon_point_idx_vec_pair_vec[j];
                    std::cout << "\tpolygon id : " <<
                      polygon_line_idx_vec_pair.first << std::endl;
                    std::cout << "\tpolygon line idx :";
                    for(size_t k = 0; k < polygon_line_idx_vec_pair.second.size(); ++k)
                    {
                        std::cout << polygon_line_idx_vec_pair.second[k] << " , ";
                    }
                    std::cout << std::endl;
                }
            }
        }

        int start_point_idx = current_start_point_idx;

        addNewPolygonPoint(
            split_polygon_vec,
            current_start_polygon_idx,
            current_start_point_idx,
            current_union_polygon,
            polygon_point_connected_vec_vec);

        std::cout << "current running at p" << current_start_polygon_idx << current_start_point_idx << std::endl;

        size_t intersection_idx;
        if(getIntersectionIdxOnPolygonPoint(
              split_polygon_vec,
              split_intersection_vec,
              current_start_polygon_idx,
              current_start_point_idx,
              intersection_idx))
        {
            updatePolygonIntersectionPointConnectedState(
                split_intersection_vec[intersection_idx],
                polygon_point_connected_vec_vec);
        }

        current_start_point_idx =
          (current_start_point_idx + 1) % split_polygon_vec[current_start_polygon_idx].point_list.size();

        std::cout << "current running at p" << current_start_polygon_idx << current_start_point_idx << std::endl;
        std::cout << "start running getUnionPolygonPoints" << std::endl;

        getUnionPolygonPoints(
            split_polygon_vec,
            split_intersection_vec,
            current_start_polygon_idx,
            start_point_idx,
            current_start_polygon_idx,
            current_start_point_idx,
            current_union_polygon,
            polygon_point_connected_vec_vec);

        updatePolygonNotIntersectionPointConnectedState(
            split_polygon_vec,
            current_union_polygon,
            polygon_point_connected_vec_vec);

        union_polygon_vec.emplace_back(current_union_polygon);

        std::cout << "current union_polygon:" << std::endl <<
          "points :" << std::endl;
        for(size_t i = 0; i < current_union_polygon.point_list.size(); ++i)
        {
            std::cout << "\t" << i << " : [" <<
              current_union_polygon.point_list[i].x << "," <<
              current_union_polygon.point_list[i].y << "]" << std::endl;
        }

        connected_polygon_point_num = 0;

        for(const std::vector<bool> &polygon_point_connected_vec :
            polygon_point_connected_vec_vec)
        {
            connected_polygon_point_num += count(
                polygon_point_connected_vec.cbegin(),
                polygon_point_connected_vec.cend(),
                true);
        }

        std::cout << "now still have :";
        for(size_t i = 0; i < polygon_point_connected_vec_vec.size(); ++i)
        {
            const auto &polygon_point_connected_vec = polygon_point_connected_vec_vec[i];
            for(size_t j = 0; j < polygon_point_connected_vec.size(); ++j)
            {
                if(!polygon_point_connected_vec[j])
                {
                    std::cout << " p" << i << j;
                }
            }
        }
        std::cout << " not connected!" << std::endl;

        std::cout << "connected_polygon_point_num = " << connected_polygon_point_num << std::endl;
        std::cout << "total_polygon_point_num = " << total_polygon_point_num << std::endl;
    }

    return true;
}

