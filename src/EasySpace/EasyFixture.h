#ifndef EASY_FIXTURE_H
#define EASY_FIXTURE_H

#include <iostream>
#include <string>
#include <cmath>

#include "EasyShape/EasyPoint2D.h"
#include "EasyShape/EasyPolygon2D.h"

class EasyFixture
{
public:
    EasyFixture()
    {
        reset();
    }

    bool reset();

    bool setSize(
        const float &target_width,
        const float &target_height);

    bool setPeopleNum(
        const size_t &target_people_num);

    bool setDirection(
        const EasyPoint2D &target_direction);

    bool generateFixture();

    bool is_size_valid;
    float width;
    float height;

    bool is_direction_valid;
    EasyPoint2D direction;
};

#endif //EASY_FIXTURE_H
