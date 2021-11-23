#include "WorldController.h"
#include <utility>

bool WorldController::reset()
{
    if(!world_tree_.reset())
    {
        std::cout << "WorldController::reset : " << std::endl <<
          "reset world_tree_ failed!" << std::endl;

        return false;
    }

    wall_pair_vec_.clear();
    roomcontainer_pair_vec_.clear();
    room_pair_vec_.clear();
    door_pair_vec_.clear();
    window_pair_vec_.clear();
    team_pair_vec_.clear();
    person_pair_vec_.clear();
    furniture_pair_vec_.clear();

    return true;
}

bool WorldController::resetButRemainWall()
{
    if(!world_tree_.resetButRemainWall())
    {
        std::cout << "WorldController::resetButRemainWall : " << std::endl <<
          "resetButRemainWall failed!" << std::endl;

        return false;
    }

    roomcontainer_pair_vec_.clear();
    room_pair_vec_.clear();
    door_pair_vec_.clear();
    window_pair_vec_.clear();
    team_pair_vec_.clear();
    person_pair_vec_.clear();
    furniture_pair_vec_.clear();

    return true;
}

bool WorldController::createWorld(
    const std::string &world_name,
    const float &world_center_x,
    const float &world_center_y)
{
    if(!world_tree_.createWorld(world_name, world_center_x, world_center_y))
    {
        std::cout << "WorldController::createWorld : " << std::endl <<
          "Input :\n" <<
          "\tworld_name = " << world_name << std::endl <<
          "\tworld_center = [" << world_center_x << "," <<
          world_center_y << "]" << std::endl <<
          "createWorld failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createWall(
    const std::string &wall_name,
    const size_t &wall_id,
    const NodeType &wall_type)
{
    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "WorldController::createWall : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "this type is not the wall type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          wall_name, wall_id, wall_type, 0, NodeType::World, 0))
    {
        std::cout << "WorldController::createWall : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "createNode for wall failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_wall_pair;
    new_wall_pair.first = wall_id;
    new_wall_pair.second = wall_type;

    wall_pair_vec_.emplace_back(new_wall_pair);

    return true;
}

bool WorldController::setWallAxisCenterPositionInParent(
    const size_t &wall_id,
    const NodeType &wall_type,
    const EasyPoint2D &axis_new_center_position_in_parent)
{
    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "WorldController::setWallAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "this type is not the wall type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInParent(
          wall_id,
          wall_type,
          axis_new_center_position_in_parent,
          true,
          true,
          true))
    {
        std::cout << "WorldController::setWallAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this wall node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setWallAxisCenterPositionInWorld(
    const size_t &wall_id,
    const NodeType &wall_type,
    const EasyPoint2D &axis_new_center_position_in_world)
{
    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "WorldController::setWallAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "this type is not the wall type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInWorld(
          wall_id,
          wall_type,
          axis_new_center_position_in_world,
          true,
          true,
          false))
    {
        std::cout << "WorldController::setWallAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this wall node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setWallBoundaryPolygon(
    const size_t &wall_id,
    const NodeType &wall_type,
    const EasyPolygon2D &wall_boundary_polygon)
{
    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "WorldController::setWallBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "this type is not the wall type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygon(wall_id, wall_type, wall_boundary_polygon))
    {
        std::cout << "WorldController::setWallBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "setNodeBoundaryPolygon for wall failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setWallBoundaryPolygonPointPosition(
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &point_idx,
    const EasyPoint2D &point_new_position_in_world)
{
    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "WorldController::setWallBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "this type is not the wall type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygonPointPosition(
          wall_id, wall_type, point_idx, point_new_position_in_world))
    {
        std::cout << "WorldController::setWallBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setNodeBoundaryPolygonPointPosition for wall failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createRoomContainer(
    const std::string &roomcontainer_name,
    const size_t &roomcontainer_id,
    const NodeType &roomcontainer_type,
    const size_t &on_wall_id,
    const NodeType &on_wall_type,
    const size_t &wall_boundary_id)
{
    if(roomcontainer_type != NodeType::RoomContainer)
    {
        std::cout << "WorldController::createRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\ton_wall_id = " << on_wall_id << std::endl <<
          "\ton_wall_type = " << on_wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "this type is not the roomcontainer type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          roomcontainer_name, roomcontainer_id, roomcontainer_type, on_wall_id, on_wall_type, wall_boundary_id))
    {
        std::cout << "WorldController::createRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\ton_wall_id = " << on_wall_id << std::endl <<
          "\ton_wall_type = " << on_wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "createNode for roomcontainer failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_roomcontainer_pair;
    new_roomcontainer_pair.first = roomcontainer_id;
    new_roomcontainer_pair.second = roomcontainer_type;

    roomcontainer_pair_vec_.emplace_back(new_roomcontainer_pair);

    return true;
}

bool WorldController::setRoomContainerAxisCenterPositionInParent(
    const size_t &roomcontainer_id,
    const NodeType &roomcontainer_type,
    const EasyPoint2D &axis_new_center_position_in_parent)
{
    if(roomcontainer_type != NodeType::RoomContainer)
    {
        std::cout << "WorldController::setRoomContainerAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "this type is not the roomcontainer type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInParent(
          roomcontainer_id,
          roomcontainer_type,
          axis_new_center_position_in_parent,
          true,
          true,
          true))
    {
        std::cout << "WorldController::setRoomContainerAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this roomcontainer node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setRoomContainerAxisCenterPositionInWorld(
    const size_t &roomcontainer_id,
    const NodeType &roomcontainer_type,
    const EasyPoint2D &axis_new_center_position_in_world)
{
    if(roomcontainer_type != NodeType::RoomContainer)
    {
        std::cout << "WorldController::setRoomContainerAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "this type is not the roomcontainer type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInWorld(
          roomcontainer_id,
          roomcontainer_type,
          axis_new_center_position_in_world,
          true,
          false,
          false))
    {
        std::cout << "WorldController::setRoomContainerAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this roomcontainer node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setRoomContainerBoundaryPolygon(
    const size_t &roomcontainer_id,
    const NodeType &roomcontainer_type,
    const EasyPolygon2D &roomcontainer_boundary_polygon)
{
    if(roomcontainer_type != NodeType::RoomContainer)
    {
        std::cout << "WorldController::setRoomContainerBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "this type is not the roomcontainer type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygon(roomcontainer_id, roomcontainer_type, roomcontainer_boundary_polygon))
    {
        std::cout << "WorldController::setRoomContainerBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "setNodeBoundaryPolygon for roomcontainer failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setRoomContainerBoundaryPolygonPointPosition(
    const size_t &roomcontainer_id,
    const NodeType &roomcontainer_type,
    const size_t &point_idx,
    const EasyPoint2D &point_new_position_in_world)
{
    if(roomcontainer_type != NodeType::RoomContainer)
    {
        std::cout << "WorldController::setRoomContainerBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "this type is not the roomcontainer type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygonPointPosition(
          roomcontainer_id, roomcontainer_type, point_idx, point_new_position_in_world))
    {
        std::cout << "WorldController::setRoomContainerBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setNodeBoundaryPolygonPointPosition for roomcontainer failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createRoom(
    const std::string &room_name,
    const size_t &room_id,
    const NodeType &room_type,
    const size_t &on_roomcontainer_id,
    const NodeType &on_roomcontainer_type)
{
    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::createRoom : " << std::endl <<
          "Input :\n" <<
          "\troom_name = " << room_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_roomcontainer_id = " << on_roomcontainer_id << std::endl <<
          "\ton_roomcontainer_type = " << on_roomcontainer_type << std::endl <<
          "this type is not the room type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          room_name, room_id, room_type, on_roomcontainer_id, on_roomcontainer_type, 0))
    {
        std::cout << "WorldController::createRoom : " << std::endl <<
          "Input :\n" <<
          "\troom_name = " << room_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_roomcontainer_id = " << on_roomcontainer_id << std::endl <<
          "\ton_roomcontainer_type = " << on_roomcontainer_type << std::endl <<
          "createNode for room failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_room_pair;
    new_room_pair.first = room_id;
    new_room_pair.second = room_type;

    room_pair_vec_.emplace_back(new_room_pair);

    return true;
}

bool WorldController::setRoomAxisCenterPositionInParent(
    const size_t &room_id,
    const NodeType &room_type,
    const EasyPoint2D &axis_new_center_position_in_parent)
{
    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::setRoomAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "this type is not the room type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInParent(
          room_id,
          room_type,
          axis_new_center_position_in_parent,
          true,
          true,
          true))
    {
        std::cout << "WorldController::setRoomAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this room node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setRoomAxisCenterPositionInWorld(
    const size_t &room_id,
    const NodeType &room_type,
    const EasyPoint2D &axis_new_center_position_in_world)
{
    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::setRoomAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "this type is not the room type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInWorld(
          room_id,
          room_type,
          axis_new_center_position_in_world,
          true,
          room_type == NodeType::FreeRoom,
          false))
    {
        std::cout << "WorldController::setRoomAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this room node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setRoomBoundaryPolygon(
    const size_t &room_id,
    const NodeType &room_type,
    const EasyPolygon2D &room_boundary_polygon)
{
    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::setRoomBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "this type is not the room type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygon(room_id, room_type, room_boundary_polygon))
    {
        std::cout << "WorldController::setRoomBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "setNodeBoundaryPolygon for room failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setRoomBoundaryPolygonPointPosition(
    const size_t &room_id,
    const NodeType &room_type,
    const size_t &point_idx,
    const EasyPoint2D &point_new_position_in_world)
{
    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::setRoomBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "this type is not the room type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygonPointPosition(
          room_id, room_type, point_idx, point_new_position_in_world))
    {
        std::cout << "WorldController::setRoomBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setNodeBoundaryPolygonPointPosition for room failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createDoor(
    const std::string &door_name,
    const size_t &door_id,
    const NodeType &door_type,
    const size_t &on_room_id,
    const NodeType &on_room_type,
    const size_t &on_room_boundary_idx)
{
    if(door_type != NodeType::Door)
    {
        std::cout << "WorldController::createDoor : " << std::endl <<
          "Input :\n" <<
          "\tdoor_name = " << door_name << std::endl <<
          "\tdoor_id = " << door_id << std::endl <<
          "\tdoor_type = " << door_type << std::endl <<
          "\ton_room_id = " << on_room_id << std::endl <<
          "\ton_room_type = " << on_room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "this type is not the door type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          door_name, door_id, door_type, on_room_id, on_room_type, on_room_boundary_idx))
    {
        std::cout << "WorldController::createDoor : " << std::endl <<
          "Input :\n" <<
          "\tdoor_name = " << door_name << std::endl <<
          "\tdoor_id = " << door_id << std::endl <<
          "\tdoor_type = " << door_type << std::endl <<
          "\ton_room_id = " << on_room_id << std::endl <<
          "\ton_room_type = " << on_room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "createNode for door failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_door_pair;
    new_door_pair.first = door_id;
    new_door_pair.second = door_type;

    door_pair_vec_.emplace_back(new_door_pair);

    return true;
}

bool WorldController::setDoorAxisCenterPositionInParent(
    const size_t &door_id,
    const NodeType &door_type,
    const EasyPoint2D &axis_new_center_position_in_parent)
{
    if(door_type != NodeType::Door)
    {
        std::cout << "WorldController::setDoorAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tdoor_id = " << door_id << std::endl <<
          "\tdoor_type = " << door_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "this type is not the door type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInParent(
          door_id,
          door_type,
          axis_new_center_position_in_parent,
          true,
          true,
          true))
    {
        std::cout << "WorldController::setDoorAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tdoor_id = " << door_id << std::endl <<
          "\tdoor_type = " << door_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this door node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setDoorAxisCenterPositionInWorld(
    const size_t &door_id,
    const NodeType &door_type,
    const EasyPoint2D &axis_new_center_position_in_world)
{
    if(door_type != NodeType::Door)
    {
        std::cout << "WorldController::setDoorAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tdoor_id = " << door_id << std::endl <<
          "\tdoor_type = " << door_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "this type is not the door type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInWorld(
          door_id,
          door_type,
          axis_new_center_position_in_world,
          true,
          true,
          false))
    {
        std::cout << "WorldController::setDoorAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tdoor_id = " << door_id << std::endl <<
          "\tdoor_type = " << door_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this door node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setDoorBoundaryPolygon(
    const size_t &door_id,
    const NodeType &door_type,
    const EasyPolygon2D &door_boundary_polygon)
{
    if(door_type != NodeType::Door)
    {
        std::cout << "WorldController::setDoorBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tdoor_id = " << door_id << std::endl <<
          "\tdoor_type = " << door_type << std::endl <<
          "this type is not the door type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygon(door_id, door_type, door_boundary_polygon))
    {
        std::cout << "WorldController::setDoorBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tdoor_id = " << door_id << std::endl <<
          "\tdoor_type = " << door_type << std::endl <<
          "setNodeBoundaryPolygon for door failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setDoorBoundaryPolygonPointPosition(
    const size_t &door_id,
    const NodeType &door_type,
    const size_t &point_idx,
    const EasyPoint2D &point_new_position_in_world)
{
    if(door_type != NodeType::Door)
    {
        std::cout << "WorldController::setDoorBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tdoor_id = " << door_id << std::endl <<
          "\tdoor_type = " << door_type << std::endl <<
          "this type is not the door type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygonPointPosition(
          door_id, door_type, point_idx, point_new_position_in_world))
    {
        std::cout << "WorldController::setDoorBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tdoor_id = " << door_id << std::endl <<
          "\tdoor_type = " << door_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setNodeBoundaryPolygonPointPosition for door failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createWindow(
    const std::string &window_name,
    const size_t &window_id,
    const NodeType &window_type,
    const size_t &on_room_id,
    const NodeType &on_room_type,
    const size_t &on_room_boundary_idx)
{
    if(window_type != NodeType::Window)
    {
        std::cout << "WorldController::createWindow : " << std::endl <<
          "Input :\n" <<
          "\twindow_name = " << window_name << std::endl <<
          "\twindow_id = " << window_id << std::endl <<
          "\twindow_type = " << window_type << std::endl <<
          "\ton_room_id = " << on_room_id << std::endl <<
          "\ton_room_type = " << on_room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "this type is not the window type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          window_name, window_id, window_type, on_room_id, on_room_type, on_room_boundary_idx))
    {
        std::cout << "WorldController::createWindow : " << std::endl <<
          "Input :\n" <<
          "\twindow_name = " << window_name << std::endl <<
          "\twindow_id = " << window_id << std::endl <<
          "\twindow_type = " << window_type << std::endl <<
          "\ton_room_id = " << on_room_id << std::endl <<
          "\ton_room_type = " << on_room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "createNode for window failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_window_pair;
    new_window_pair.first = window_id;
    new_window_pair.second = window_type;

    window_pair_vec_.emplace_back(new_window_pair);

    return true;
}

bool WorldController::setWindowAxisCenterPositionInParent(
    const size_t &window_id,
    const NodeType &window_type,
    const EasyPoint2D &axis_new_center_position_in_parent)
{
    if(window_type != NodeType::Window)
    {
        std::cout << "WorldController::setWindowAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\twindow_id = " << window_id << std::endl <<
          "\twindow_type = " << window_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "this type is not the window type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInParent(
          window_id,
          window_type,
          axis_new_center_position_in_parent,
          true,
          true,
          true))
    {
        std::cout << "WorldController::setWindowAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\twindow_id = " << window_id << std::endl <<
          "\twindow_type = " << window_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this window node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setWindowAxisCenterPositionInWorld(
    const size_t &window_id,
    const NodeType &window_type,
    const EasyPoint2D &axis_new_center_position_in_world)
{
    if(window_type != NodeType::Window)
    {
        std::cout << "WorldController::setWindowAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\twindow_id = " << window_id << std::endl <<
          "\twindow_type = " << window_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "this type is not the window type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInWorld(
          window_id,
          window_type,
          axis_new_center_position_in_world,
          true,
          true,
          false))
    {
        std::cout << "WorldController::setWindowAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\twindow_id = " << window_id << std::endl <<
          "\twindow_type = " << window_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this window node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setWindowBoundaryPolygon(
    const size_t &window_id,
    const NodeType &window_type,
    const EasyPolygon2D &window_boundary_polygon)
{
    if(window_type != NodeType::Window)
    {
        std::cout << "WorldController::setWindowBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\twindow_id = " << window_id << std::endl <<
          "\twindow_type = " << window_type << std::endl <<
          "this type is not the window type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygon(window_id, window_type, window_boundary_polygon))
    {
        std::cout << "WorldController::setWindowBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\twindow_id = " << window_id << std::endl <<
          "\twindow_type = " << window_type << std::endl <<
          "setNodeBoundaryPolygon for window failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setWindowBoundaryPolygonPointPosition(
    const size_t &window_id,
    const NodeType &window_type,
    const size_t &point_idx,
    const EasyPoint2D &point_new_position_in_world)
{
    if(window_type != NodeType::Window)
    {
        std::cout << "WorldController::setWindowBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\twindow_id = " << window_id << std::endl <<
          "\twindow_type = " << window_type << std::endl <<
          "this type is not the window type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygonPointPosition(
          window_id, window_type, point_idx, point_new_position_in_world))
    {
        std::cout << "WorldController::setWindowBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\twindow_id = " << window_id << std::endl <<
          "\twindow_type = " << window_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setNodeBoundaryPolygonPointPosition for window failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createTeam(
    const std::string &team_name,
    const size_t &team_id,
    const NodeType &team_type,
    const size_t &on_room_id,
    const NodeType &on_room_type)
{
    if(team_type != NodeType::Team)
    {
        std::cout << "WorldController::createTeam : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\ton_room_id = " << on_room_id << std::endl <<
          "\ton_room_type = " << on_room_type << std::endl <<
          "this type is not the team type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          team_name, team_id, team_type, on_room_id, on_room_type, 0))
    {
        std::cout << "WorldController::createTeam : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\ton_room_id = " << on_room_id << std::endl <<
          "\ton_room_type = " << on_room_type << std::endl <<
          "createNode for team failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_team_pair;
    new_team_pair.first = team_id;
    new_team_pair.second = team_type;

    team_pair_vec_.emplace_back(new_team_pair);

    return true;
}

bool WorldController::setTeamAxisCenterPositionInParent(
    const size_t &team_id,
    const NodeType &team_type,
    const EasyPoint2D &axis_new_center_position_in_parent)
{
    if(team_type != NodeType::Team)
    {
        std::cout << "WorldController::setTeamAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "this type is not the team type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInParent(
          team_id,
          team_type,
          axis_new_center_position_in_parent,
          true,
          true,
          true))
    {
        std::cout << "WorldController::setTeamAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this team node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setTeamAxisCenterPositionInWorld(
    const size_t &team_id,
    const NodeType &team_type,
    const EasyPoint2D &axis_new_center_position_in_world)
{
    if(team_type != NodeType::Team)
    {
        std::cout << "WorldController::setTeamAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "this type is not the team type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInWorld(
          team_id,
          team_type,
          axis_new_center_position_in_world,
          true,
          true,
          false))
    {
        std::cout << "WorldController::setTeamAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this team node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setTeamBoundaryPolygon(
    const size_t &team_id,
    const NodeType &team_type,
    const EasyPolygon2D &team_boundary_polygon)
{
    if(team_type != NodeType::Team)
    {
        std::cout << "WorldController::setTeamBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "this type is not the team type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygon(team_id, team_type, team_boundary_polygon))
    {
        std::cout << "WorldController::setTeamBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "setNodeBoundaryPolygon for team failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setTeamBoundaryPolygonPointPosition(
    const size_t &team_id,
    const NodeType &team_type,
    const size_t &point_idx,
    const EasyPoint2D &point_new_position_in_world)
{
    if(team_type != NodeType::Team)
    {
        std::cout << "WorldController::setTeamBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "this type is not the team type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygonPointPosition(
          team_id, team_type, point_idx, point_new_position_in_world))
    {
        std::cout << "WorldController::setTeamBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setNodeBoundaryPolygonPointPosition for team failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createPerson(
    const std::string &person_name,
    const size_t &person_id,
    const NodeType &person_type,
    const size_t &on_team_id,
    const NodeType &on_team_type)
{
    if(person_type != NodeType::Person)
    {
        std::cout << "WorldController::createPerson : " << std::endl <<
          "Input :\n" <<
          "\tperson_name = " << person_name << std::endl <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "\ton_team_id = " << on_team_id << std::endl <<
          "\ton_team_type = " << on_team_type << std::endl <<
          "this type is not the person type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          person_name, person_id, person_type, on_team_id, on_team_type, 0))
    {
        std::cout << "WorldController::createPerson : " << std::endl <<
          "Input :\n" <<
          "\tperson_name = " << person_name << std::endl <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "\ton_team_id = " << on_team_id << std::endl <<
          "\ton_team_type = " << on_team_type << std::endl <<
          "createNode for person failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_person_pair;
    new_person_pair.first = person_id;
    new_person_pair.second = person_type;

    person_pair_vec_.emplace_back(new_person_pair);

    return true;
}

bool WorldController::setPersonAxisCenterPositionInParent(
    const size_t &person_id,
    const NodeType &person_type,
    const EasyPoint2D &axis_new_center_position_in_parent)
{
    if(person_type != NodeType::Person)
    {
        std::cout << "WorldController::setPersonAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "this type is not the person type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInParent(
          person_id,
          person_type,
          axis_new_center_position_in_parent,
          true,
          true,
          false))
    {
        std::cout << "WorldController::setPersonAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this person node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setPersonAxisCenterPositionInWorld(
    const size_t &person_id,
    const NodeType &person_type,
    const EasyPoint2D &axis_new_center_position_in_world)
{
    if(person_type != NodeType::Person)
    {
        std::cout << "WorldController::setPersonAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "this type is not the person type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInWorld(
          person_id,
          person_type,
          axis_new_center_position_in_world,
          true,
          true,
          false))
    {
        std::cout << "WorldController::setPersonAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this person node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setPersonBoundaryPolygon(
    const size_t &person_id,
    const NodeType &person_type,
    const EasyPolygon2D &person_boundary_polygon)
{
    if(person_type != NodeType::Person)
    {
        std::cout << "WorldController::setPersonBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "this type is not the person type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygon(person_id, person_type, person_boundary_polygon))
    {
        std::cout << "WorldController::setPersonBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "setNodeBoundaryPolygon for person failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setPersonBoundaryPolygonPointPosition(
    const size_t &person_id,
    const NodeType &person_type,
    const size_t &point_idx,
    const EasyPoint2D &point_new_position_in_world)
{
    if(person_type != NodeType::Person)
    {
        std::cout << "WorldController::setPersonBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "this type is not the person type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygonPointPosition(
          person_id, person_type, point_idx, point_new_position_in_world))
    {
        std::cout << "WorldController::setPersonBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setNodeBoundaryPolygonPointPosition for person failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createFurniture(
    const std::string &furniture_name,
    const size_t &furniture_id,
    const NodeType &furniture_type,
    const size_t &on_person_id,
    const NodeType &on_person_type)
{
    if(furniture_type != NodeType::Furniture)
    {
        std::cout << "WorldController::createFurniture : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tfurniture_id = " << furniture_id << std::endl <<
          "\tfurniture_type = " << furniture_type << std::endl <<
          "\ton_person_id = " << on_person_id << std::endl <<
          "\ton_person_type = " << on_person_type << std::endl <<
          "this type is not the furniture type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          furniture_name, furniture_id, furniture_type, on_person_id, on_person_type, 0))
    {
        std::cout << "WorldController::createFurniture : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tfurniture_id = " << furniture_id << std::endl <<
          "\tfurniture_type = " << furniture_type << std::endl <<
          "\ton_person_id = " << on_person_id << std::endl <<
          "\ton_person_type = " << on_person_type << std::endl <<
          "createNode for furniture failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_furniture_pair;
    new_furniture_pair.first = furniture_id;
    new_furniture_pair.second = furniture_type;

    furniture_pair_vec_.emplace_back(new_furniture_pair);

    return true;
}

bool WorldController::setFurnitureAxisCenterPositionInParent(
    const size_t &furniture_id,
    const NodeType &furniture_type,
    const EasyPoint2D &axis_new_center_position_in_parent)
{
    if(furniture_type != NodeType::Furniture)
    {
        std::cout << "WorldController::setFurnitureAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_id = " << furniture_id << std::endl <<
          "\tfurniture_type = " << furniture_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "this type is not the furniture type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInParent(
          furniture_id,
          furniture_type,
          axis_new_center_position_in_parent,
          true,
          true,
          false))
    {
        std::cout << "WorldController::setFurnitureAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_id = " << furniture_id << std::endl <<
          "\tfurniture_type = " << furniture_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this furniture node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setFurnitureAxisCenterPositionInWorld(
    const size_t &furniture_id,
    const NodeType &furniture_type,
    const EasyPoint2D &axis_new_center_position_in_world)
{
    if(furniture_type != NodeType::Furniture)
    {
        std::cout << "WorldController::setFurnitureAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_id = " << furniture_id << std::endl <<
          "\tfurniture_type = " << furniture_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "this type is not the furniture type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisCenterPositionInWorld(
          furniture_id,
          furniture_type,
          axis_new_center_position_in_world,
          true,
          true,
          false))
    {
        std::cout << "WorldController::setFurnitureAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_id = " << furniture_id << std::endl <<
          "\tfurniture_type = " << furniture_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "setNodeAxisCenterPositionInParent for this furniture node failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setFurnitureBoundaryPolygon(
    const size_t &furniture_id,
    const NodeType &furniture_type,
    const EasyPolygon2D &furniture_boundary_polygon)
{
    if(furniture_type != NodeType::Furniture)
    {
        std::cout << "WorldController::setFurnitureBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_id = " << furniture_id << std::endl <<
          "\tfurniture_type = " << furniture_type << std::endl <<
          "this type is not the furniture type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygon(furniture_id, furniture_type, furniture_boundary_polygon))
    {
        std::cout << "WorldController::setFurnitureBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_id = " << furniture_id << std::endl <<
          "\tfurniture_type = " << furniture_type << std::endl <<
          "setNodeBoundaryPolygon for furniture failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::setFurnitureBoundaryPolygonPointPosition(
    const size_t &furniture_id,
    const NodeType &furniture_type,
    const size_t &point_idx,
    const EasyPoint2D &point_new_position_in_world)
{
    if(furniture_type != NodeType::Furniture)
    {
        std::cout << "WorldController::setFurnitureBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_id = " << furniture_id << std::endl <<
          "\tfurniture_type = " << furniture_type << std::endl <<
          "this type is not the furniture type!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeBoundaryPolygonPointPosition(
          furniture_id, furniture_type, point_idx, point_new_position_in_world))
    {
        std::cout << "WorldController::setFurnitureBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_id = " << furniture_id << std::endl <<
          "\tfurniture_type = " << furniture_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setNodeBoundaryPolygonPointPosition for furniture failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createFurnitureForPerson(
    const std::string &furniture_name,
    const size_t &person_id,
    const NodeType &person_type)
{
    if(person_type != NodeType::Person)
    {
        std::cout << "WorldController::createFurnitureForPerson : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "this type is not the person type!" << std::endl;

        return false;
    }

    EasyNode* search_node = findNode(person_id, person_type);

    if(search_node == nullptr)
    {
        std::cout << "WorldController::createFurnitureForPerson : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "person node not exist!" << std::endl;

        return false;
    }

    bool find_exist_furniture = false;
    size_t new_furniture_id = 0;
    for(const std::pair<size_t, NodeType> &furniture_pair : furniture_pair_vec_)
    {
        if(furniture_pair.second != NodeType::Furniture)
        {
            continue;
        }

        new_furniture_id = std::max(new_furniture_id, furniture_pair.first);
        find_exist_furniture = true;
    }
    if(find_exist_furniture)
    {
        ++new_furniture_id;
    }

    if(!world_tree_.createNode(furniture_name, new_furniture_id, NodeType::Furniture, person_id, person_type, 0))
    {
        std::cout << "WorldController::createFurnitureForPerson : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "createNode for this furniture node not exist!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_furniture_pair;
    new_furniture_pair.first = new_furniture_id;
    new_furniture_pair.second = NodeType::Furniture;

    furniture_pair_vec_.emplace_back(new_furniture_pair);

    EasyNode* search_space_node = search_node->findChild(0, NodeType::Space);

    if(search_space_node == nullptr)
    {
        std::cout << "WorldController::createFurnitureForPerson : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "person space node not exist!" << std::endl;

        return false;
    }

    const EasyPolygon2D &search_space_boundary_polygon =
      search_space_node->getBoundaryPolygon();

    const EasyPoint2D &person_size = search_space_boundary_polygon.point_list[2];

    if(person_size.x <= 0 || person_size.y <= 0)
    {
        std::cout << "WorldController::createFurnitureForPerson : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "this person size not valid!" << std::endl;

        return false;
    }

    EasyPolygon2D furniture_node_boundary_polygon;
    furniture_node_boundary_polygon.point_list.resize(8);
    furniture_node_boundary_polygon.point_list[0].setPosition(0, person_size.y);
    furniture_node_boundary_polygon.point_list[1].setPosition(person_size.x, person_size.y);
    furniture_node_boundary_polygon.point_list[2].setPosition(person_size.x, 0.6 * person_size.y);
    furniture_node_boundary_polygon.point_list[3].setPosition(0.75 * person_size.x, 0.6 * person_size.y);
    furniture_node_boundary_polygon.point_list[4].setPosition(0.75 * person_size.x, 0.3 * person_size.y);
    furniture_node_boundary_polygon.point_list[5].setPosition(0.25 * person_size.x, 0.3 * person_size.y);
    furniture_node_boundary_polygon.point_list[6].setPosition(0.25 * person_size.x, 0.6 * person_size.y);
    furniture_node_boundary_polygon.point_list[7].setPosition(0, 0.6 * person_size.y);
    furniture_node_boundary_polygon.setAntiClockWise();

    if(!world_tree_.setNodeBoundaryPolygon(new_furniture_id, NodeType::Furniture, furniture_node_boundary_polygon))
    {
        std::cout << "WorldController::createFurnitureForPerson : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "setNodeBoundaryPolygon for new furniture failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createPersonForTeam(
    const std::string &person_name,
    const std::string &furniture_name,
    const size_t &team_id,
    const NodeType &team_type,
    const float &person_width,
    const float &person_height,
    const EasyAxis2D &person_axis_in_parent)
{
    if(team_type != NodeType::Team)
    {
        std::cout << "WorldController::createPersonForTeam : " << std::endl <<
          "Input :\n" <<
          "\tperson_name = " << person_name << std::endl <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_width = " << person_width << std::endl <<
          "\tperson_height = " << person_height << std::endl <<
          "\tperson_axis_in_parent :" << std::endl;
        person_axis_in_parent.outputInfo(1);
        std::cout << "this type is not the team type!" << std::endl;

        return false;
    }

    if(!haveThisNode(team_id, team_type))
    {
        std::cout << "WorldController::createPersonForTeam : " << std::endl <<
          "Input :\n" <<
          "\tperson_name = " << person_name << std::endl <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_width = " << person_width << std::endl <<
          "\tperson_height = " << person_height << std::endl <<
          "\tperson_axis_in_parent :" << std::endl;
        person_axis_in_parent.outputInfo(1);
        std::cout << "this team node not exist!" << std::endl;

        return false;
    }

    if(person_width <= 0 || person_height <= 0)
    {
        std::cout << "WorldController::createPersonForTeam : " << std::endl <<
          "Input :\n" <<
          "\tperson_name = " << person_name << std::endl <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_width = " << person_width << std::endl <<
          "\tperson_height = " << person_height << std::endl <<
          "\tperson_axis_in_parent :" << std::endl;
        person_axis_in_parent.outputInfo(1);
        std::cout << "this person size not valid!" << std::endl;

        return false;
    }

    bool find_exist_person = false;
    size_t new_person_id = 0;
    for(const std::pair<size_t, NodeType> &person_pair : person_pair_vec_)
    {
        if(person_pair.second != NodeType::Person)
        {
            continue;
        }

        new_person_id = std::max(new_person_id, person_pair.first);
        find_exist_person = true;
    }
    if(find_exist_person)
    {
        ++new_person_id;
    }

    if(!world_tree_.createNode(person_name, new_person_id, NodeType::Person, team_id, team_type, 0))
    {
        std::cout << "WorldController::createPersonForTeam : " << std::endl <<
          "Input :\n" <<
          "\tperson_name = " << person_name << std::endl <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_width = " << person_width << std::endl <<
          "\tperson_height = " << person_height << std::endl <<
          "\tperson_axis_in_parent :" << std::endl;
        person_axis_in_parent.outputInfo(1);
        std::cout << "createNode for this person node failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_person_pair;
    new_person_pair.first = new_person_id;
    new_person_pair.second = NodeType::Person;

    person_pair_vec_.emplace_back(new_person_pair);

    EasyPolygon2D person_node_boundary_polygon;
    person_node_boundary_polygon.point_list.resize(4);
    person_node_boundary_polygon.point_list[0].setPosition(0, 0);
    person_node_boundary_polygon.point_list[1].setPosition(person_width, 0);
    person_node_boundary_polygon.point_list[2].setPosition(person_width, person_height);
    person_node_boundary_polygon.point_list[3].setPosition(0, person_height);
    person_node_boundary_polygon.setAntiClockWise();

    if(!world_tree_.setNodeBoundaryPolygon(new_person_id, NodeType::Person, person_node_boundary_polygon))
    {
        std::cout << "WorldController::createPersonForTeam : " << std::endl <<
          "Input :\n" <<
          "\tperson_name = " << person_name << std::endl <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_width = " << person_width << std::endl <<
          "\tperson_height = " << person_height << std::endl <<
          "\tperson_axis_in_parent :" << std::endl;
        person_axis_in_parent.outputInfo(1);
        std::cout << "setNodeBoundaryPolygon for new person failed!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisInParent(new_person_id, NodeType::Person, person_axis_in_parent, true))
    {
        std::cout << "WorldController::createPersonForTeam : " << std::endl <<
          "Input :\n" <<
          "\tperson_name = " << person_name << std::endl <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_width = " << person_width << std::endl <<
          "\tperson_height = " << person_height << std::endl <<
          "\tperson_axis_in_parent :" << std::endl;
        person_axis_in_parent.outputInfo(1);
        std::cout << "setNodeAxisInParent for new person failed!" << std::endl;

        return false;
    }

    if(!createFurnitureForPerson(furniture_name, new_person_id, NodeType::Person))
    {
        std::cout << "WorldController::createPersonForTeam : " << std::endl <<
          "Input :\n" <<
          "\tperson_name = " << person_name << std::endl <<
          "\tfurniture_name = " << furniture_name << std::endl <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_width = " << person_width << std::endl <<
          "\tperson_height = " << person_height << std::endl <<
          "\tperson_axis_in_parent :" << std::endl;
        person_axis_in_parent.outputInfo(1);
        std::cout << "createFurnitureForPerson for new person failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createPersonGroupForTeam(
    const std::vector<std::vector<std::string>> &person_name_matrix,
    const std::vector<std::vector<std::string>> &furniture_name_matrix,
    const size_t &team_id,
    const NodeType &team_type,
    const size_t &person_x_direction_num,
    const size_t &person_y_direction_num,
    const bool &is_face_horizontal)
{
    if(person_x_direction_num == 0 || person_y_direction_num == 0)
    {
        std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "this person size not valid!" << std::endl;

        return false;
    }

    if(person_name_matrix.size() == 0 || furniture_name_matrix.size() == 0)
    {
        std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "name matrix size not valid!" << std::endl;

        return false;
    }

    if(person_name_matrix.size() != person_x_direction_num ||
        furniture_name_matrix.size() != person_x_direction_num ||
        person_name_matrix[0].size() != person_y_direction_num ||
        furniture_name_matrix[0].size() != person_y_direction_num)
    {
        std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "name matrix size not match person size!" << std::endl;

        return false;
    }

    if(team_type != NodeType::Team)
    {
        std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "this type is not the team type!" << std::endl;

        return false;
    }

    EasyNode* search_node = findNode(team_id, team_type);

    if(search_node == nullptr)
    {
        std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "this team node not exist!" << std::endl;

        return false;
    }

    EasyNode* search_space_node = search_node->findChild(0, NodeType::Space);

    if(search_space_node == nullptr)
    {
        std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "team space node not exist!" << std::endl;

        return false;
    }

    const EasyPolygon2D &search_space_boundary_polygon =
      search_space_node->getBoundaryPolygon();

    if(search_space_boundary_polygon.point_list.size() != 4)
    {
        std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "team space boundary polygon size != 4!" << std::endl;

        return false;
    }

    const EasyPoint2D &team_size = search_space_boundary_polygon.point_list[2];

    float person_x_length = team_size.x / person_x_direction_num;
    float person_y_length = team_size.y / person_y_direction_num;

    std::vector<EasyAxis2D> axis_vec;
    axis_vec.resize(2);

    if(is_face_horizontal)
    {
        if(!axis_vec[0].setXDirection(0, -1))
        {
            std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
              "Input :\n" <<
              "\tteam_id = " << team_id << std::endl <<
              "\tteam_type = " << team_type << std::endl <<
              "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
              "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
              "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
              "setXDirection for person basic axis failed!" << std::endl;

            return false;
        }

        if(!axis_vec[1].setXDirection(0, 1))
        {
            std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
              "Input :\n" <<
              "\tteam_id = " << team_id << std::endl <<
              "\tteam_type = " << team_type << std::endl <<
              "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
              "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
              "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
              "setXDirection for person opposite axis failed!" << std::endl;

            return false;
        }
    }
    else
    {
        if(!axis_vec[0].setXDirection(1, 0))
        {
            std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
              "Input :\n" <<
              "\tteam_id = " << team_id << std::endl <<
              "\tteam_type = " << team_type << std::endl <<
              "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
              "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
              "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
              "setXDirection for person first axis failed!" << std::endl;

            return false;
        }

        if(!axis_vec[1].setXDirection(-1, 0))
        {
            std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
              "Input :\n" <<
              "\tteam_id = " << team_id << std::endl <<
              "\tteam_type = " << team_type << std::endl <<
              "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
              "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
              "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
              "setXDirection for person second axis failed!" << std::endl;

            return false;
        }
    }

    if(is_face_horizontal)
    {
        for(size_t i = 0; i < person_x_direction_num; ++i)
        {
            const size_t use_axis_idx = i % 2;
            for(size_t j = 0; j < person_y_direction_num; ++j)
            {
                if(!axis_vec[use_axis_idx].setCenter(
                      (i + use_axis_idx) * person_x_length,
                      (j + ((use_axis_idx + 1) % 2)) * person_y_length))
                {
                    std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
                      "Input :\n" <<
                      "\tteam_id = " << team_id << std::endl <<
                      "\tteam_type = " << team_type << std::endl <<
                      "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
                      "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
                      "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
                      "setCenter for current person axis failed!" << std::endl;

                    return false;
                }

                if(!createPersonForTeam(
                      person_name_matrix[i][j],
                      furniture_name_matrix[i][j],
                      team_id,
                      team_type,
                      person_y_length,
                      person_x_length,
                      axis_vec[use_axis_idx]))
                {
                    std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
                      "Input :\n" <<
                      "\tteam_id = " << team_id << std::endl <<
                      "\tteam_type = " << team_type << std::endl <<
                      "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
                      "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
                      "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
                      "createPersonForTeam for new person failed!" << std::endl;

                    return false;
                }
            }
        }
    }
    else
    {
        for(size_t j = 0; j < person_y_direction_num; ++j)
        {
            const size_t use_axis_idx = j % 2;
            for(size_t i = 0; i < person_x_direction_num; ++i)
            {
                if(!axis_vec[use_axis_idx].setCenter(
                      (i + use_axis_idx) * person_x_length,
                      (j + use_axis_idx) * person_y_length))
                {
                    std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
                      "Input :\n" <<
                      "\tteam_id = " << team_id << std::endl <<
                      "\tteam_type = " << team_type << std::endl <<
                      "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
                      "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
                      "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
                      "setCenter for current person axis failed!" << std::endl;

                    return false;
                }

                if(!createPersonForTeam(
                      person_name_matrix[i][j],
                      furniture_name_matrix[i][j],
                      team_id,
                      team_type,
                      person_x_length,
                      person_y_length,
                      axis_vec[use_axis_idx]))
                {
                    std::cout << "WorldController::createPersonGroupForTeam : " << std::endl <<
                      "Input :\n" <<
                      "\tteam_id = " << team_id << std::endl <<
                      "\tteam_type = " << team_type << std::endl <<
                      "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
                      "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
                      "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
                      "createPersonForTeam for new person failed!" << std::endl;

                    return false;
                }
            }
        }
    }

    return true;
}

bool WorldController::createTeamForRoom(
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
    const bool &is_face_horizontal)
{
    if(person_x_direction_num == 0 || person_y_direction_num == 0)
    {
        std::cout << "WorldController::createTeamForRoom : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\tteam_width = " << team_width << std::endl <<
          "\tteam_height = " << team_height << std::endl <<
          "\tteam_axis_in_parent :" << std::endl;
        team_axis_in_parent.outputInfo(1);
        std::cout << "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "this person size not valid!" << std::endl;

        return false;
    }

    if(person_name_matrix.size() == 0 || furniture_name_matrix.size() == 0)
    {
        std::cout << "WorldController::createTeamForRoom : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\tteam_width = " << team_width << std::endl <<
          "\tteam_height = " << team_height << std::endl <<
          "\tteam_axis_in_parent :" << std::endl;
        team_axis_in_parent.outputInfo(1);
        std::cout << "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "name matrix size not valid!" << std::endl;

        return false;
    }

    if(person_name_matrix.size() != person_x_direction_num ||
        furniture_name_matrix.size() != person_x_direction_num ||
        person_name_matrix[0].size() != person_y_direction_num ||
        furniture_name_matrix[0].size() != person_y_direction_num)
    {
        std::cout << "WorldController::createTeamForRoom : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\tteam_width = " << team_width << std::endl <<
          "\tteam_height = " << team_height << std::endl <<
          "\tteam_axis_in_parent :" << std::endl;
        team_axis_in_parent.outputInfo(1);
        std::cout << "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "name matrix size not match person size!" << std::endl;

        return false;
    }

    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::createTeamForRoom : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\tteam_width = " << team_width << std::endl <<
          "\tteam_height = " << team_height << std::endl <<
          "\tteam_axis_in_parent :" << std::endl;
        team_axis_in_parent.outputInfo(1);
        std::cout << "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "this type is not the room type!" << std::endl;

        return false;
    }

    if(team_width <= 0 || team_height <= 0)
    {
        std::cout << "WorldController::createTeamForRoom : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\tteam_width = " << team_width << std::endl <<
          "\tteam_height = " << team_height << std::endl <<
          "\tteam_axis_in_parent :" << std::endl;
        team_axis_in_parent.outputInfo(1);
        std::cout << "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "this team size not valid!" << std::endl;

        return false;
    }

    if(!haveThisNode(room_id, room_type))
    {
        std::cout << "WorldController::createTeamForRoom : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\tteam_width = " << team_width << std::endl <<
          "\tteam_height = " << team_height << std::endl <<
          "\tteam_axis_in_parent :" << std::endl;
        team_axis_in_parent.outputInfo(1);
        std::cout << "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "this room node not exist!" << std::endl;

        return false;
    }

    bool find_exist_team = false;
    size_t new_team_id = 0;
    for(const std::pair<size_t, NodeType> &team_pair : team_pair_vec_)
    {
        if(team_pair.second != NodeType::Team)
        {
            continue;
        }

        new_team_id = std::max(new_team_id, team_pair.first);
        find_exist_team = true;
    }
    if(find_exist_team)
    {
        ++new_team_id;
    }

    if(!world_tree_.createNode(team_name, new_team_id, NodeType::Team, room_id, room_type, 0))
    {
        std::cout << "WorldController::createTeamForRoom : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\tteam_width = " << team_width << std::endl <<
          "\tteam_height = " << team_height << std::endl <<
          "\tteam_axis_in_parent :" << std::endl;
        team_axis_in_parent.outputInfo(1);
        std::cout << "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "createNode for this team node failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_team_pair;
    new_team_pair.first = new_team_id;
    new_team_pair.second = NodeType::Team;

    team_pair_vec_.emplace_back(new_team_pair);

    EasyPolygon2D team_node_boundary_polygon;
    team_node_boundary_polygon.point_list.resize(4);
    team_node_boundary_polygon.point_list[0].setPosition(0, 0);
    team_node_boundary_polygon.point_list[1].setPosition(team_width, 0);
    team_node_boundary_polygon.point_list[2].setPosition(team_width, team_height);
    team_node_boundary_polygon.point_list[3].setPosition(0, team_height);
    team_node_boundary_polygon.setAntiClockWise();

    if(!world_tree_.setNodeBoundaryPolygon(new_team_id, NodeType::Team, team_node_boundary_polygon))
    {
        std::cout << "WorldController::createTeamForRoom : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\tteam_width = " << team_width << std::endl <<
          "\tteam_height = " << team_height << std::endl <<
          "\tteam_axis_in_parent :" << std::endl;
        team_axis_in_parent.outputInfo(1);
        std::cout << "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "setNodeBoundaryPolygon for new team failed!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisInParent(new_team_id, NodeType::Team, team_axis_in_parent, true))
    {
        std::cout << "WorldController::createTeamForRoom : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\tteam_width = " << team_width << std::endl <<
          "\tteam_height = " << team_height << std::endl <<
          "\tteam_axis_in_parent :" << std::endl;
        team_axis_in_parent.outputInfo(1);
        std::cout << "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "setNodeAxisInParent for new team failed!" << std::endl;

        return false;
    }

    if(!createPersonGroupForTeam(
          person_name_matrix,
          furniture_name_matrix,
          new_team_id,
          NodeType::Team,
          person_x_direction_num,
          person_y_direction_num,
          is_face_horizontal))
    {
        std::cout << "WorldController::createTeamForRoom : " << std::endl <<
          "Input :\n" <<
          "\tteam_name = " << team_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\tteam_width = " << team_width << std::endl <<
          "\tteam_height = " << team_height << std::endl <<
          "\tteam_axis_in_parent :" << std::endl;
        team_axis_in_parent.outputInfo(1);
        std::cout << "\tperson_x_direction_num = " << person_x_direction_num << std::endl <<
          "\tperson_y_direction_num = " << person_y_direction_num << std::endl <<
          "\tis_face_horizontal = " << is_face_horizontal << std::endl <<
          "createPersonGroupForTeam for new team failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createWindowForRoom(
    const std::string &window_name,
    const size_t &room_id,
    const NodeType &room_type,
    const size_t &on_room_boundary_idx,
    const float &window_width,
    const EasyAxis2D &window_axis_in_parent)
{
    const float window_small_height = 0.00001;

    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::createWindowForRoom : " << std::endl <<
          "Input :\n" <<
          "\twindow_name = " << window_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\twindow_width = " << window_width << std::endl <<
          "\twindow_axis_in_parent :" << std::endl;
        window_axis_in_parent.outputInfo(1);
        std::cout <<
          "this type is not the room type!" << std::endl;

        return false;
    }

    if(!haveThisNode(room_id, room_type))
    {
        std::cout << "WorldController::createWindowForRoom : " << std::endl <<
          "Input :\n" <<
          "\twindow_name = " << window_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\twindow_width = " << window_width << std::endl <<
          "\twindow_axis_in_parent :" << std::endl;
        std::cout <<
          "this room node not exist!" << std::endl;

        return false;
    }

    if(window_width <= 0)
    {
        std::cout << "WorldController::createWindowForRoom : " << std::endl <<
          "Input :\n" <<
          "\twindow_name = " << window_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\twindow_width = " << window_width << std::endl <<
          "\twindow_axis_in_parent :" << std::endl;
        std::cout <<
          "this window size not valid!" << std::endl;

        return false;
    }

    bool find_exist_window = false;
    size_t new_window_id = 0;
    for(const std::pair<size_t, NodeType> &window_pair : window_pair_vec_)
    {
        if(window_pair.second != NodeType::Window)
        {
            continue;
        }

        new_window_id = std::max(new_window_id, window_pair.first);
        find_exist_window = true;
    }
    if(find_exist_window)
    {
        ++new_window_id;
    }

    if(!world_tree_.createNode(window_name, new_window_id, NodeType::Window, room_id, room_type, on_room_boundary_idx))
    {
        std::cout << "WorldController::createWindowForRoom : " << std::endl <<
          "Input :\n" <<
          "\twindow_name = " << window_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\twindow_width = " << window_width << std::endl <<
          "\twindow_axis_in_parent :" << std::endl;
        std::cout <<
          "createNode for this window node failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_window_pair;
    new_window_pair.first = new_window_id;
    new_window_pair.second = NodeType::Window;

    window_pair_vec_.emplace_back(new_window_pair);

    EasyPolygon2D window_node_boundary_polygon;
    window_node_boundary_polygon.point_list.resize(4);
    window_node_boundary_polygon.point_list[0].setPosition(0, 0);
    window_node_boundary_polygon.point_list[1].setPosition(window_width, 0);
    window_node_boundary_polygon.point_list[2].setPosition(window_width, window_small_height);
    window_node_boundary_polygon.point_list[3].setPosition(0, window_small_height);
    window_node_boundary_polygon.setAntiClockWise();

    if(!world_tree_.setNodeBoundaryPolygon(new_window_id, NodeType::Window, window_node_boundary_polygon))
    {
        std::cout << "WorldController::createWindowForRoom : " << std::endl <<
          "Input :\n" <<
          "\twindow_name = " << window_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\twindow_width = " << window_width << std::endl <<
          "\twindow_axis_in_parent :" << std::endl;
        std::cout <<
          "setNodeBoundaryPolygon for new window failed!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisInParent(new_window_id, NodeType::Window, window_axis_in_parent, true))
    {
        std::cout << "WorldController::createWindowForRoom : " << std::endl <<
          "Input :\n" <<
          "\twindow_name = " << window_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\twindow_width = " << window_width << std::endl <<
          "\twindow_axis_in_parent :" << std::endl;
        std::cout <<
          "setNodeAxisInParent for new window failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createDoorForRoom(
    const std::string &door_name,
    const size_t &room_id,
    const NodeType &room_type,
    const size_t &on_room_boundary_idx,
    const float &door_width,
    const EasyAxis2D &door_axis_in_parent,
    const bool &is_handle_on_right_from_outside)
{
    const float door_small_height = 0.00001;

    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::createDoorForRoom : " << std::endl <<
          "Input :\n" <<
          "\tdoor_name = " << door_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\tdoor_width = " << door_width << std::endl <<
          "\tdoor_axis_in_parent :" << std::endl;
        door_axis_in_parent.outputInfo(1);
        std::cout <<
          "\tis_handle_on_right_from_outside = " << is_handle_on_right_from_outside << std::endl <<
          "this type is not the room type!" << std::endl;

        return false;
    }

    if(!haveThisNode(room_id, room_type))
    {
        std::cout << "WorldController::createDoorForRoom : " << std::endl <<
          "Input :\n" <<
          "\tdoor_name = " << door_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\tdoor_width = " << door_width << std::endl <<
          "\tdoor_axis_in_parent :" << std::endl;
        std::cout <<
          "\tis_handle_on_right_from_outside = " << is_handle_on_right_from_outside << std::endl <<
          "this room node not exist!" << std::endl;

        return false;
    }

    if(door_width <= 0)
    {
        std::cout << "WorldController::createDoorForRoom : " << std::endl <<
          "Input :\n" <<
          "\tdoor_name = " << door_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\tdoor_width = " << door_width << std::endl <<
          "\tdoor_axis_in_parent :" << std::endl;
        std::cout <<
          "\tis_handle_on_right_from_outside = " << is_handle_on_right_from_outside << std::endl <<
          "this door size not valid!" << std::endl;

        return false;
    }

    bool find_exist_door = false;
    size_t new_door_id = 0;
    for(const std::pair<size_t, NodeType> &door_pair : door_pair_vec_)
    {
        if(door_pair.second != NodeType::Door)
        {
            continue;
        }

        new_door_id = std::max(new_door_id, door_pair.first);
        find_exist_door = true;
    }
    if(find_exist_door)
    {
        ++new_door_id;
    }

    if(!world_tree_.createNode(door_name, new_door_id, NodeType::Door, room_id, room_type, on_room_boundary_idx))
    {
        std::cout << "WorldController::createDoorForRoom : " << std::endl <<
          "Input :\n" <<
          "\tdoor_name = " << door_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\tdoor_width = " << door_width << std::endl <<
          "\tdoor_axis_in_parent :" << std::endl;
        std::cout <<
          "\tis_handle_on_right_from_outside = " << is_handle_on_right_from_outside << std::endl <<
          "createNode for this door node failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_door_pair;
    new_door_pair.first = new_door_id;
    new_door_pair.second = NodeType::Door;

    door_pair_vec_.emplace_back(new_door_pair);

    EasyPolygon2D door_node_boundary_polygon;
    door_node_boundary_polygon.point_list.resize(6);
    door_node_boundary_polygon.point_list[0].setPosition(0, 0);
    door_node_boundary_polygon.point_list[1].setPosition(door_width, 0);
    if(is_handle_on_right_from_outside)
    {
        door_node_boundary_polygon.point_list[2].setPosition(door_width, door_small_height);
        door_node_boundary_polygon.point_list[3].setPosition(door_small_height, door_small_height);
        door_node_boundary_polygon.point_list[4].setPosition(door_small_height, door_width + door_small_height);
        door_node_boundary_polygon.point_list[5].setPosition(0, door_width + door_small_height);
    }
    else
    {
        door_node_boundary_polygon.point_list[2].setPosition(door_width, door_width + door_small_height);
        door_node_boundary_polygon.point_list[3].setPosition(door_width - door_small_height, door_width + door_small_height);
        door_node_boundary_polygon.point_list[4].setPosition(door_width - door_small_height, door_small_height);
        door_node_boundary_polygon.point_list[5].setPosition(0, door_small_height);
    }
    door_node_boundary_polygon.setAntiClockWise();

    if(!world_tree_.setNodeBoundaryPolygon(new_door_id, NodeType::Door, door_node_boundary_polygon))
    {
        std::cout << "WorldController::createDoorForRoom : " << std::endl <<
          "Input :\n" <<
          "\tdoor_name = " << door_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\tdoor_width = " << door_width << std::endl <<
          "\tdoor_axis_in_parent :" << std::endl;
        std::cout <<
          "\tis_handle_on_right_from_outside = " << is_handle_on_right_from_outside << std::endl <<
          "setNodeBoundaryPolygon for new door failed!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisInParent(new_door_id, NodeType::Door, door_axis_in_parent, true))
    {
        std::cout << "WorldController::createDoorForRoom : " << std::endl <<
          "Input :\n" <<
          "\tdoor_name = " << door_name << std::endl <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_room_boundary_idx = " << on_room_boundary_idx << std::endl <<
          "\tdoor_width = " << door_width << std::endl <<
          "\tdoor_axis_in_parent :" << std::endl;
        std::cout <<
          "\tis_handle_on_right_from_outside = " << is_handle_on_right_from_outside << std::endl <<
          "setNodeAxisInParent for new door failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createRoomForRoomContainer(
    const std::string &room_name,
    const size_t &roomcontainer_id,
    const NodeType &roomcontainer_type,
    const NodeType &room_type,
    const float &room_width,
    const float &room_height,
    const EasyAxis2D &room_axis_in_parent)
{
    if(roomcontainer_type != NodeType::RoomContainer)
    {
        std::cout << "WorldController::createRoomForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troom_name = " << room_name << std::endl <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_width = " << room_width << std::endl <<
          "\troom_height = " << room_height << std::endl <<
          "\troom_axis_in_parent : " << std::endl;
        room_axis_in_parent.outputInfo(1);
        std::cout << "this type is not the roomcontainer type!" << std::endl;

        return false;
    }

    if(!haveThisNode(roomcontainer_id, roomcontainer_type))
    {
        std::cout << "WorldController::createRoomForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troom_name = " << room_name << std::endl <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_width = " << room_width << std::endl <<
          "\troom_height = " << room_height << std::endl <<
          "\troom_axis_in_parent : " << std::endl;
        room_axis_in_parent.outputInfo(1);
        std::cout << "roomcontainer node not exist!" << std::endl;

        return false;
    }

    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::createRoomForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troom_name = " << room_name << std::endl <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_width = " << room_width << std::endl <<
          "\troom_height = " << room_height << std::endl <<
          "\troom_axis_in_parent : " << std::endl;
        room_axis_in_parent.outputInfo(1);
        std::cout << "this type is not the room type!" << std::endl;

        return false;
    }

    if(room_width <= 0 || room_height <= 0)
    {
        std::cout << "WorldController::createRoomForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troom_name = " << room_name << std::endl <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_width = " << room_width << std::endl <<
          "\troom_height = " << room_height << std::endl <<
          "\troom_axis_in_parent : " << std::endl;
        room_axis_in_parent.outputInfo(1);
        std::cout << "this room size not valid!" << std::endl;

        return false;
    }

    bool find_exist_room = false;
    size_t new_room_id = 0;
    for(const std::pair<size_t, NodeType> &room_pair : room_pair_vec_)
    {
        if(room_pair.second != room_type)
        {
            continue;
        }

        new_room_id = std::max(new_room_id, room_pair.first);
        find_exist_room = true;
    }
    if(find_exist_room)
    {
        ++new_room_id;
    }

    if(!world_tree_.createNode(
          room_name, new_room_id, room_type, roomcontainer_id, roomcontainer_type, 0))
    {
        std::cout << "WorldController::createRoomForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troom_name = " << room_name << std::endl <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_width = " << room_width << std::endl <<
          "\troom_height = " << room_height << std::endl <<
          "\troom_axis_in_parent : " << std::endl;
        room_axis_in_parent.outputInfo(1);
        std::cout << "createNode for new room failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_room_pair;
    new_room_pair.first = new_room_id;
    new_room_pair.second = room_type;

    room_pair_vec_.emplace_back(new_room_pair);

    EasyPolygon2D room_node_boundary_polygon;
    room_node_boundary_polygon.point_list.resize(4);
    room_node_boundary_polygon.point_list[0].setPosition(0, 0);
    room_node_boundary_polygon.point_list[1].setPosition(room_width, 0);
    room_node_boundary_polygon.point_list[2].setPosition(room_width, room_height);
    room_node_boundary_polygon.point_list[3].setPosition(0, room_height);
    room_node_boundary_polygon.setAntiClockWise();

    if(!world_tree_.setNodeBoundaryPolygon(new_room_id, room_type, room_node_boundary_polygon))
    {
        std::cout << "WorldController::createRoomForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troom_name = " << room_name << std::endl <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_width = " << room_width << std::endl <<
          "\troom_height = " << room_height << std::endl <<
          "\troom_axis_in_parent : " << std::endl;
        room_axis_in_parent.outputInfo(1);
        std::cout << "setNodeBoundaryPolygon for new room failed!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisInParent(new_room_id, room_type, room_axis_in_parent, true))
    {
        std::cout << "WorldController::createRoomForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troom_name = " << room_name << std::endl <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_width = " << room_width << std::endl <<
          "\troom_height = " << room_height << std::endl <<
          "\troom_axis_in_parent : " << std::endl;
        room_axis_in_parent.outputInfo(1);
        std::cout << "setNodeAxisInParent for new room failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createRoomGroupForRoomContainer(
    const std::vector<std::string> &room_name_vec,
    const size_t &roomcontainer_id,
    const NodeType &roomcontainer_type,
    const NodeType &room_type,
    const size_t &room_x_direction_num)
{
    if(room_name_vec.size() != room_x_direction_num)
    {
        std::cout << "WorldController::createRoomGroupForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "room_name_vec size not match room_x_direction_num!" << std::endl;

        return false;
    }

    if(roomcontainer_type != NodeType::RoomContainer)
    {
        std::cout << "WorldController::createRoomGroupForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "this type is not the roomcontainer type!" << std::endl;

        return false;
    }

    EasyNode* search_node = findNode(roomcontainer_id, roomcontainer_type);

    if(search_node == nullptr)
    {
        std::cout << "WorldController::createRoomGroupForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "this roomcontainer node not exist!" << std::endl;

        return false;
    }

    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::createRoomGroupForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "this type is not the room type!" << std::endl;

        return false;
    }

    if(room_x_direction_num == 0)
    {
        std::cout << "WorldController::createRoomGroupForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "this room size not valid!" << std::endl;

        return false;
    }

    EasyNode* search_space_node = search_node->findChild(0, NodeType::Space);

    if(search_space_node == nullptr)
    {
        std::cout << "WorldController::createRoomGroupForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "roomcontainer space node not exist!" << std::endl;

        return false;
    }

    const EasyPolygon2D &search_space_boundary_polygon =
      search_space_node->getBoundaryPolygon();

    if(search_space_boundary_polygon.point_list.size() != 4)
    {
        std::cout << "WorldController::createRoomGroupForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "roomcontainer space boundary polygon size != 4!" << std::endl;

        return false;
    }

    const EasyPoint2D &roomcontainer_size = search_space_boundary_polygon.point_list[2];

    float room_x_length = roomcontainer_size.x / room_x_direction_num;
    float room_y_length = roomcontainer_size.y;

    EasyAxis2D room_axis;

    if(!room_axis.setXDirection(1, 0))
    {
        std::cout << "WorldController::createRoomGroupForRoomContainer : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_id = " << roomcontainer_id << std::endl <<
          "\troomcontainer_type = " << roomcontainer_type << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "setXDirection for room axis failed!" << std::endl;

        return false;
    }

    for(size_t i = 0; i < room_x_direction_num; ++i)
    {
        if(!room_axis.setCenter(i * room_x_length, 0))
        {
            std::cout << "WorldController::createRoomGroupForRoomContainer : " << std::endl <<
              "Input :\n" <<
              "\troomcontainer_id = " << roomcontainer_id << std::endl <<
              "\troomcontainer_type = " << roomcontainer_type << std::endl <<
              "\troom_type = " << room_type << std::endl <<
              "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
              "setCenter for room axis failed!" << std::endl;

            return false;
        }

        if(!createRoomForRoomContainer(
              room_name_vec[i], roomcontainer_id, roomcontainer_type, room_type, room_x_length, room_y_length, room_axis))
        {
            std::cout << "WorldController::createRoomGroupForRoomContainer : " << std::endl <<
              "Input :\n" <<
              "\troomcontainer_id = " << roomcontainer_id << std::endl <<
              "\troomcontainer_type = " << roomcontainer_type << std::endl <<
              "\troom_type = " << room_type << std::endl <<
              "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
              "createRoomForRoomContainer for new room failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool WorldController::createRoomContainerForWall(
    const std::string &roomcontainer_name,
    const std::vector<std::string> &room_name_vec,
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &wall_boundary_id,
    const float &roomcontainer_width,
    const float &roomcontainer_height,
    const EasyAxis2D &roomcontainer_axis_in_parent,
    const NodeType &room_type,
    const size_t &room_x_direction_num)
{
    if(room_name_vec.size() != room_x_direction_num)
    {
        std::cout << "WorldController::createRoomContainerForWall : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "\troomcontainer_axis_in_parent : " << std::endl;
        roomcontainer_axis_in_parent.outputInfo(1);
        std::cout << "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "room_name_vec size not match room_x_direction_num!" << std::endl;

        return false;
    }

    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "WorldController::createRoomContainerForWall : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "\troomcontainer_axis_in_parent : " << std::endl;
        roomcontainer_axis_in_parent.outputInfo(1);
        std::cout << "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "this type is not the wall type!" << std::endl;

        return false;
    }

    if(!haveThisNode(wall_id, wall_type))
    {
        std::cout << "WorldController::createRoomContainerForWall : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "\troomcontainer_axis_in_parent : " << std::endl;
        roomcontainer_axis_in_parent.outputInfo(1);
        std::cout << "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "wall node not exist!" << std::endl;

        return false;
    }

    if(roomcontainer_width <= 0 || roomcontainer_height <= 0)
    {
        std::cout << "WorldController::createRoomContainerForWall : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "\troomcontainer_axis_in_parent : " << std::endl;
        roomcontainer_axis_in_parent.outputInfo(1);
        std::cout << "\troom_type = " << room_type << std::endl <<
          "this roomcontainer size not valid!" << std::endl;

        return false;
    }

    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::createRoomContainerForWall : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "\troomcontainer_axis_in_parent : " << std::endl;
        roomcontainer_axis_in_parent.outputInfo(1);
        std::cout << "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "this type is not the room type!" << std::endl;

        return false;
    }

    bool find_exist_roomcontainer = false;
    size_t new_roomcontainer_id = 0;
    for(const std::pair<size_t, NodeType> &roomcontainer_pair : roomcontainer_pair_vec_)
    {
        if(roomcontainer_pair.second != NodeType::RoomContainer)
        {
            continue;
        }

        new_roomcontainer_id = std::max(new_roomcontainer_id, roomcontainer_pair.first);
        find_exist_roomcontainer = true;
    }
    if(find_exist_roomcontainer)
    {
        ++new_roomcontainer_id;
    }

    if(!world_tree_.createNode(
          roomcontainer_name, new_roomcontainer_id, NodeType::RoomContainer, wall_id, wall_type, wall_boundary_id))
    {
        std::cout << "WorldController::createRoomContainerForWall : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "\troomcontainer_axis_in_parent : " << std::endl;
        roomcontainer_axis_in_parent.outputInfo(1);
        std::cout << "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "createNode for new roomcontainer failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_roomcontainer_pair;
    new_roomcontainer_pair.first = new_roomcontainer_id;
    new_roomcontainer_pair.second = NodeType::RoomContainer;

    roomcontainer_pair_vec_.emplace_back(new_roomcontainer_pair);

    EasyPolygon2D roomcontainer_node_boundary_polygon;
    roomcontainer_node_boundary_polygon.point_list.resize(4);
    roomcontainer_node_boundary_polygon.point_list[0].setPosition(0, 0);
    roomcontainer_node_boundary_polygon.point_list[1].setPosition(roomcontainer_width, 0);
    roomcontainer_node_boundary_polygon.point_list[2].setPosition(roomcontainer_width, roomcontainer_height);
    roomcontainer_node_boundary_polygon.point_list[3].setPosition(0, roomcontainer_height);
    roomcontainer_node_boundary_polygon.setAntiClockWise();

    if(!world_tree_.setNodeBoundaryPolygon(new_roomcontainer_id, NodeType::RoomContainer, roomcontainer_node_boundary_polygon))
    {
        std::cout << "WorldController::createRoomContainerForWall : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "\troomcontainer_axis_in_parent : " << std::endl;
        roomcontainer_axis_in_parent.outputInfo(1);
        std::cout << "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "setNodeBoundaryPolygon for new roomcontainer failed!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisInParent(new_roomcontainer_id, NodeType::RoomContainer, roomcontainer_axis_in_parent, true))
    {
        std::cout << "WorldController::createRoomContainerForWall : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "\troomcontainer_axis_in_parent : " << std::endl;
        roomcontainer_axis_in_parent.outputInfo(1);
        std::cout << "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "setNodeAxisInParent for new roomcontainer failed!" << std::endl;

        return false;
    }

    if(!createRoomGroupForRoomContainer(
          room_name_vec,
          new_roomcontainer_id,
          NodeType::RoomContainer,
          room_type,
          room_x_direction_num))
    {
        std::cout << "WorldController::createRoomContainerForWall : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "\troomcontainer_axis_in_parent : " << std::endl;
        roomcontainer_axis_in_parent.outputInfo(1);
        std::cout << "\troom_type = " << room_type << std::endl <<
          "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "createRoomGroupForRoomContainer for new roomcontainer failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createWallRoomContainerForWall(
    const std::string &roomcontainer_name,
    const std::vector<std::string> &room_name_vec,
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &wall_boundary_id,
    const float &roomcontainer_width,
    const float &roomcontainer_height,
    const EasyAxis2D &roomcontainer_axis_in_parent,
    const size_t &room_x_direction_num)
{
    if(!createRoomContainerForWall(
          roomcontainer_name,
          room_name_vec,
          wall_id,
          wall_type,
          wall_boundary_id,
          roomcontainer_width,
          roomcontainer_height,
          roomcontainer_axis_in_parent,
          NodeType::WallRoom,
          room_x_direction_num))
    {
        std::cout << "WorldController::createWallRoomContainerForWall : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "\troomcontainer_axis_in_parent : " << std::endl;
        roomcontainer_axis_in_parent.outputInfo(1);
        std::cout << "\troom_x_direction_num = " << room_x_direction_num << std::endl <<
          "createRoomGroupForRoomContainer for new roomcontainer failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createFreeRoomContainerForWall(
    const std::string &roomcontainer_name,
    const std::vector<std::string> &room_name_vec,
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &wall_boundary_id,
    const float &roomcontainer_width,
    const float &roomcontainer_height,
    const EasyAxis2D &roomcontainer_axis_in_parent,
    const size_t &room_x_direction_num)
{
    if(!createRoomContainerForWall(
          roomcontainer_name,
          room_name_vec,
          wall_id,
          wall_type,
          wall_boundary_id,
          roomcontainer_width,
          roomcontainer_height,
          roomcontainer_axis_in_parent,
          NodeType::FreeRoom,
          room_x_direction_num))
    {
        std::cout << "WorldController::createFreeRoomContainerForWall : " << std::endl <<
          "Input :\n" <<
          "\troomcontainer_name = " << roomcontainer_name << std::endl <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "\troomcontainer_width = " << roomcontainer_width << std::endl <<
          "\troomcontainer_height = " << roomcontainer_height << std::endl <<
          "\troomcontainer_axis_in_parent : " << std::endl;
        roomcontainer_axis_in_parent.outputInfo(1);
        std::cout << "createRoomGroupForRoomContainer for new roomcontainer failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createWallForWorld(
    const std::string &wall_name,
    const EasyAxis2D &wall_axis_in_parent,
    const NodeType &wall_type,
    const EasyPolygon2D &wall_boundary_polygon)
{
    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "WorldController::createWallForWorld : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "\twall_axis_in_parent :" << std::endl;
        wall_axis_in_parent.outputInfo(1);
        std::cout << "\twall_type = " << wall_type << std::endl <<
          "wall_type is not the wall type!" << std::endl;

        return false;
    }

    if(wall_boundary_polygon.point_list.size() < 3)
    {
        std::cout << "WorldController::createWallForWorld : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "\twall_axis_in_parent :" << std::endl;
        wall_axis_in_parent.outputInfo(1);
        std::cout << "\twall_type = " << wall_type << std::endl <<
          "wall_boundary_polygon size not valid!" << std::endl;

        return false;
    }

    bool find_exist_wall = false;
    size_t new_wall_id = 0;
    for(const std::pair<size_t, NodeType> &wall_pair : wall_pair_vec_)
    {
        if(wall_pair.second != wall_type)
        {
            continue;
        }

        new_wall_id = std::max(new_wall_id, wall_pair.first);
        find_exist_wall = true;
    }
    if(find_exist_wall)
    {
        ++new_wall_id;
    }

    if(!world_tree_.createNode(
          wall_name, new_wall_id, wall_type, 0, NodeType::World, 0))
    {
        std::cout << "WorldController::createWallForWorld : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "\twall_axis_in_parent :" << std::endl;
        wall_axis_in_parent.outputInfo(1);
        std::cout << "\twall_type = " << wall_type << std::endl <<
          "createNode for new wall failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_wall_pair;
    new_wall_pair.first = new_wall_id;
    new_wall_pair.second = wall_type;

    wall_pair_vec_.emplace_back(new_wall_pair);

    if(!world_tree_.setNodeBoundaryPolygon(new_wall_id, wall_type, wall_boundary_polygon))
    {
        std::cout << "WorldController::createWallForWorld : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "\twall_axis_in_parent :" << std::endl;
        wall_axis_in_parent.outputInfo(1);
        std::cout << "\twall_type = " << wall_type << std::endl <<
          "setNodeBoundaryPolygon for new wall failed!" << std::endl;

        return false;
    }

    if(!world_tree_.setNodeAxisInParent(new_wall_id, wall_type, wall_axis_in_parent, true))
    {
        std::cout << "WorldController::createWallForWorld : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "\twall_axis_in_parent :" << std::endl;
        wall_axis_in_parent.outputInfo(1);
        std::cout << "\twall_type = " << wall_type << std::endl <<
          "setNodeAxisInParent for new wall failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createInnerWallForWorld(
    const std::string &wall_name,
    const EasyAxis2D &wall_axis_in_parent,
    const EasyPolygon2D &wall_boundary_polygon)
{
    if(!createWallForWorld(
          wall_name,
          wall_axis_in_parent,
          NodeType::InnerWall,
          wall_boundary_polygon))
    {
        std::cout << "WorldController::createInnerWallForWorld : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "\twall_axis_in_parent :" << std::endl;
        wall_axis_in_parent.outputInfo(1);
        std::cout <<
          "createWallForWorld failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createOuterWallForWorld(
    const std::string &wall_name,
    const EasyAxis2D &wall_axis_in_parent,
    const EasyPolygon2D &wall_boundary_polygon)
{
    if(!createWallForWorld(
          wall_name,
          wall_axis_in_parent,
          NodeType::OuterWall,
          wall_boundary_polygon))
    {
        std::cout << "WorldController::createOuterWallForWorld : " << std::endl <<
          "Input :\n" <<
          "\twall_name = " << wall_name << std::endl <<
          "\twall_axis_in_parent :" << std::endl;
        wall_axis_in_parent.outputInfo(1);
        std::cout <<
          "createWallForWorld failed!" << std::endl;

        return false;
    }

    return true;
}

EasyNode* WorldController::findNode(
    const size_t &node_id,
    const NodeType &node_type)
{
    EasyNode* search_node = world_tree_.findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "WorldController::findNode :" << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "can't find this node!" << std::endl;

        return nullptr;
    }

    return search_node;
}

bool WorldController::haveThisNode(
    const size_t &node_id,
    const NodeType &node_type)
{
    EasyNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        return false;
    }

    return true;
}

bool WorldController::getWallNodeVec(
    std::vector<EasyNode*> &wall_node_vec)
{
    wall_node_vec.clear();

    if(wall_pair_vec_.size() == 0)
    {
        return true;
    }

    for(const std::pair<size_t, NodeType> &wall_pair : wall_pair_vec_)
    {
        EasyNode* wall_node = findNode(wall_pair.first, wall_pair.second);

        if(wall_node == nullptr)
        {
            std::cout << "WorldController::getWallNodeVec : " << std::endl <<
              "get wall : id = " << wall_pair.first <<
              ", type = " << wall_pair.second <<
              " failed!" << std::endl;

            return false;
        }

        wall_node_vec.emplace_back(wall_node);
    }

    return true;
}

bool WorldController::getWallBoundaryNodeVecVec(
    std::vector<std::vector<EasyNode*>> &wall_boundary_node_vec_vec)
{
    wall_boundary_node_vec_vec.clear();

    if(wall_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> wall_node_vec;

    if(!getWallNodeVec(wall_node_vec))
    {
        std::cout << "WorldController::getWallBoundaryNodeVec : " << std::endl <<
          "getWallNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* wall_node : wall_node_vec)
    {
        std::vector<EasyNode*> wall_boundary_node_vec;
        std::vector<EasyNode*> wall_child_node_vec = wall_node->getChildNodeVec();

        for(EasyNode* wall_child_node : wall_child_node_vec)
        {
            if(wall_child_node->getNodeType() == NodeType::Boundary)
            {
                wall_boundary_node_vec.emplace_back(wall_child_node);
            }
        }

        wall_boundary_node_vec_vec.emplace_back(wall_boundary_node_vec);
    }
    return true;
}

bool WorldController::getWallSpaceNodeVec(
    std::vector<EasyNode*> &wall_space_node_vec)
{
    wall_space_node_vec.clear();

    if(wall_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> wall_node_vec;

    if(!getWallNodeVec(wall_node_vec))
    {
        std::cout << "WorldController::getWallSpaceNodeVec : " << std::endl <<
          "getWallNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* wall_node : wall_node_vec)
    {
        EasyNode* wall_space_node = wall_node->findChild(0, NodeType::Space);

        if(wall_space_node == nullptr)
        {
            std::cout << "WorldController::getWallNodeVec : " << std::endl <<
              "get wall space node failed!" << std::endl;

            return false;
        }

        wall_space_node_vec.emplace_back(wall_space_node);
    }

    return true;
}

bool WorldController::getRoomContainerNodeVec(
    std::vector<EasyNode*> &roomcontainer_node_vec)
{
    roomcontainer_node_vec.clear();

    if(roomcontainer_pair_vec_.size() == 0)
    {
        return true;
    }

    for(const std::pair<size_t, NodeType> &roomcontainer_pair : roomcontainer_pair_vec_)
    {
        EasyNode* roomcontainer_node = findNode(roomcontainer_pair.first, roomcontainer_pair.second);

        if(roomcontainer_node == nullptr)
        {
            std::cout << "WorldController::getRoomContainerNodeVec : " << std::endl <<
              "get roomcontainer : id = " << roomcontainer_pair.first <<
              ", type = " << roomcontainer_pair.second <<
              " failed!" << std::endl;

            return false;
        }

        roomcontainer_node_vec.emplace_back(roomcontainer_node);
    }

    return true;
}

bool WorldController::getRoomContainerBoundaryNodeVecVec(
    std::vector<std::vector<EasyNode*>> &roomcontainer_boundary_node_vec_vec)
{
    roomcontainer_boundary_node_vec_vec.clear();

    if(roomcontainer_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> roomcontainer_node_vec;

    if(!getRoomContainerNodeVec(roomcontainer_node_vec))
    {
        std::cout << "WorldController::getRoomContainerBoundaryNodeVec : " << std::endl <<
          "getRoomContainerNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* roomcontainer_node : roomcontainer_node_vec)
    {
        std::vector<EasyNode*> roomcontainer_boundary_node_vec;
        std::vector<EasyNode*> roomcontainer_child_node_vec = roomcontainer_node->getChildNodeVec();

        for(EasyNode* roomcontainer_child_node : roomcontainer_child_node_vec)
        {
            if(roomcontainer_child_node->getNodeType() == NodeType::Boundary)
            {
                roomcontainer_boundary_node_vec.emplace_back(roomcontainer_child_node);
            }
        }

        roomcontainer_boundary_node_vec_vec.emplace_back(roomcontainer_boundary_node_vec);
    }
    return true;
}

bool WorldController::getRoomContainerSpaceNodeVec(
    std::vector<EasyNode*> &roomcontainer_space_node_vec)
{
    roomcontainer_space_node_vec.clear();

    if(roomcontainer_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> roomcontainer_node_vec;

    if(!getRoomContainerNodeVec(roomcontainer_node_vec))
    {
        std::cout << "WorldController::getRoomContainerSpaceNodeVec : " << std::endl <<
          "getRoomContainerNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* roomcontainer_node : roomcontainer_node_vec)
    {
        EasyNode* roomcontainer_space_node = roomcontainer_node->findChild(0, NodeType::Space);

        if(roomcontainer_space_node == nullptr)
        {
            std::cout << "WorldController::getRoomContainerNodeVec : " << std::endl <<
              "get roomcontainer space node failed!" << std::endl;

            return false;
        }

        roomcontainer_space_node_vec.emplace_back(roomcontainer_space_node);
    }

    return true;
}

bool WorldController::getWallRoomNodeVec(
    std::vector<EasyNode*> &wallroom_node_vec)
{
    wallroom_node_vec.clear();

    if(room_pair_vec_.size() == 0)
    {
        return true;
    }

    for(const std::pair<size_t, NodeType> &wallroom_pair : room_pair_vec_)
    {
        if(wallroom_pair.second != NodeType::WallRoom)
        {
            continue;
        }

        EasyNode* wallroom_node = findNode(wallroom_pair.first, wallroom_pair.second);

        if(wallroom_node == nullptr)
        {
            std::cout << "WorldController::getWallRoomNodeVec : " << std::endl <<
              "get wallroom : id = " << wallroom_pair.first <<
              ", type = " << wallroom_pair.second <<
              " failed!" << std::endl;

            return false;
        }

        wallroom_node_vec.emplace_back(wallroom_node);
    }

    return true;
}

bool WorldController::getWallRoomBoundaryNodeVecVec(
    std::vector<std::vector<EasyNode*>> &wallroom_boundary_node_vec_vec)
{
    wallroom_boundary_node_vec_vec.clear();

    if(room_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> wallroom_node_vec;

    if(!getWallRoomNodeVec(wallroom_node_vec))
    {
        std::cout << "WorldController::getWallRoomBoundaryNodeVec : " << std::endl <<
          "getWallRoomNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* wallroom_node : wallroom_node_vec)
    {
        std::vector<EasyNode*> wallroom_boundary_node_vec;
        std::vector<EasyNode*> wallroom_child_node_vec = wallroom_node->getChildNodeVec();

        for(EasyNode* wallroom_child_node : wallroom_child_node_vec)
        {
            if(wallroom_child_node->getNodeType() == NodeType::Boundary)
            {
                wallroom_boundary_node_vec.emplace_back(wallroom_child_node);
            }
        }

        wallroom_boundary_node_vec_vec.emplace_back(wallroom_boundary_node_vec);
    }
    return true;
}

bool WorldController::getWallRoomSpaceNodeVec(
    std::vector<EasyNode*> &wallroom_space_node_vec)
{
    wallroom_space_node_vec.clear();

    if(room_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> wallroom_node_vec;

    if(!getWallRoomNodeVec(wallroom_node_vec))
    {
        std::cout << "WorldController::getWallRoomSpaceNodeVec : " << std::endl <<
          "getWallRoomNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* wallroom_node : wallroom_node_vec)
    {
        EasyNode* wallroom_space_node = wallroom_node->findChild(0, NodeType::Space);

        if(wallroom_space_node == nullptr)
        {
            std::cout << "WorldController::getWallRoomNodeVec : " << std::endl <<
              "get wallroom space node failed!" << std::endl;

            return false;
        }

        wallroom_space_node_vec.emplace_back(wallroom_space_node);
    }

    return true;
}

bool WorldController::getFreeRoomNodeVec(
    std::vector<EasyNode*> &freeroom_node_vec)
{
    freeroom_node_vec.clear();

    if(room_pair_vec_.size() == 0)
    {
        return true;
    }

    for(const std::pair<size_t, NodeType> &freeroom_pair : room_pair_vec_)
    {
        if(freeroom_pair.second != NodeType::FreeRoom)
        {
            continue;
        }

        EasyNode* freeroom_node = findNode(freeroom_pair.first, freeroom_pair.second);

        if(freeroom_node == nullptr)
        {
            std::cout << "WorldController::getFreeRoomNodeVec : " << std::endl <<
              "get freeroom : id = " << freeroom_pair.first <<
              ", type = " << freeroom_pair.second <<
              " failed!" << std::endl;

            return false;
        }

        freeroom_node_vec.emplace_back(freeroom_node);
    }

    return true;
}

bool WorldController::getFreeRoomBoundaryNodeVecVec(
    std::vector<std::vector<EasyNode*>> &freeroom_boundary_node_vec_vec)
{
    freeroom_boundary_node_vec_vec.clear();

    if(room_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> freeroom_node_vec;

    if(!getFreeRoomNodeVec(freeroom_node_vec))
    {
        std::cout << "WorldController::getFreeRoomBoundaryNodeVec : " << std::endl <<
          "getFreeRoomNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* freeroom_node : freeroom_node_vec)
    {
        std::vector<EasyNode*> freeroom_boundary_node_vec;
        std::vector<EasyNode*> freeroom_child_node_vec = freeroom_node->getChildNodeVec();

        for(EasyNode* freeroom_child_node : freeroom_child_node_vec)
        {
            if(freeroom_child_node->getNodeType() == NodeType::Boundary)
            {
                freeroom_boundary_node_vec.emplace_back(freeroom_child_node);
            }
        }

        freeroom_boundary_node_vec_vec.emplace_back(freeroom_boundary_node_vec);
    }
    return true;
}

bool WorldController::getFreeRoomSpaceNodeVec(
    std::vector<EasyNode*> &freeroom_space_node_vec)
{
    freeroom_space_node_vec.clear();

    if(room_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> freeroom_node_vec;

    if(!getFreeRoomNodeVec(freeroom_node_vec))
    {
        std::cout << "WorldController::getFreeRoomSpaceNodeVec : " << std::endl <<
          "getFreeRoomNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* freeroom_node : freeroom_node_vec)
    {
        EasyNode* freeroom_space_node = freeroom_node->findChild(0, NodeType::Space);

        if(freeroom_space_node == nullptr)
        {
            std::cout << "WorldController::getFreeRoomNodeVec : " << std::endl <<
              "get freeroom space node failed!" << std::endl;

            return false;
        }

        freeroom_space_node_vec.emplace_back(freeroom_space_node);
    }

    return true;
}

bool WorldController::getDoorNodeVec(
    std::vector<EasyNode*> &door_node_vec)
{
    door_node_vec.clear();

    if(door_pair_vec_.size() == 0)
    {
        return true;
    }

    for(const std::pair<size_t, NodeType> &door_pair : door_pair_vec_)
    {
        EasyNode* door_node = findNode(door_pair.first, door_pair.second);

        if(door_node == nullptr)
        {
            std::cout << "WorldController::getDoorNodeVec : " << std::endl <<
              "get door : id = " << door_pair.first <<
              ", type = " << door_pair.second <<
              " failed!" << std::endl;

            return false;
        }

        door_node_vec.emplace_back(door_node);
    }

    return true;
}

bool WorldController::getDoorBoundaryNodeVecVec(
    std::vector<std::vector<EasyNode*>> &door_boundary_node_vec_vec)
{
    door_boundary_node_vec_vec.clear();

    if(door_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> door_node_vec;

    if(!getDoorNodeVec(door_node_vec))
    {
        std::cout << "WorldController::getDoorBoundaryNodeVec : " << std::endl <<
          "getDoorNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* door_node : door_node_vec)
    {
        std::vector<EasyNode*> door_boundary_node_vec;
        std::vector<EasyNode*> door_child_node_vec = door_node->getChildNodeVec();

        for(EasyNode* door_child_node : door_child_node_vec)
        {
            if(door_child_node->getNodeType() == NodeType::Boundary)
            {
                door_boundary_node_vec.emplace_back(door_child_node);
            }
        }

        door_boundary_node_vec_vec.emplace_back(door_boundary_node_vec);
    }
    return true;
}

bool WorldController::getDoorSpaceNodeVec(
    std::vector<EasyNode*> &door_space_node_vec)
{
    door_space_node_vec.clear();

    if(door_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> door_node_vec;

    if(!getDoorNodeVec(door_node_vec))
    {
        std::cout << "WorldController::getDoorSpaceNodeVec : " << std::endl <<
          "getDoorNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* door_node : door_node_vec)
    {
        EasyNode* door_space_node = door_node->findChild(0, NodeType::Space);

        if(door_space_node == nullptr)
        {
            std::cout << "WorldController::getDoorNodeVec : " << std::endl <<
              "get door space node failed!" << std::endl;

            return false;
        }

        door_space_node_vec.emplace_back(door_space_node);
    }

    return true;
}

bool WorldController::getWindowNodeVec(
    std::vector<EasyNode*> &window_node_vec)
{
    window_node_vec.clear();

    if(window_pair_vec_.size() == 0)
    {
        return true;
    }

    for(const std::pair<size_t, NodeType> &window_pair : window_pair_vec_)
    {
        EasyNode* window_node = findNode(window_pair.first, window_pair.second);

        if(window_node == nullptr)
        {
            std::cout << "WorldController::getWindowNodeVec : " << std::endl <<
              "get window : id = " << window_pair.first <<
              ", type = " << window_pair.second <<
              " failed!" << std::endl;

            return false;
        }

        window_node_vec.emplace_back(window_node);
    }

    return true;
}

bool WorldController::getWindowBoundaryNodeVecVec(
    std::vector<std::vector<EasyNode*>> &window_boundary_node_vec_vec)
{
    window_boundary_node_vec_vec.clear();

    if(window_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> window_node_vec;

    if(!getWindowNodeVec(window_node_vec))
    {
        std::cout << "WorldController::getWindowBoundaryNodeVec : " << std::endl <<
          "getWindowNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* window_node : window_node_vec)
    {
        std::vector<EasyNode*> window_boundary_node_vec;
        std::vector<EasyNode*> window_child_node_vec = window_node->getChildNodeVec();

        for(EasyNode* window_child_node : window_child_node_vec)
        {
            if(window_child_node->getNodeType() == NodeType::Boundary)
            {
                window_boundary_node_vec.emplace_back(window_child_node);
            }
        }

        window_boundary_node_vec_vec.emplace_back(window_boundary_node_vec);
    }
    return true;
}

bool WorldController::getWindowSpaceNodeVec(
    std::vector<EasyNode*> &window_space_node_vec)
{
    window_space_node_vec.clear();

    if(window_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> window_node_vec;

    if(!getWindowNodeVec(window_node_vec))
    {
        std::cout << "WorldController::getWindowSpaceNodeVec : " << std::endl <<
          "getWindowNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* window_node : window_node_vec)
    {
        EasyNode* window_space_node = window_node->findChild(0, NodeType::Space);

        if(window_space_node == nullptr)
        {
            std::cout << "WorldController::getWindowNodeVec : " << std::endl <<
              "get window space node failed!" << std::endl;

            return false;
        }

        window_space_node_vec.emplace_back(window_space_node);
    }

    return true;
}

bool WorldController::getTeamNodeVec(
    std::vector<EasyNode*> &team_node_vec)
{
    team_node_vec.clear();

    if(team_pair_vec_.size() == 0)
    {
        return true;
    }

    for(const std::pair<size_t, NodeType> &team_pair : team_pair_vec_)
    {
        EasyNode* team_node = findNode(team_pair.first, team_pair.second);

        if(team_node == nullptr)
        {
            std::cout << "WorldController::getTeamNodeVec : " << std::endl <<
              "get team : id = " << team_pair.first <<
              ", type = " << team_pair.second <<
              " failed!" << std::endl;

            return false;
        }

        team_node_vec.emplace_back(team_node);
    }

    return true;
}

bool WorldController::getTeamBoundaryNodeVecVec(
    std::vector<std::vector<EasyNode*>> &team_boundary_node_vec_vec)
{
    team_boundary_node_vec_vec.clear();

    if(team_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> team_node_vec;

    if(!getTeamNodeVec(team_node_vec))
    {
        std::cout << "WorldController::getTeamBoundaryNodeVec : " << std::endl <<
          "getTeamNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* team_node : team_node_vec)
    {
        std::vector<EasyNode*> team_boundary_node_vec;
        std::vector<EasyNode*> team_child_node_vec = team_node->getChildNodeVec();

        for(EasyNode* team_child_node : team_child_node_vec)
        {
            if(team_child_node->getNodeType() == NodeType::Boundary)
            {
                team_boundary_node_vec.emplace_back(team_child_node);
            }
        }

        team_boundary_node_vec_vec.emplace_back(team_boundary_node_vec);
    }
    return true;
}

bool WorldController::getTeamSpaceNodeVec(
    std::vector<EasyNode*> &team_space_node_vec)
{
    team_space_node_vec.clear();

    if(team_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> team_node_vec;

    if(!getTeamNodeVec(team_node_vec))
    {
        std::cout << "WorldController::getTeamSpaceNodeVec : " << std::endl <<
          "getTeamNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* team_node : team_node_vec)
    {
        EasyNode* team_space_node = team_node->findChild(0, NodeType::Space);

        if(team_space_node == nullptr)
        {
            std::cout << "WorldController::getTeamNodeVec : " << std::endl <<
              "get team space node failed!" << std::endl;

            return false;
        }

        team_space_node_vec.emplace_back(team_space_node);
    }

    return true;
}

bool WorldController::getPersonNodeVec(
    std::vector<EasyNode*> &person_node_vec)
{
    person_node_vec.clear();

    if(person_pair_vec_.size() == 0)
    {
        return true;
    }

    for(const std::pair<size_t, NodeType> &person_pair : person_pair_vec_)
    {
        EasyNode* person_node = findNode(person_pair.first, person_pair.second);

        if(person_node == nullptr)
        {
            std::cout << "WorldController::getPersonNodeVec : " << std::endl <<
              "get person : id = " << person_pair.first <<
              ", type = " << person_pair.second <<
              " failed!" << std::endl;

            return false;
        }

        person_node_vec.emplace_back(person_node);
    }

    return true;
}

bool WorldController::getPersonBoundaryNodeVecVec(
    std::vector<std::vector<EasyNode*>> &person_boundary_node_vec_vec)
{
    person_boundary_node_vec_vec.clear();

    if(person_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> person_node_vec;

    if(!getPersonNodeVec(person_node_vec))
    {
        std::cout << "WorldController::getPersonBoundaryNodeVec : " << std::endl <<
          "getPersonNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* person_node : person_node_vec)
    {
        std::vector<EasyNode*> person_boundary_node_vec;
        std::vector<EasyNode*> person_child_node_vec = person_node->getChildNodeVec();

        for(EasyNode* person_child_node : person_child_node_vec)
        {
            if(person_child_node->getNodeType() == NodeType::Boundary)
            {
                person_boundary_node_vec.emplace_back(person_child_node);
            }
        }

        person_boundary_node_vec_vec.emplace_back(person_boundary_node_vec);
    }
    return true;
}

bool WorldController::getPersonSpaceNodeVec(
    std::vector<EasyNode*> &person_space_node_vec)
{
    person_space_node_vec.clear();

    if(person_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> person_node_vec;

    if(!getPersonNodeVec(person_node_vec))
    {
        std::cout << "WorldController::getPersonSpaceNodeVec : " << std::endl <<
          "getPersonNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* person_node : person_node_vec)
    {
        EasyNode* person_space_node = person_node->findChild(0, NodeType::Space);

        if(person_space_node == nullptr)
        {
            std::cout << "WorldController::getPersonNodeVec : " << std::endl <<
              "get person space node failed!" << std::endl;

            return false;
        }

        person_space_node_vec.emplace_back(person_space_node);
    }

    return true;
}

bool WorldController::getFurnitureNodeVec(
    std::vector<EasyNode*> &furniture_node_vec)
{
    furniture_node_vec.clear();

    if(furniture_pair_vec_.size() == 0)
    {
        return true;
    }

    for(const std::pair<size_t, NodeType> &furniture_pair : furniture_pair_vec_)
    {
        EasyNode* furniture_node = findNode(furniture_pair.first, furniture_pair.second);

        if(furniture_node == nullptr)
        {
            std::cout << "WorldController::getFurnitureNodeVec : " << std::endl <<
              "get furniture : id = " << furniture_pair.first <<
              ", type = " << furniture_pair.second <<
              " failed!" << std::endl;

            return false;
        }

        furniture_node_vec.emplace_back(furniture_node);
    }

    return true;
}

bool WorldController::getFurnitureBoundaryNodeVecVec(
    std::vector<std::vector<EasyNode*>> &furniture_boundary_node_vec_vec)
{
    furniture_boundary_node_vec_vec.clear();

    if(furniture_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> furniture_node_vec;

    if(!getFurnitureNodeVec(furniture_node_vec))
    {
        std::cout << "WorldController::getFurnitureBoundaryNodeVec : " << std::endl <<
          "getFurnitureNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* furniture_node : furniture_node_vec)
    {
        std::vector<EasyNode*> furniture_boundary_node_vec;
        std::vector<EasyNode*> furniture_child_node_vec = furniture_node->getChildNodeVec();

        for(EasyNode* furniture_child_node : furniture_child_node_vec)
        {
            if(furniture_child_node->getNodeType() == NodeType::Boundary)
            {
                furniture_boundary_node_vec.emplace_back(furniture_child_node);
            }
        }

        furniture_boundary_node_vec_vec.emplace_back(furniture_boundary_node_vec);
    }
    return true;
}

bool WorldController::getFurnitureSpaceNodeVec(
    std::vector<EasyNode*> &furniture_space_node_vec)
{
    furniture_space_node_vec.clear();

    if(furniture_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> furniture_node_vec;

    if(!getFurnitureNodeVec(furniture_node_vec))
    {
        std::cout << "WorldController::getFurnitureSpaceNodeVec : " << std::endl <<
          "getFurnitureNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* furniture_node : furniture_node_vec)
    {
        EasyNode* furniture_space_node = furniture_node->findChild(0, NodeType::Space);

        if(furniture_space_node == nullptr)
        {
            std::cout << "WorldController::getFurnitureNodeVec : " << std::endl <<
              "get furniture space node failed!" << std::endl;

            return false;
        }

        furniture_space_node_vec.emplace_back(furniture_space_node);
    }

    return true;
}


bool WorldController::outputInfo()
{
    world_tree_.outputInfo();

    return true;
}

