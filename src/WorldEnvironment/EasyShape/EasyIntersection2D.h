#ifndef EASYINTERSECTION_2D
#define EASYINTERSECTION_2D

#include "export_library_global.h"

#include <vector>

#include "EasyPoint2D.h"

class LIBRARY_EXPORT EasyIntersection2D
{
public:
    EasyIntersection2D()
    {
    }

    bool setPosition(
        const float &position_x,
        const float &position_y);
    bool setPosition(
        const EasyPoint2D &point_data);

    bool haveThisPointIdx(
        const size_t &polygon_idx,
        const size_t &point_idx) const;

    bool addPolygonPointIdx(
        const size_t &polygon_idx,
        const size_t &point_idx);

    EasyPoint2D getPoint()
    {
        return point;
    }

    EasyPoint2D point;
    // std::vector<std::pair<polygon_idx, std::vector<polygon_intersection_line_idx>>>
    std::vector<std::pair<size_t, std::vector<size_t>>> polygon_point_idx_vec_pair_vec;
};

#endif //EASYINTERSECTION_2D
