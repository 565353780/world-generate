#ifndef EASYLINE2D_H
#define EASYLINE2D_H

#include "export_library_global.h"

#include "EasyPoint2D.h"
#include "EasyRect2D.h"

class LIBRARY_EXPORT EasyLine2D
{
public:
    EasyLine2D()
    {
    }

    bool setPosition(
        const float &position_x_1,
        const float &position_y_1,
        const float &position_x_2,
        const float &position_y_2);

    bool setPosition(
        const EasyPoint2D &point_1_data,
        const EasyPoint2D &point_2_data);

    bool outputInfo(
        const size_t& info_level);

    EasyPoint2D point_1;
    EasyPoint2D point_2;

    EasyRect2D rect;

    float x_diff;
    float y_diff;
};

#endif // EASYLINE2D_H
