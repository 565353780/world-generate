#ifndef EASY_COMPUTATION_H
#define EASY_COMPUTATION_H

#include <iostream>
#include <limits.h>

#include "EasyPoint2D.h"
#include "EasyRect2D.h"
#include "EasyLine2D.h"
#include "EasyIntersection2D.h"
#include "EasyPolygon2D.h"

enum PointState
{
    PointOutside = 0,
    PointOnVertex = 1,
    PointOnEdge = 2,
    PointInside = 3
};

enum LineState
{
    LineOutside = 0,
    LineCrossVertex = 1,
    LineCrossEdge = 2,
    LineInside = 3
};

enum CrossState
{
    NoCross = 0,
    SameVertex = 1,
    SameEdge = 2,
    Cross = 3
};

class EasyComputation
{
public:
    EasyComputation()
    {
    }

    static float dot(
        const float &x_1,
        const float &y_1,
        const float &x_2,
        const float &y_2);

    static float dot(
        const EasyLine2D &line_1,
        const EasyLine2D &line_2);

    static float cross(
        const float &x_1,
        const float &y_1,
        const float &x_2,
        const float &y_2);

    static float cross(
        const EasyLine2D &line_1,
        const EasyLine2D &line_2);

    static float pointDist2(
        const EasyPoint2D &point_1,
        const EasyPoint2D &point_2);

    static float pointDist(
        const EasyPoint2D &point_1,
        const EasyPoint2D &point_2);

    static float getPointDistToRect(
        const EasyPoint2D &point,
        const EasyRect2D &rect);

    static float lineLength2(
        const EasyLine2D &line);

    static float lineLength(
        const EasyLine2D &line);

    static float angle(
        const EasyLine2D &line_1,
        const EasyLine2D &line_2);

    static float getClockWiseAngle(
        const EasyLine2D &line_1,
        const EasyLine2D &line_2);

    static float getAntiClockWiseAngle(
        const EasyLine2D &line_1,
        const EasyLine2D &line_2);

    static bool isSamePoint(
        const EasyPoint2D &point_1,
        const EasyPoint2D &point_2);

    static bool isPointInRect(
        const EasyPoint2D &point,
        const EasyRect2D &rect);

    static bool isPointInLineRect(
        const EasyPoint2D &point,
        const EasyLine2D &line);

    static bool isRectCross(
        const EasyLine2D &line_1,
        const EasyLine2D &line_2);

    static bool isRectCross(
        const EasyRect2D &rect_1,
        const EasyRect2D &rect_2);

    static bool isLineCross(
        const EasyLine2D &line_1,
        const EasyLine2D &line_2);

    static bool isLineParallel(
        const EasyLine2D &line_1,
        const EasyLine2D &line_2);

    static bool isPointOnOpenBoundedLine(
        const EasyPoint2D &point,
        const EasyLine2D &line);

    static int isPointInPolygon(
        const EasyPoint2D &point,
        const EasyPolygon2D &polygon);

    static bool isPolygonCross(
        EasyPolygon2D &polygon_1,
        EasyPolygon2D &polygon_2);

    static PointState getPointStateOfLine(
        const EasyPoint2D &point,
        const EasyLine2D &line);

    static PointState getPointStateOfPolygon(
        const EasyPoint2D &point,
        const EasyPolygon2D &polygon);

    static LineState getLineStateOfLine(
        const EasyLine2D &line_1,
        const EasyLine2D &line_2);

    static LineState getLineStateOfPolygon(
        const EasyLine2D &line,
        const EasyPolygon2D &polygon);

    static bool getLineCrossPoint(
        const EasyLine2D &line_1,
        const EasyLine2D &line_2,
        EasyPoint2D &line_cross_point);

    static bool getBoundedLineCrossPointVec(
        const EasyLine2D &line_1,
        const EasyLine2D &line_2,
        std::vector<EasyPoint2D> &line_cross_point_vec);

    static bool getPolygonIntersection(
        std::vector<EasyPolygon2D> &polygon_vec,
        std::vector<EasyIntersection2D> &intersection_vec);

    static bool getSortedIntersectionOnPolygonLine(
        const EasyPolygon2D &polygon,
        const std::vector<EasyIntersection2D> &intersection_vec,
        const size_t &polygon_idx,
        const size_t &point_idx,
        std::vector<size_t> &sorted_intersection_idx_on_polygon_line_vec);

    static bool getSplitPolygonAndIntersectionPosition(
        const EasyPolygon2D &polygon,
        const std::vector<EasyIntersection2D> &intersection_vec,
        const size_t &polygon_idx,
        EasyPolygon2D &split_polygon,
        std::vector<std::pair<size_t, size_t>> &intersection_idx_polygon_point_idx_pair_vec);

    static bool splitPolygonsByIntersection(
        const std::vector<EasyIntersection2D> &intersection_vec,
        const std::vector<EasyPolygon2D> &polygon_vec,
        std::vector<EasyIntersection2D> &split_intersection_vec,
        std::vector<EasyPolygon2D> &split_polygon_vec);

    static bool getIntersectionIdxOnPolygonPoint(
        const std::vector<EasyPolygon2D> &polygon_vec,
        const std::vector<EasyIntersection2D> &intersection_vec,
        const size_t &polygon_idx,
        const size_t &point_idx,
        size_t &intersection_idx);

    static bool updatePolygonIntersectionPointConnectedState(
        const EasyIntersection2D &intersection,
        std::vector<std::vector<bool>> &polygon_point_connected_vec_vec);

    static bool updatePolygonNotIntersectionPointConnectedState(
        const std::vector<EasyPolygon2D> &polygon_vec,
        const EasyPolygon2D &union_polygon,
        std::vector<std::vector<bool>> &polygon_point_connected_vec_vec);

    static bool addNewPolygonPoint(
        const std::vector<EasyPolygon2D> &polygon_vec,
        const size_t &polygon_idx,
        const size_t &start_point_idx,
        EasyPolygon2D &union_polygon,
        std::vector<std::vector<bool>> &polygon_point_connected_vec_vec);

    static bool getMinimalAnglePolygonPointIdx(
        const std::vector<EasyPolygon2D> &polygon_vec,
        const std::vector<EasyIntersection2D> &intersection_vec,
        const size_t &polygon_idx,
        const size_t &start_point_idx,
        const size_t &start_intersection_idx,
        std::pair<size_t, size_t> &minimal_angle_polygon_point_idx);

    bool getUnionPolygonPoints(
        const std::vector<EasyPolygon2D> &polygon_vec,
        const std::vector<EasyIntersection2D> &intersection_vec,
        const size_t &start_polygon_idx,
        const size_t &start_point_idx,
        const size_t &current_start_polygon_idx,
        const size_t &current_start_point_idx,
        EasyPolygon2D &union_polygon,
        std::vector<std::vector<bool>> &polygon_point_connected_vec_vec);

    bool getUnionPolygonVec(
        std::vector<EasyPolygon2D> &polygon_vec,
        std::vector<EasyPolygon2D> &union_polygon_vec);

private:
    size_t connected_polygon_point_num_=0;
};

#endif //EASY_COMPUTATION_H
