#ifndef UNIT_WORLD_ENVIRONMENT_H
#define UNIT_WORLD_ENVIRONMENT_H

#include "export_library_global.h"

#include "UnitWorldController.h"
#include "UnitWorldTransformer.h"

#if defined(EXPORT_PYBIND)
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#endif

class EasyNodeInfo
{
public:
    EasyNodeInfo()
    {
    }

    std::string name;
    size_t id;
    NodeType type;
    EasyPolygon2D boundary_polygon;
};

class LIBRARY_EXPORT UnitWorldEnvironment
{
public:
    UnitWorldEnvironment()
    {
    }

    bool reset();
    bool resetButRemainWall();

    bool setImageSize(
        const size_t& image_width,
        const size_t& image_height,
        const size_t& free_area_width);

    bool createNewWorld();

    bool createOuterWall();
    bool createInnerWall();

    bool addPointForOuterWall(
        const size_t& outerwall_idx,
        const float& point_x,
        const float& point_y);
    bool addPointForInnerWall(
        const size_t& innerwall_idx,
        const float& point_x,
        const float& point_y);

    bool generateWall();

    bool placeWallRoomByPosition(
        const size_t& point_x_in_image,
        const size_t& point_y_in_image);

    bool setWallRoomPositionByPosition(
        const size_t& wall_room_idx,
        const size_t& point_x_in_image,
        const size_t& point_y_in_image);

private:
    std::vector<std::vector<std::vector<size_t>>> getNodeBoundaryDataVec(
        const std::vector<EasyNodeInfo>& node_info_vec);

public:
    std::vector<std::vector<std::vector<size_t>>> getOuterWallBoundaryDataVec();
    std::vector<std::vector<std::vector<size_t>>> getInnerWallBoundaryDataVec();
    std::vector<std::vector<std::vector<size_t>>> getWallRoomBoundaryDataVec();

// private:
    UnitWorldController unit_world_controller_;
    UnitWorldTransformer unit_world_transformer_;

    std::vector<EasyNodeInfo> outer_wall_info_vec_;
    std::vector<EasyNodeInfo> inner_wall_info_vec_;
    std::vector<EasyNodeInfo> wall_room_info_vec_;
};

#if defined(EXPORT_PYBIND)
PYBIND11_MODULE(UnitWorldEnvironment, m)
{
    pybind11::class_<UnitWorldEnvironment>(m, "UnitWorldEnvironment")
        .def(pybind11::init())
        .def("reset", &UnitWorldEnvironment::reset)
        .def("resetButRemainWall", &UnitWorldEnvironment::resetButRemainWall)
        .def("setImageSize", &UnitWorldEnvironment::setImageSize)
        .def("createNewWorld", &UnitWorldEnvironment::createNewWorld)
        .def("createOuterWall", &UnitWorldEnvironment::createOuterWall)
        .def("createInnerWall", &UnitWorldEnvironment::createInnerWall)
        .def("addPointForOuterWall", &UnitWorldEnvironment::addPointForOuterWall)
        .def("addPointForInnerWall", &UnitWorldEnvironment::addPointForInnerWall)
        .def("generateWall", &UnitWorldEnvironment::generateWall)
        .def("placeWallRoomByPosition", &UnitWorldEnvironment::placeWallRoomByPosition)
        .def("setWallRoomPositionByPosition", &UnitWorldEnvironment::setWallRoomPositionByPosition)
        .def("getOuterWallBoundaryDataVec", &UnitWorldEnvironment::getOuterWallBoundaryDataVec)
        .def("getInnerWallBoundaryDataVec", &UnitWorldEnvironment::getInnerWallBoundaryDataVec)
        .def("getWallRoomBoundaryDataVec", &UnitWorldEnvironment::getWallRoomBoundaryDataVec);
}
#endif

#endif // UNIT_WORLD_ENVIRONMENT_H
