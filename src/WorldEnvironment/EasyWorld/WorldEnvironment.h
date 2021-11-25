#ifndef WORLD_ENVIRONMENT_H
#define WORLD_ENVIRONMENT_H

#include "export_library_global.h"

#include "EasyWorld/WallGenerator.h"
#include "EasyWorld/WorldPlaceGenerator.h"
#include "EasyWorld/WorldObservation.h"
#include "EasyWorld/WorldReward.h"
#include "EasyWorld/WorldEditor.h"

#if defined(EXPORT_PYBIND)
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#endif

class LIBRARY_EXPORT WorldEnvironment
{
public:
    WorldEnvironment()
    {
    }

    bool reset();
    bool resetButRemainWall();

    bool createNewWorld(
        const float& world_center_x,
        const float& world_center_y);

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

    bool placeOuterWallRoomContainer(
        const size_t &wall_id,
        const size_t &boundary_idx,
        const float &roomcontainer_start_position,
        const float &roomcontainer_width,
        const float &roomcontainer_height,
        const size_t &room_num);
    bool placeInnerWallRoomContainer(
        const size_t &wall_id,
        const size_t &boundary_idx,
        const float &roomcontainer_start_position,
        const float &roomcontainer_width,
        const float &roomcontainer_height,
        const size_t &room_num);

    bool generateFreeRoomContainer(
        const size_t &team_x_direction_person_num,
        const size_t &team_y_direction_person_num,
        const float &team_dist,
        const float &person_edge);

    bool setWallRoomContainerPosition(
        const size_t &wall_roomcontainer_id,
        const float &new_position_x,
        const float &new_position_y,
        const float &mouse_pos_x_direction_delta);

    std::vector<std::vector<float>> getOuterWallBoundaryXYDataVec();
    std::vector<std::vector<float>> getInnerWallBoundaryXYDataVec();
    std::vector<std::vector<float>> getRoomContainerBoundaryXYDataVec();
    std::vector<std::vector<float>> getWallRoomBoundaryXYDataVec();
    std::vector<std::vector<float>> getFreeRoomBoundaryXYDataVec();
    std::vector<std::vector<float>> getDoorBoundaryXYDataVec();
    std::vector<std::vector<float>> getWindowBoundaryXYDataVec();
    std::vector<std::vector<float>> getTeamBoundaryXYDataVec();
    std::vector<std::vector<float>> getPersonBoundaryXYDataVec();
    std::vector<std::vector<float>> getFurnitureBoundaryXYDataVec();


    WallGenerator wall_generator_;
    WorldController world_controller_;
    WorldPlaceGenerator world_place_generator_;
    WorldObservation world_observation_;
    WorldReward world_reward_;
    WorldEditor world_editor_;
};

#if defined(EXPORT_PYBIND)
PYBIND11_MODULE(WorldEnvironment, m)
{
    pybind11::class_<WorldEnvironment>(m, "WorldEnvironment")
        .def(pybind11::init())
        .def("reset", &WorldEnvironment::reset)
        .def("resetButRemainWall", &WorldEnvironment::resetButRemainWall)
        .def("createNewWorld", &WorldEnvironment::createNewWorld)
        .def("createOuterWall", &WorldEnvironment::createOuterWall)
        .def("createInnerWall", &WorldEnvironment::createInnerWall)
        .def("addPointForOuterWall", &WorldEnvironment::addPointForOuterWall)
        .def("addPointForInnerWall", &WorldEnvironment::addPointForInnerWall)
        .def("generateWall", &WorldEnvironment::generateWall)
        .def("placeOuterWallRoomContainer", &WorldEnvironment::placeOuterWallRoomContainer)
        .def("placeInnerWallRoomContainer", &WorldEnvironment::placeInnerWallRoomContainer)
        .def("generateFreeRoomContainer", &WorldEnvironment::generateFreeRoomContainer)
        .def("setWallRoomContainerPosition", &WorldEnvironment::setWallRoomContainerPosition)
        .def("getOuterWallBoundaryXYDataVec", &WorldEnvironment::getOuterWallBoundaryXYDataVec)
        .def("getInnerWallBoundaryXYDataVec", &WorldEnvironment::getInnerWallBoundaryXYDataVec)
        .def("getRoomContainerBoundaryXYDataVec", &WorldEnvironment::getRoomContainerBoundaryXYDataVec)
        .def("getWallRoomBoundaryXYDataVec", &WorldEnvironment::getWallRoomBoundaryXYDataVec)
        .def("getFreeRoomBoundaryXYDataVec", &WorldEnvironment::getFreeRoomBoundaryXYDataVec)
        .def("getDoorBoundaryXYDataVec", &WorldEnvironment::getDoorBoundaryXYDataVec)
        .def("getWindowBoundaryXYDataVec", &WorldEnvironment::getWindowBoundaryXYDataVec)
        .def("getTeamBoundaryXYDataVec", &WorldEnvironment::getTeamBoundaryXYDataVec)
        .def("getPersonBoundaryXYDataVec", &WorldEnvironment::getPersonBoundaryXYDataVec)
        .def("getFurnitureBoundaryXYDataVec", &WorldEnvironment::getFurnitureBoundaryXYDataVec);
}
#endif

#endif //WORLD_ENVIRONMENT_H
