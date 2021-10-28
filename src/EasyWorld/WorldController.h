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
        const std::string &world_name,
        const float &world_center_x,
        const float &world_center_y);

    bool createWall(
        const std::string &wall_name,
        const size_t &wall_id,
        const NodeType &wall_type);

    bool setWallAxisCenterPositionInParent(
        const size_t &wall_id,
        const NodeType &wall_type,
        const EasyPoint2D &axis_new_center_position_in_parent);

    bool setWallAxisCenterPositionInWorld(
        const size_t &wall_id,
        const NodeType &wall_type,
        const EasyPoint2D &axis_new_center_position_in_world);

    bool setWallBoundaryPolygon(
        const size_t &wall_id,
        const NodeType &wall_type,
        const EasyPolygon2D &wall_boundary_polygon);

    bool setWallBoundaryPolygonPointPosition(
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &point_idx,
        const EasyPoint2D &point_new_position_in_world);

    bool createRoomContainer(
        const std::string &roomcontainer_name,
        const size_t &roomcontainer_id,
        const NodeType &roomcontainer_type,
        const size_t &on_wall_id,
        const NodeType &on_wall_type,
        const size_t &wall_boundary_id);

    bool setRoomContainerAxisCenterPositionInParent(
        const size_t &roomcontainer_id,
        const NodeType &roomcontainer_type,
        const EasyPoint2D &axis_new_center_position_in_parent);

    bool setRoomContainerAxisCenterPositionInWorld(
        const size_t &roomcontainer_id,
        const NodeType &roomcontainer_type,
        const EasyPoint2D &axis_new_center_position_in_world);

    bool setRoomContainerBoundaryPolygon(
        const size_t &roomcontainer_id,
        const NodeType &roomcontainer_type,
        const EasyPolygon2D &roomcontainer_boundary_polygon);

    bool setRoomContainerBoundaryPolygonPointPosition(
        const size_t &roomcontainer_id,
        const NodeType &roomcontainer_type,
        const size_t &point_idx,
        const EasyPoint2D &point_new_position_in_world);

    bool createRoom(
        const std::string &room_name,
        const size_t &room_id,
        const NodeType &room_type,
        const size_t &on_roomcontainer_id,
        const NodeType &on_roomcontainer_type);

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

    bool createDoor(
        const std::string &door_name,
        const size_t &door_id,
        const NodeType &door_type,
        const size_t &on_room_id,
        const NodeType &on_room_type,
        const size_t &on_room_boundary_idx);

    bool setDoorAxisCenterPositionInParent(
        const size_t &door_id,
        const NodeType &door_type,
        const EasyPoint2D &axis_new_center_position_in_parent);

    bool setDoorAxisCenterPositionInWorld(
        const size_t &door_id,
        const NodeType &door_type,
        const EasyPoint2D &axis_new_center_position_in_world);

    bool setDoorBoundaryPolygon(
        const size_t &door_id,
        const NodeType &door_type,
        const EasyPolygon2D &door_boundary_polygon);

    bool setDoorBoundaryPolygonPointPosition(
        const size_t &door_id,
        const NodeType &door_type,
        const size_t &point_idx,
        const EasyPoint2D &point_new_position_in_world);

    bool createWindow(
        const std::string &window_name,
        const size_t &window_id,
        const NodeType &window_type,
        const size_t &on_room_id,
        const NodeType &on_room_type,
        const size_t &on_room_boundary_idx);

    bool setWindowAxisCenterPositionInParent(
        const size_t &window_id,
        const NodeType &window_type,
        const EasyPoint2D &axis_new_center_position_in_parent);

    bool setWindowAxisCenterPositionInWorld(
        const size_t &window_id,
        const NodeType &window_type,
        const EasyPoint2D &axis_new_center_position_in_world);

    bool setWindowBoundaryPolygon(
        const size_t &window_id,
        const NodeType &window_type,
        const EasyPolygon2D &window_boundary_polygon);

    bool setWindowBoundaryPolygonPointPosition(
        const size_t &window_id,
        const NodeType &window_type,
        const size_t &point_idx,
        const EasyPoint2D &point_new_position_in_world);

    bool createTeam(
        const std::string &team_name,
        const size_t &team_id,
        const NodeType &team_type,
        const size_t &on_room_id,
        const NodeType &on_room_type);

    bool setTeamAxisCenterPositionInParent(
        const size_t &team_id,
        const NodeType &team_type,
        const EasyPoint2D &axis_new_center_position_in_parent);

    bool setTeamAxisCenterPositionInWorld(
        const size_t &team_id,
        const NodeType &team_type,
        const EasyPoint2D &axis_new_center_position_in_world);

    bool setTeamBoundaryPolygon(
        const size_t &team_id,
        const NodeType &team_type,
        const EasyPolygon2D &team_boundary_polygon);

    bool setTeamBoundaryPolygonPointPosition(
        const size_t &team_id,
        const NodeType &team_type,
        const size_t &point_idx,
        const EasyPoint2D &point_new_position_in_world);

    bool createPerson(
        const std::string &person_name,
        const size_t &person_id,
        const NodeType &person_type,
        const size_t &on_team_id,
        const NodeType &on_team_type);

    bool setPersonAxisCenterPositionInParent(
        const size_t &person_id,
        const NodeType &person_type,
        const EasyPoint2D &axis_new_center_position_in_parent);

    bool setPersonAxisCenterPositionInWorld(
        const size_t &person_id,
        const NodeType &person_type,
        const EasyPoint2D &axis_new_center_position_in_world);

    bool setPersonBoundaryPolygon(
        const size_t &person_id,
        const NodeType &person_type,
        const EasyPolygon2D &person_boundary_polygon);

    bool setPersonBoundaryPolygonPointPosition(
        const size_t &person_id,
        const NodeType &person_type,
        const size_t &point_idx,
        const EasyPoint2D &point_new_position_in_world);

    bool createFurniture(
        const std::string &furniture_name,
        const size_t &furniture_id,
        const NodeType &furniture_type,
        const size_t &on_person_id,
        const NodeType &on_person_type);

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

    bool createFurnitureForPerson(
        const std::string &furniture_name,
        const size_t &person_id,
        const NodeType &person_type);

    bool createPersonForTeam(
        const std::string &person_name,
        const std::string &furniture_name,
        const size_t &team_id,
        const NodeType &team_type,
        const float &person_width,
        const float &person_height,
        const EasyAxis2D &person_axis_in_parent);

    bool createPersonGroupForTeam(
        const std::vector<std::vector<std::string>> &person_name_matrix,
        const std::vector<std::vector<std::string>> &furniture_name_matrix,
        const size_t &team_id,
        const NodeType &team_type,
        const size_t &person_x_direction_num,
        const size_t &person_y_direction_num,
        const bool &is_face_horizontal);

    bool createTeamForRoom(
        const std::string &team_name,
        const std::vector<std::vector<std::string>> &person_name_matrix,
        const std::vector<std::vector<std::string>> &furniture_name_matrix,
        const size_t &room_id,
        const NodeType &room_type,
        const float &team_width,
        const float &team_height,
        const EasyAxis2D &team_axis_in_parent,
        const size_t &person_x_direction_num,
        const size_t &person_y_direction_num,
        const bool &is_face_horizontal);

    bool createWindowForRoom(
        const std::string &window_name,
        const size_t &room_id,
        const NodeType &room_type,
        const size_t &on_room_boundary_idx,
        const float &window_width,
        const EasyAxis2D &window_axis_in_parent);

    bool createDoorForRoom(
        const std::string &door_name,
        const size_t &room_id,
        const NodeType &room_type,
        const size_t &on_room_boundary_idx,
        const float &door_width,
        const EasyAxis2D &door_axis_in_parent,
        const bool &is_handle_on_right_from_outside);

    bool createRoomForRoomContainer(
        const std::string &room_name,
        const size_t &roomcontainer_id,
        const NodeType &roomcontainer_type,
        const NodeType &room_type,
        const float &room_width,
        const float &room_height,
        const EasyAxis2D &room_axis_in_parent);

    bool createRoomGroupForRoomContainer(
        const std::vector<std::string> &room_name_vec,
        const size_t &roomcontainer_id,
        const NodeType &roomcontainer_type,
        const NodeType &room_type,
        const size_t &room_x_direction_num);

    bool createRoomContainerForWall(
        const std::string &roomcontainer_name,
        const std::vector<std::string> &room_name_vec,
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &wall_boundary_id,
        const float &roomcontainer_width,
        const float &roomcontainer_height,
        const EasyAxis2D &roomcontainer_axis_in_parent,
        const NodeType &room_type,
        const size_t &room_x_direction_num);

    bool createWallRoomContainerForWall(
        const std::string &roomcontainer_name,
        const std::vector<std::string> &room_name_vec,
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &wall_boundary_id,
        const float &roomcontainer_width,
        const float &roomcontainer_height,
        const EasyAxis2D &roomcontainer_axis_in_parent,
        const size_t &room_x_direction_num);

    bool createFreeRoomContainerForWall(
        const std::string &roomcontainer_name,
        const std::vector<std::string> &room_name_vec,
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &wall_boundary_id,
        const float &roomcontainer_width,
        const float &roomcontainer_height,
        const EasyAxis2D &roomcontainer_axis_in_parent,
        const size_t &room_x_direction_num);

    EasyNode* findNode(
        const size_t &node_id,
        const NodeType &node_type);

    bool haveThisNode(
        const size_t &node_id,
        const NodeType &node_type);

    bool getWallNodeVec(
        std::vector<EasyNode*> &wall_node_vec);

    bool getWallBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &wall_boundary_node_vec_vec);

    bool getWallSpaceNodeVec(
        std::vector<EasyNode*> &wall_space_node_vec);

    bool getRoomContainerNodeVec(
        std::vector<EasyNode*> &roomcontainer_node_vec);

    bool getRoomContainerBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &roomcontainer_boundary_node_vec_vec);

    bool getRoomContainerSpaceNodeVec(
        std::vector<EasyNode*> &roomcontainer_space_node_vec);

    bool getWallRoomNodeVec(
        std::vector<EasyNode*> &room_node_vec);

    bool getWallRoomBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &room_boundary_node_vec_vec);

    bool getWallRoomSpaceNodeVec(
        std::vector<EasyNode*> &room_space_node_vec);

    bool getFreeRoomNodeVec(
        std::vector<EasyNode*> &room_node_vec);

    bool getFreeRoomBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &room_boundary_node_vec_vec);

    bool getFreeRoomSpaceNodeVec(
        std::vector<EasyNode*> &room_space_node_vec);

    bool getDoorNodeVec(
        std::vector<EasyNode*> &door_node_vec);

    bool getDoorBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &door_boundary_node_vec_vec);

    bool getDoorSpaceNodeVec(
        std::vector<EasyNode*> &door_space_node_vec);

    bool getWindowNodeVec(
        std::vector<EasyNode*> &window_node_vec);

    bool getWindowBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &window_boundary_node_vec_vec);

    bool getWindowSpaceNodeVec(
        std::vector<EasyNode*> &window_space_node_vec);

    bool getTeamNodeVec(
        std::vector<EasyNode*> &team_node_vec);

    bool getTeamBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &team_boundary_node_vec_vec);

    bool getTeamSpaceNodeVec(
        std::vector<EasyNode*> &team_space_node_vec);

    bool getPersonNodeVec(
        std::vector<EasyNode*> &person_node_vec);

    bool getPersonBoundaryNodeVecVec(
        std::vector<std::vector<EasyNode*>> &person_boundary_node_vec_vec);

    bool getPersonSpaceNodeVec(
        std::vector<EasyNode*> &person_space_node_vec);

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
    std::vector<std::pair<size_t, NodeType>> roomcontainer_pair_vec_;
    std::vector<std::pair<size_t, NodeType>> room_pair_vec_;
    std::vector<std::pair<size_t, NodeType>> door_pair_vec_;
    std::vector<std::pair<size_t, NodeType>> window_pair_vec_;
    std::vector<std::pair<size_t, NodeType>> team_pair_vec_;
    std::vector<std::pair<size_t, NodeType>> person_pair_vec_;
    std::vector<std::pair<size_t, NodeType>> furniture_pair_vec_;
};

#endif //WORLD_CONTROLLER_H
