#ifndef EASYPOLYGON_H
#define EASYPOLYGON_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <cmath>

#include "EasyPoint2D.h"
#include "EasyRect2D.h"
#include "EasyLine2D.h"
#include "EasyIntersection2D.h"

class EasyPolygon2D
{
public:
    EasyPolygon2D()
    {
    }

    bool reset();

    bool setID(
        const int &id_data);

    bool updateRect(
        const EasyPoint2D &new_point);

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

    bool isClockWise();

    bool setClockWise();

    bool setAntiClockWise();

    float getPolygonArea();

    bool getPolygonRect(
        EasyRect2D &rect_2d);

    std::vector<EasyPoint2D> point_list;

    EasyRect2D rect;
};

#endif //EASYPOLYGON_H
