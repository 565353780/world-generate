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

    return true;
}

bool WorldController::createWorld(
    const float &world_center_x,
    const float &world_center_y)
{
    if(!world_tree_.createWorld(world_center_x, world_center_y))
    {
        std::cout << "WorldController::createWorld : " << std::endl <<
          "Input :\n" <<
          "\tworld_center = [" << world_center_x << "," <<
          world_center_y << "]" << std::endl <<
          "createWorld failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldController::createWall(
    const size_t &wall_id,
    const NodeType &wall_type)
{
    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "WorldController::createWall : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "this type is not the wall type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          wall_id, wall_type, 0, NodeType::World, 0))
    {
        std::cout << "WorldController::createWall : " << std::endl <<
          "Input :\n" <<
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
          true))
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

bool WorldController::createRoom(
    const size_t &room_id,
    const NodeType &room_type,
    const size_t &on_wall_id,
    const NodeType &on_wall_type,
    const size_t &wall_boundary_id)
{
    if(room_type != NodeType::WallRoom &&
        room_type != NodeType::FreeRoom)
    {
        std::cout << "WorldController::createRoom : " << std::endl <<
          "Input :\n" <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_wall_id = " << on_wall_id << std::endl <<
          "\ton_wall_type = " << on_wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
          "this type is not the room type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          room_id, room_type, on_wall_id, on_wall_type, wall_boundary_id))
    {
        std::cout << "WorldController::createRoom : " << std::endl <<
          "Input :\n" <<
          "\troom_id = " << room_id << std::endl <<
          "\troom_type = " << room_type << std::endl <<
          "\ton_wall_id = " << on_wall_id << std::endl <<
          "\ton_wall_type = " << on_wall_type << std::endl <<
          "\twall_boundary_id = " << wall_boundary_id << std::endl <<
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
          room_type == NodeType::FreeRoom))
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
          room_type == NodeType::FreeRoom))
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

bool WorldController::createTeam(
    const size_t &team_id,
    const NodeType &team_type,
    const size_t &on_room_id,
    const NodeType &on_room_type)
{
    if(team_type != NodeType::Team)
    {
        std::cout << "WorldController::createTeam : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\ton_room_id = " << on_room_id << std::endl <<
          "\ton_room_type = " << on_room_type << std::endl <<
          "this type is not the team type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          team_id, team_type, on_room_id, on_room_type, 0))
    {
        std::cout << "WorldController::createTeam : " << std::endl <<
          "Input :\n" <<
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
          true))
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
    const size_t &person_id,
    const NodeType &person_type,
    const size_t &on_team_id,
    const NodeType &on_team_type)
{
    if(person_type != NodeType::Person)
    {
        std::cout << "WorldController::createPerson : " << std::endl <<
          "Input :\n" <<
          "\tperson_id = " << person_id << std::endl <<
          "\tperson_type = " << person_type << std::endl <<
          "\ton_team_id = " << on_team_id << std::endl <<
          "\ton_team_type = " << on_team_type << std::endl <<
          "this type is not the person type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          person_id, person_type, on_team_id, on_team_type, 0))
    {
        std::cout << "WorldController::createPerson : " << std::endl <<
          "Input :\n" <<
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
          true))
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
          true))
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

bool WorldController::createPersonForTeam(
    const size_t &team_id,
    const size_t &team_type,
    const EasyAxis2D &person_axis_in_parent)
{
    if(team_type != NodeType::Team)
    {
        std::cout << "WorldController::createPersonForTeam : " << std::endl <<
          "Input :\n" <<
          "\tteam_id = " << team_id << std::endl <<
          "\tteam_type = " << team_type << std::endl <<
          "\tperson_axis_in_parent :" << std::endl;
        person_axis_in_parent.outputInfo(1);
        std::cout << "this type is not the team type!" << std::endl;

        return false;
    }
}

bool WorldController::createFurniture(
    const size_t &furniture_id,
    const NodeType &furniture_type,
    const size_t &on_person_id,
    const NodeType &on_person_type)
{
    if(furniture_type != NodeType::Furniture)
    {
        std::cout << "WorldController::createFurniture : " << std::endl <<
          "Input :\n" <<
          "\tfurniture_id = " << furniture_id << std::endl <<
          "\tfurniture_type = " << furniture_type << std::endl <<
          "\ton_person_id = " << on_person_id << std::endl <<
          "\ton_person_type = " << on_person_type << std::endl <<
          "this type is not the furniture type!" << std::endl;

        return false;
    }

    if(!world_tree_.createNode(
          furniture_id, furniture_type, on_person_id, on_person_type, 0))
    {
        std::cout << "WorldController::createFurniture : " << std::endl <<
          "Input :\n" <<
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
          true))
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
          true))
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

bool WorldController::getRoomNodeVec(
    std::vector<EasyNode*> &room_node_vec)
{
    room_node_vec.clear();

    if(room_pair_vec_.size() == 0)
    {
        return true;
    }

    for(const std::pair<size_t, NodeType> &room_pair : room_pair_vec_)
    {
        EasyNode* room_node = findNode(room_pair.first, room_pair.second);

        if(room_node == nullptr)
        {
            std::cout << "WorldController::getRoomNodeVec : " << std::endl <<
              "get room : id = " << room_pair.first <<
              ", type = " << room_pair.second <<
              " failed!" << std::endl;

            return false;
        }

        room_node_vec.emplace_back(room_node);
    }

    return true;
}

bool WorldController::getRoomBoundaryNodeVecVec(
    std::vector<std::vector<EasyNode*>> &room_boundary_node_vec_vec)
{
    room_boundary_node_vec_vec.clear();

    if(room_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> room_node_vec;

    if(!getRoomNodeVec(room_node_vec))
    {
        std::cout << "WorldController::getRoomBoundaryNodeVec : " << std::endl <<
          "getRoomNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* room_node : room_node_vec)
    {
        std::vector<EasyNode*> room_boundary_node_vec;
        std::vector<EasyNode*> room_child_node_vec = room_node->getChildNodeVec();

        for(EasyNode* room_child_node : room_child_node_vec)
        {
            if(room_child_node->getNodeType() == NodeType::Boundary)
            {
                room_boundary_node_vec.emplace_back(room_child_node);
            }
        }

        room_boundary_node_vec_vec.emplace_back(room_boundary_node_vec);
    }
    return true;
}

bool WorldController::getRoomSpaceNodeVec(
    std::vector<EasyNode*> &room_space_node_vec)
{
    room_space_node_vec.clear();

    if(room_pair_vec_.size() == 0)
    {
        return true;
    }

    std::vector<EasyNode*> room_node_vec;

    if(!getRoomNodeVec(room_node_vec))
    {
        std::cout << "WorldController::getRoomSpaceNodeVec : " << std::endl <<
          "getRoomNodeVec failed!" << std::endl;

        return false;
    }

    for(EasyNode* room_node : room_node_vec)
    {
        EasyNode* room_space_node = room_node->findChild(0, NodeType::Space);

        if(room_space_node == nullptr)
        {
            std::cout << "WorldController::getRoomNodeVec : " << std::endl <<
              "get room space node failed!" << std::endl;

            return false;
        }

        room_space_node_vec.emplace_back(room_space_node);
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

