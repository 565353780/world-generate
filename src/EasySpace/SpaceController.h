#ifndef SPACE_CONTROLLER_H
#define SPACE_CONTROLLER_H

#include <iostream>
#include <string>

#include "EasyShape/EasyShape.h"
#include "EasySpace.h"

// for test only
#include </home/chli/OpenCV/opencv-3.4.10/build/installed/include/opencv2/opencv.hpp>

class SpaceController
{
public:
    SpaceController()
    {
    }

    bool createBoundary(
        const std::string &boundary_name);

    bool createRoom(
        const std::string &room_name);

    bool setOuterBoundary(
        const size_t &boundary_idx);

    bool setBoundaryPointVec(
        const size_t &boundary_idx,
        const std::vector<EasyPoint2D> &boundary_point_vec);

    bool addBoundaryPoint(
        const size_t &boundary_idx,
        const EasyPoint2D &boundary_point);

    bool addBoundaryPoint(
        const size_t &boundary_idx,
        const float &x,
        const float &y);

    bool setRoomSize(
        const size_t &room_idx,
        const float &width,
        const float &height);

    bool setRoomNeighboor(
        const size_t &room_idx_1,
        const size_t &room_idx_2);

    bool setRoomBoundaryPointParam(
        const size_t &room_idx,
        const size_t &boundary_idx,
        const size_t &boundary_line_idx,
        const float &boundary_line_param);

    bool updateBoundary();

    bool updateRoomConnection();

    bool updateRoom();

    bool outputRoomLineVec();

    bool outputRoomLineBoundaryPointVec();

    bool outputRoomBoundaryPointVec();

    bool showSpace();

private:
    bool getRoomLine(
        const size_t &start_room_idx,
        const size_t &current_room_idx,
        EasyRoomLine &room_line);

    bool getSortedRoomLine(
        const size_t &room_idx,
        EasyRoomLine &room_line);

    bool updateSortedRoomLineVec();

    bool updateRoomLineSize(
        EasyRoomLine &room_line);

    bool updateRoomLineVecSize();

    bool getRoomLineBoundaryPointParam(
        const EasyRoomLine &room_line,
        const EasyBoundary &boundary,
        const size_t &room_idx,
        const size_t &boundary_line_idx,
        const float &boundary_line_param,
        float &room_line_boundary_point_param);

    bool setRoomLineBoundaryPointParam(
        const size_t &room_line_idx,
        const size_t &boundary_idx,
        const size_t &boundary_line_idx,
        const float &boundary_line_param);

    bool updateRoomLineBoundaryPointPosition();

    bool updateRoomRealWidthOnRoomLine(
        const size_t &room_line_idx);

    bool updateRoomRealHeightOnRoomLine(
        const size_t &room_line_idx);

    bool updateRoomBoundaryParam(
        const size_t &room_line_idx);

    bool updateAllRoomBoundaryParam();

    bool updateRoomBoundary(
        const size_t &room_line_idx);

    bool updateAllRoomBoundary();

    bool updateRoomPosition();

    bool updateRoomBoundary();

    bool outputRoomLine(
        const EasyRoomLine &room_line);

    bool outputBoundaryPoint(
        const EasyBoundaryPoint &boundary_point);

    bool initSpaceImage();

    bool drawBoundary();

    bool drawRoomLinePosition();

    bool drawRoomPosition();

    bool drawRoomBoundary();

    bool showSpaceImage();

private:
    std::vector<EasyBoundary> boundary_vec_;

    std::vector<EasyRoom> room_vec_;
    std::vector<EasyBoundaryPoint> room_boundary_point_vec_;
    std::vector<EasyBoundaryLine> room_boundary_line_vec_;

    std::vector<EasyRoomLine> room_line_vec_;
    std::vector<EasyBoundaryPoint> room_line_boundary_point_vec_;
    std::vector<EasyBoundaryLine> room_line_boundary_line_vec_;

    cv::Mat space_image_;
    size_t x_free_;
    size_t y_free_;
    float x_min_;
    float y_min_;
};

#endif //SPACE_CONTROLLER_H
