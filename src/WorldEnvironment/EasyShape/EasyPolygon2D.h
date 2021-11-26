#ifndef EASYPOLYGON_H
#define EASYPOLYGON_H

#include "export_library_global.h"
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <cmath>

#include "EasyPoint2D.h"
#include "EasyRect2D.h"
#include "EasyLine2D.h"
#include "EasyIntersection2D.h"

class LIBRARY_EXPORT EasyPolygon2D
{
public:
    EasyPolygon2D()
    {
    }

    bool reset();

    bool setID(
        const int &id_data);

    bool addPoint(
        const EasyPoint2D &point_2d);

    bool addPoint(
        const float &x,
        const float &y);

    bool insertPoint(
        const EasyPoint2D &point_2d,
        const size_t &insert_idx1);

    bool removePoint(
        const size_t &remove_idx);

    bool setPointPosition(
        const size_t& point_idx,
        const EasyPoint2D& point_position);

    bool isClockWise() const;

    bool setClockWise();

    bool setAntiClockWise();

    float getPolygonArea() const;

    float getPolygonAreaAbs() const;

private:
    bool updateRect();

    bool updatePolygonPerimeter();

    bool update();

public:
    float perimeter;

    std::vector<EasyPoint2D> point_list;

    EasyRect2D rect;

private:
    std::vector<float> point_length_vec;
};

#endif //EASYPOLYGON_H
