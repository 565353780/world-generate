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

bool WorldController::createWorld()
{
    if(!world_tree_.createWorld())
    {
        std::cout << "WorldController::createWorld : " << std::endl <<
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
    if(room_type != NodeType::Room)
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

bool WorldController::setRoomBoundaryPolygon(
    const size_t &room_id,
    const NodeType &room_type,
    const EasyPolygon2D &room_boundary_polygon)
{
    if(room_type != NodeType::Room)
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
    if(room_type != NodeType::Room)
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

bool WorldController::outputInfo()
{
    world_tree_.outputInfo();

    return true;
}

