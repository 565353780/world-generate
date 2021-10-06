#include "WorldController.h"

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
    if(!world_tree_.createWall(wall_id, wall_type))
    {
        std::cout << "WorldController::createWall : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "createWall failed!" << std::endl;

        return false;
    }

    std::pair<size_t, NodeType> new_wall_pair;
    new_wall_pair.first = wall_id;
    new_wall_pair.second = wall_type;

    wall_pair_vec_.emplace_back(new_wall_pair);

    return true;
}

bool WorldController::createWallBoundary(
    const size_t &wall_id,
    const NodeType &wall_type,
    const EasyPolygon2D &wall_boundary_polygon)
{
    if(!world_tree_.createWallBoundary(wall_id, wall_type, wall_boundary_polygon))
    {
        std::cout << "WorldController::createWallBoundary : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "createWallBoundary failed!" << std::endl;

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

bool WorldController::outputInfo()
{
    world_tree_.outputInfo();

    return true;
}

