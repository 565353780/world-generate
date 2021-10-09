#ifndef WORLD_CONTROLLER_H
#define WORLD_CONTROLLER_H

#include <iostream>
#include <string>

#include "EasyTree.h"

class WorldController
{
public:
    WorldController() {}

    bool reset();

    bool createWorld(
        const float &world_center_x,
        const float &world_center_y);

    bool createWall(
        const size_t &wall_id,
        const NodeType &wall_type);

    bool setWallBoundaryPolygon(
        const size_t &wall_id,
        const NodeType &wall_type,
        const EasyPolygon2D &wall_boundary_polygon);

    bool setWallBoundaryPolygonPointPosition(
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &point_idx,
        const EasyPoint2D &point_new_position_in_world);

    bool createRoom(
        const size_t &room_id,
        const NodeType &room_type,
        const size_t &on_wall_id,
        const NodeType &on_wall_type,
        const size_t &wall_boundary_id);

    bool setRoomAxisCenterPositionInParent(
        const size_t &room_id,
        const NodeType &room_type,
        const EasyPoint2D &axis_new_center_position_in_parent);

    bool setRoomAxisCenterPositionInWorld(
        const size_t &room_id,
        const NodeType &room_type,
        const EasyPoint2D &axis_new_center_position_in_world);

    bool setRoomBoundaryPolygon(
        const size_t &room_id,
        const NodeType &room_type,
        const EasyPolygon2D &room_boundary_polygon);

    bool setRoomBoundaryPolygonPointPosition(
        const size_t &room_id,
        const NodeType &room_type,
        const size_t &point_idx,
        const EasyPoint2D &point_new_position_in_world);

    bool createFurniture(
        const size_t &furniture_id,
        const NodeType &furniture_type,
        const size_t &on_room_id,
        const NodeType &on_room_type);

    bool setFurnitureAxisCenterPositionInParent(
        const size_t &furniture_id,
        const NodeType &furniture_type,
        const EasyPoint2D &axis_new_center_position_in_parent);

    bool setFurnitureAxisCenterPositionInWorld(
        const size_t &furniture_id,
        const NodeType &furniture_type,
        const EasyPoint2D &axis_new_center_position_in_world);

    bool setFurnitureBoundaryPolygon(
        const size_t &furniture_id,
        const NodeType &furniture_type,
        const EasyPolygon2D &furniture_boundary_polygon);

    bool setFurnitureBoundaryPolygonPointPosition(
        const size_t &furniture_id,
        const NodeType &furniture_type,
        const size_t &point_idx,
        const EasyPoint2D &point_new_position_in_world);

    EasyNode* findNode(
        const size_t &node_id,
        const NodeType &node_type);

    bool getWallNodeVec(
        std::vector<EasyNode*> &wall_node_vec);

    bool getWallBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &wall_boundary_node_vec_vec);

    bool getWallSpaceNodeVec(
        std::vector<EasyNode*> &wall_space_node_vec);

    bool getRoomNodeVec(
        std::vector<EasyNode*> &room_node_vec);

    bool getRoomBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &room_boundary_node_vec_vec);

    bool getRoomSpaceNodeVec(
        std::vector<EasyNode*> &room_space_node_vec);

    bool getFurnitureNodeVec(
        std::vector<EasyNode*> &furniture_node_vec);

    bool getFurnitureBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &furniture_boundary_node_vec_vec);

    bool getFurnitureSpaceNodeVec(
        std::vector<EasyNode*> &furniture_space_node_vec);

    bool outputInfo();

private:
    EasyTree world_tree_;

    std::vector<std::pair<size_t, NodeType>> wall_pair_vec_;
    std::vector<std::pair<size_t, NodeType>> room_pair_vec_;
    std::vector<std::pair<size_t, NodeType>> furniture_pair_vec_;
};

#endif //WORLD_CONTROLLER_H
