#include "EasyTree.h"

bool EasyTree::reset()
{
    if(root_ != nullptr)
    {
        if(!root_->removeAllChild())
        {
            std::cout << "EasyTree::reset : " << std::endl <<
              "removeAllChild for root failed!" << std::endl;

            return false;
        }

        root_ = nullptr;
    }

    return true;
}

bool EasyTree::createWorld()
{
    if(root_ != nullptr)
    {
        std::cout << "EasyTree::createWorld : " << std::endl <<
          "tree root already exist!" << std::endl;

        return false;
    }

    root_ = new EasyNode();

    if(!root_->setID(0))
    {
        std::cout << "EasyTree::createWorld : " << std::endl <<
          "setID for root failed!" << std::endl;

        return false;
    }

    if(!root_->setNodeType(NodeType::World))
    {
        std::cout << "EasyTree::createWorld : " << std::endl <<
          "setNodeType for root failed!" << std::endl;

        return false;
    }

    if(!root_->setAxisInParent(0, 0, 1, 0))
    {
        std::cout << "EasyTree::createWorld : " << std::endl <<
          "setAxisInParent for root failed!" << std::endl;

        return false;
    }

    if(!root_->setAxisInWorld(0, 0, 1, 0))
    {
        std::cout << "EasyTree::createWorld : " << std::endl <<
          "setAxisInWorld for root failed!" << std::endl;

        return false;
    }

    return true;
}

EasyNode* EasyTree::findNode(
    const size_t &id,
    const NodeType &type)
{
    if(root_ == nullptr)
    {
        std::cout << "EasyTree::findNode : " << std::endl <<
          "Input :\n" <<
          "\tid = " << id << std::endl <<
          "\ttype = " << type << std::endl <<
          "tree is empty!" << std::endl;

        return nullptr;
    }

    EasyNode* search_node = root_->findFromAllChild(id, type);

    if(search_node == nullptr)
    {
        std::cout << "EasyTree::findNode : " << std::endl <<
          "Input :\n" <<
          "\tid = " << id << std::endl <<
          "\ttype = " << type << std::endl <<
          "findFromNode start from root failed!" << std::endl;

        return nullptr;
    }

    return search_node;
}

bool EasyTree::createWall(
    const size_t &wall_id,
    const NodeType &wall_type)
{
    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "EasyTree::createWall : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "wall_type is not the wall type!" << std::endl;

        return false;
    }

    size_t node_idx;

    if(root_->findChild(wall_id, wall_type, node_idx))
    {
        std::cout << "EasyTree::createWall : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "this wall already exist!" << std::endl;

        return false;
    }

    if(!root_->createChild(wall_id, wall_type))
    {
        std::cout << "EasyTree::createWall : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "createChild failed!" << std::endl;

        return false;
    }

    return true;
}

bool EasyTree::createWallBoundary(
    const size_t &wall_id,
    const NodeType &wall_type,
    const EasyPolygon2D &wall_boundary_polygon)
{
    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "EasyTree::createWallBoundary : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "wall_type is not the wall type!" << std::endl;

        return false;
    }

    EasyNode* wall_node = findNode(wall_id, wall_type);

    if(wall_node == nullptr)
    {
        std::cout << "EasyTree::createWallBoundary : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "this wall not exist!" << std::endl;

        return false;
    }

    for(size_t i = 0; i < wall_boundary_polygon.point_list.size(); ++i)
    {
        const EasyPoint2D &wall_boundary_point =
          wall_boundary_polygon.point_list[i];
        const EasyPoint2D &next_wall_boundary_point =
          wall_boundary_polygon.point_list[(i + 1) % wall_boundary_polygon.point_list.size()];

        if(!wall_node->createChild(i, NodeType::Boundary))
        {
            std::cout << "EasyTree::createWallBoundary : " << std::endl <<
              "Input :\n" <<
              "\twall_id = " << wall_id << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "createChild for point " << i << " failed!" << std::endl;

            return false;
        }

        if(!wall_node->setChildAxisInParent(
              i,
              NodeType::Boundary,
              wall_boundary_point.x,
              wall_boundary_point.y,
              next_wall_boundary_point.x - wall_boundary_point.x,
              next_wall_boundary_point.y - wall_boundary_point.y))
        {
            std::cout << "EasyTree::createWallBoundary : " << std::endl <<
              "Input :\n" <<
              "\twall_id = " << wall_id << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "setChildAxisInParent for point " << i << " failed!" << std::endl;

            return false;
        }
    }

    if(!wall_node->createChild(0, NodeType::Space))
    {
        std::cout << "EasyTree::createWallBoundary : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "createChild for boundary space failed!" << std::endl;

        return false;
    }

    if(!wall_node->setChildAxisInParent(0, NodeType::Space, 0, 0, 1, 0))
    {
        std::cout << "EasyTree::createWallBoundary : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "setChildAxisInParent for boundary space failed!" << std::endl;

        return false;
    }

    if(!wall_node->setChildBoundaryPolygon(0, NodeType::Space, wall_boundary_polygon))
    {
        std::cout << "EasyTree::createWallBoundary : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "setBoundaryPolygon for boundary space failed!" << std::endl;

        return false;
    }

    return true;
}

bool EasyTree::createRoom(
    const size_t &room_id,
    const size_t &on_wall_id,
    const NodeType &on_wall_type,
    const size_t &wall_boundary_id)
{
    return true;
}

bool EasyTree::outputInfo() const
{
    std::cout << "EasyTree :" << std::endl;

    root_->outputInfo(0);

    return true;
}

