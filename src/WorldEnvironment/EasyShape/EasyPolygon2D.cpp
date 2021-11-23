#include "EasyPolygon2D.h"
#include <limits>

bool EasyPolygon2D::reset()
{
    point_list.clear();

    return true;
}

bool EasyPolygon2D::updateRect(
    const EasyPoint2D &new_point)
{
    if(point_list.size() == 1)
    {
        rect.setPosition(new_point.x, new_point.y, new_point.x, new_point.y);

        return true;
    }

    float x_min = std::fmin(new_point.x, rect.x_min);
    float x_max = std::fmax(new_point.x, rect.x_max);
    float y_min = std::fmin(new_point.y, rect.y_min);
    float y_max = std::fmax(new_point.y, rect.y_max);

    rect.setPosition(x_min, y_min, x_max, y_max);

    return true;
}

bool EasyPolygon2D::addPoint(
    const EasyPoint2D &point_2d)
{
    point_list.emplace_back(point_2d);

    updateRect(point_2d);

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
    const EasyPoint2D &point_2d,
    const size_t &insert_idx)
{
    if(insert_idx > point_list.size() - 1)
    {
        std::cout << "insert point to polygon failed!" << std::endl;
        return false;
    }

    point_list.insert(point_list.begin() + insert_idx, point_2d);

    updateRect(point_2d);

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

    float x_min = std::numeric_limits<float>::max();
    float x_max = std::numeric_limits<float>::min();
    float y_min = std::numeric_limits<float>::max();
    float y_max = std::numeric_limits<float>::min();

    for(const EasyPoint2D &point : point_list)
    {
        x_min = std::fmin(x_min, point.x);
        x_max = std::fmax(x_max, point.x);
        y_min = std::fmin(y_min, point.y);
        y_max = std::fmax(y_max, point.y);
    }

    rect.setPosition(x_min, y_min, x_max, y_max);

    return true;
}

bool EasyPolygon2D::isClockWise()
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

float EasyPolygon2D::getPolygonArea()
{
    if(point_list.size() < 3)
    {
        return 0;
    }

    float area = 0;
    
    for(size_t i = 0; i < point_list.size(); ++i)
    {
        int next_point_idx = i + 1;
        if(i == point_list.size() - 1)
        {
            next_point_idx = 0;
        }

        area -= 0.5 *
          (point_list[next_point_idx].y + point_list[i].y) *
          (point_list[next_point_idx].x - point_list[i].x);
    }

    return area;
}

bool EasyPolygon2D::getPolygonRect(
    EasyRect2D &rect_2d)
{
    if(point_list.size() == 0)
    {
        std::cout << "EasyPolygon2D::getPolygonRect : no point found!" << std::endl;
        return false;
    }

    rect_2d.x_min = point_list[0].x;
    rect_2d.x_max = rect_2d.x_min;
    rect_2d.y_min = point_list[0].y;
    rect_2d.y_max = rect_2d.y_min;

    for(const EasyPoint2D &point : point_list)
    {
        rect_2d.x_min = fmin(rect_2d.x_min, point.x);
        rect_2d.x_max = fmax(rect_2d.x_max, point.x);
        rect_2d.y_min = fmin(rect_2d.y_min, point.y);
        rect_2d.y_max = fmax(rect_2d.y_max, point.y);
    }

    return true;
}

