#include "EasyPolygon2D.h"
#include <limits>

bool EasyPolygon2D::reset()
{
    point_list.clear();

    return true;
}

bool EasyPolygon2D::addPoint(
    const EasyPoint2D &point)
{
    point_list.emplace_back(point);

    if(!update())
    {
        std::cout << "EasyPolygon2D::addPoint :\n" <<
          "Input :\n" <<
          "point = [" << point.x << "," <<
          point.y << "]\n" <<
          "update failed!\n";

        return false;
    }

    return true;
}

bool EasyPolygon2D::addPoint(
    const float &x,
    const float &y)
{
    EasyPoint2D point;
    point.setPosition(x, y);

    return addPoint(point);
}

bool EasyPolygon2D::insertPoint(
    const EasyPoint2D &point,
    const size_t &insert_idx)
{
    if(insert_idx > point_list.size() - 1)
    {
        std::cout << "insert point to polygon failed!" << std::endl;
        return false;
    }

    point_list.insert(point_list.begin() + insert_idx, point);


    if(!update())
    {
        std::cout << "EasyPolygon2D::addPoint :\n" <<
          "Input :\n" <<
          "point = [" << point.x << "," <<
          point.y << "]\n" <<
          "update failed!\n";

        return false;
    }

    return true;
}

bool EasyPolygon2D::removePoint(
    const size_t &remove_idx)
{
    if(remove_idx > point_list.size() - 1)
    {
        std::cout << "remove point from polygon failed!" << std::endl;
        return false;
    }

    point_list.erase(point_list.begin() + remove_idx);

    if(!update())
    {
        std::cout << "EasyPolygon2D::addPoint :\n" <<
          "Input :\n" <<
          "remove_idx = " << remove_idx << std::endl <<
          "update failed!\n";

        return false;
    }

    return true;
}

bool EasyPolygon2D::setPointPosition(
    const size_t& point_idx,
    const EasyPoint2D& point_position)
{
    if(point_idx >= point_list.size())
    {
        std::cout << "EasyPolygon2D::setPointPosition :\n" <<
          "Input :\n" <<
          "\t point_idx = " << point_idx << std::endl <<
          "\t point_position = [" << point_position.x << "," <<
          point_position.y << "]\n" <<
          "point_idx out of range!\n";

        return false;
    }

    point_list[point_idx] = point_position;

    if(!update())
    {
        std::cout << "EasyPolygon2D::setPointPosition :\n" <<
          "Input :\n" <<
          "\t point_idx = " << point_idx << std::endl <<
          "\t point_position = [" << point_position.x << "," <<
          point_position.y << "]\n" <<
          "update failed!\n";

        return false;
    }

    return true;
}

bool EasyPolygon2D::isClockWise() const
{
    if(getPolygonArea() < 0)
    {
        return true;
    }

    return false;
}

bool EasyPolygon2D::setClockWise()
{
    if(!isClockWise())
    {
        std::reverse(point_list.begin(), point_list.end());
    }

    return true;
}

bool EasyPolygon2D::setAntiClockWise()
{
    if(isClockWise())
    {
        std::reverse(point_list.begin(), point_list.end());
    }

    return true;
}

float EasyPolygon2D::getPolygonArea() const
{
    if(point_list.size() < 3)
    {
        return 0;
    }

    float area = 0;
    
    for(size_t i = 0; i < point_list.size(); ++i)
    {
        const size_t next_point_idx = (i + 1) % point_list.size();

        area -= 0.5 *
          (point_list[next_point_idx].y + point_list[i].y) *
          (point_list[next_point_idx].x - point_list[i].x);
    }

    return area;
}

float EasyPolygon2D::getPolygonAreaAbs() const
{
    float polygon_area = getPolygonArea();

    return std::abs(polygon_area);
}

bool EasyPolygon2D::updateRect()
{
    if(point_list.size() == 0)
    {
        rect.setPosition(0, 0, 0, 0);
        return true;
    }

    float x_min = point_list[0].x;
    float y_min = point_list[0].y;
    float x_max = x_min;
    float y_max = y_min;

    for(const EasyPoint2D& point : point_list)
    {
        x_min = std::min(x_min, point.x);
        y_min = std::min(y_min, point.y);
        x_max = std::max(x_max, point.x);
        y_max = std::max(y_max, point.y);
    }

    rect.setPosition(x_min, y_min, x_max, y_max);

    return true;
}

bool EasyPolygon2D::updatePolygonPerimeter()
{
    perimeter = 0;

    point_length_vec.resize(point_list.size());

    if(point_list.size() == 0)
    {
        return true;
    }

    for(size_t i = 0; i < point_list.size(); ++i)
    {
        const EasyPoint2D& current_point = point_list[i];
        const EasyPoint2D& next_point = point_list[(i + 1) % point_list.size()];

        const float x_diff = next_point.x - current_point.x;
        const float y_diff = next_point.y - current_point.y;

        const float line_length2 = x_diff * x_diff + y_diff * y_diff;

        point_length_vec[i] = perimeter;

        perimeter += std::sqrt(line_length2);
    }

    return true;
}

bool EasyPolygon2D::update()
{
    if(!updateRect())
    {
        std::cout << "EasyPolygon2D::update :\n" <<
          "updateRect failed!\n";

        return false;
    }

    if(!updatePolygonPerimeter())
    {
        std::cout << "EasyPolygon2D::update :\n" <<
          "updatePolygonPerimeter failed!\n";

        return false;
    }

    return true;
}

