#ifndef WORLD_OBSERVATION_H
#define WORLD_OBSERVATION_H

#include "EasyWorld/WorldController.h"

class WorldObservation
{
public:
    WorldObservation()
    {
    }

    bool reset();

    bool getObservation(
        WorldController& world_controller);

    bool getWallBoundaryPolygon(
        WorldController& world_controller);

    bool getRoomContainerBoundaryPolygon(
        WorldController& world_controller);

    bool getWallRoomBoundaryPolygon(
        WorldController& world_controller);

    bool getFreeRoomBoundaryPolygon(
        WorldController& world_controller);

    bool getDoorBoundaryPolygon(
        WorldController& world_controller);

    bool getWindowBoundaryPolygon(
        WorldController& world_controller);

    bool getTeamBoundaryPolygon(
        WorldController& world_controller);

    bool getPersonBoundaryPolygon(
        WorldController& world_controller);

    bool getFurnitureBoundaryPolygon(
        WorldController& world_controller);

    std::vector<EasyPolygon2D> wall_boundary_polygon_vec_;
    std::vector<EasyPolygon2D> roomcontainer_boundary_polygon_vec_;
    std::vector<EasyPolygon2D> wallroom_boundary_polygon_vec_;
    std::vector<EasyPolygon2D> freeroom_boundary_polygon_vec_;
    std::vector<EasyPolygon2D> door_boundary_polygon_vec_;
    std::vector<EasyPolygon2D> window_boundary_polygon_vec_;
    std::vector<EasyPolygon2D> team_boundary_polygon_vec_;
    std::vector<EasyPolygon2D> person_boundary_polygon_vec_;
    std::vector<EasyPolygon2D> furniture_boundary_polygon_vec_;
};

#endif //WORLD_OBSERVATION_H
