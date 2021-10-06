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

    EasyNode* search_node = root_->findChild(wall_id, wall_type);

    if(search_node != nullptr)
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
        EasyNode* new_child_boundary_node = new EasyNode();

        if(!new_child_boundary_node->setID(i))
        {
            std::cout << "EasyTree::createWallBoundary : " << std::endl <<
              "Input :\n" <<
              "\twall_id = " << wall_id << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "setID for point " << i << " failed!" << std::endl;

            return false;
        }

        if(!new_child_boundary_node->setNodeType(NodeType::Boundary))
        {
            std::cout << "EasyTree::createWallBoundary : " << std::endl <<
              "Input :\n" <<
              "\twall_id = " << wall_id << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "setNodeType for point " << i << " failed!" << std::endl;

            return false;
        }

        if(!wall_node->addChild(new_child_boundary_node))
        {
            std::cout << "EasyTree::createWallBoundary : " << std::endl <<
              "Input :\n" <<
              "\twall_id = " << wall_id << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "addChild for point " << i << " failed!" << std::endl;

            return false;
        }

        const EasyPoint2D &wall_boundary_point =
          wall_boundary_polygon.point_list[i];
        const EasyPoint2D &next_wall_boundary_point =
          wall_boundary_polygon.point_list[(i + 1) % wall_boundary_polygon.point_list.size()];

        if(!new_child_boundary_node->setAxisInParent(
              wall_boundary_point.x,
              wall_boundary_point.y,
              next_wall_boundary_point.x - wall_boundary_point.x,
              next_wall_boundary_point.y - wall_boundary_point.y))
        {
            std::cout << "EasyTree::createWallBoundary : " << std::endl <<
              "Input :\n" <<
              "\twall_id = " << wall_id << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "setAxisInParent for point " << i << " failed!" << std::endl;

            return false;
        }

        EasyPoint2D wall_boundary_point_in_node;
        EasyPoint2D next_wall_boundary_point_in_node;

        if(!new_child_boundary_node->getPonitInNode(
              wall_boundary_point,
              wall_boundary_point_in_node))
        {
            std::cout << "EasyTree::createWallBoundary : " << std::endl <<
              "Input :\n" <<
              "\twall_id = " << wall_id << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "getPonitInNode for point " << i << " failed!" << std::endl;

            return false;
        }

        if(!new_child_boundary_node->getPonitInNode(
              next_wall_boundary_point,
              next_wall_boundary_point_in_node))
        {
            std::cout << "EasyTree::createWallBoundary : " << std::endl <<
              "Input :\n" <<
              "\twall_id = " << wall_id << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "getPonitInNode for point " << i << " failed!" << std::endl;

            return false;
        }

        EasyPolygon2D wall_boundary_node_polygon;

        wall_boundary_node_polygon.addPoint(wall_boundary_point_in_node);
        wall_boundary_node_polygon.addPoint(next_wall_boundary_point_in_node);

        if(!new_child_boundary_node->setBoundaryPolygon(wall_boundary_node_polygon))
        {
            std::cout << "EasyTree::createWallBoundary : " << std::endl <<
              "Input :\n" <<
              "\twall_id = " << wall_id << std::endl <<
              "\twall_type = " << wall_type << std::endl <<
              "setBoundaryPolygon for point " << i << " failed!" << std::endl;

            return false;
        }
    }

    EasyNode* new_child_space_node = new EasyNode();

    if(!new_child_space_node->setID(0))
    {
        std::cout << "EasyTree::createWallBoundary : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "setID for space node failed!" << std::endl;

        return false;
    }

    if(!new_child_space_node->setNodeType(NodeType::Space))
    {
        std::cout << "EasyTree::createWallBoundary : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "setNodeType for space node failed!" << std::endl;

        return false;
    }

    if(!wall_node->addChild(new_child_space_node))
    {
        std::cout << "EasyTree::createWallBoundary : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "addChild for space node failed!" << std::endl;

        return false;
    }

    if(!new_child_space_node->setBoundaryPolygon(wall_boundary_polygon))
    {
        std::cout << "EasyTree::createWallBoundary : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "setBoundaryPolygon for space node failed!" << std::endl;

        return false;
    }

    return true;
}

bool EasyTree::setWallBoundaryPolygonPointPosition(
    const size_t &wall_id,
    const NodeType &wall_type,
    const size_t &point_idx,
    const EasyPoint2D &point_new_position_in_world)
{
    if(wall_type != NodeType::OuterWall &&
        wall_type != NodeType::InnerWall)
    {
        std::cout << "EasyTree::setWallBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "wall_type is not the wall type!" << std::endl;

        return false;
    }

    EasyNode* wall_node = findNode(wall_id, wall_type);

    if(wall_node == nullptr)
    {
        std::cout << "EasyTree::setWallBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "this wall not exist!" << std::endl;

        return false;
    }

    EasyNode* wall_space_node =
      wall_node->findChild(0, NodeType::Space);

    if(wall_space_node == nullptr)
    {
        std::cout << "EasyTree::setWallBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "can't find wall space node!" << std::endl;

        return false;
    }

    const EasyPolygon2D& wall_space_polygon =
      wall_space_node->getBoundaryPolygon();

    EasyNode* prev_boundary_node =
      wall_node->findChild(
          (point_idx - 1 + wall_space_polygon.point_list.size()) %
          wall_space_polygon.point_list.size(), NodeType::Boundary);

    if(prev_boundary_node == nullptr)
    {
        std::cout << "EasyTree::setWallBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "can't find wall prev boundary node!" << std::endl;

        return false;
    }

    const EasyPolygon2D &prev_boundary_polygon =
      prev_boundary_node->getBoundaryPolygon();

    const EasyPoint2D prev_boundary_start_point_in_world =
      prev_boundary_node->getPointInWorld()

    EasyNode* wall_boundary_node =
      wall_node->findChild(point_idx, NodeType::Boundary);

    if(wall_boundary_node == nullptr)
    {
        std::cout << "EasyTree::setWallBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\twall_id = " << wall_id << std::endl <<
          "\twall_type = " << wall_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "can't find wall boundary node!" << std::endl;

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

