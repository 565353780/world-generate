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

bool EasyTree::createNode(
    const size_t &node_id,
    const NodeType &node_type,
    const size_t &parent_node_id,
    const NodeType &parent_node_type,
    const size_t &parent_boundary_node_id)
{
    if(parent_node_type == NodeType::World)
    {
        if(root_->haveThisChild(node_id, node_type))
        {
            std::cout << "EasyTree::createNode : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tparent_node_id = " << parent_node_id << std::endl <<
              "\tparent_node_type = " << parent_node_type << std::endl <<
              "\tparent_boundary_node_id = " << parent_boundary_node_id << std::endl <<
              "this node already exist!" << std::endl;

            return false;
        }

        if(!root_->createChild(node_id, node_type))
        {
            std::cout << "EasyTree::createNode : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tparent_node_id = " << parent_node_id << std::endl <<
              "\tparent_node_type = " << parent_node_type << std::endl <<
              "\tparent_boundary_node_id = " << parent_boundary_node_id << std::endl <<
              "createChild failed!" << std::endl;

            return false;
        }

        return true;
    }

    EasyNode* search_node = findNode(node_id, node_type);

    if(search_node != nullptr)
    {
        std::cout << "EasyTree::createNode : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tparent_node_id = " << parent_node_id << std::endl <<
          "\tparent_node_type = " << parent_node_type << std::endl <<
          "\tparent_boundary_node_id = " << parent_boundary_node_id << std::endl <<
          "this node already exist!" << std::endl;

        return false;
    }

    EasyNode* parent_node = findNode(parent_node_id, parent_node_type);

    if(parent_node == nullptr)
    {
        std::cout << "EasyTree::createNode : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tparent_node_id = " << parent_node_id << std::endl <<
          "\tparent_node_type = " << parent_node_type << std::endl <<
          "\tparent_boundary_node_id = " << parent_boundary_node_id << std::endl <<
          "can't find this parent node!" << std::endl;

        return false;
    }

    EasyNode* parent_boundary_node =
      parent_node->findChild(parent_boundary_node_id, NodeType::Boundary);

    if(parent_boundary_node == nullptr)
    {
        std::cout << "EasyTree::createNode : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tparent_node_id = " << parent_node_id << std::endl <<
          "\tparent_node_type = " << parent_node_type << std::endl <<
          "\tparent_boundary_node_id = " << parent_boundary_node_id << std::endl <<
          "can't find this parent node boundary!" << std::endl;

        return false;
    }

    if(!parent_boundary_node->createChild(node_id, node_type))
    {
        std::cout << "EasyTree::createNode : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tparent_node_id = " << parent_node_id << std::endl <<
          "\tparent_node_type = " << parent_node_type << std::endl <<
          "\tparent_boundary_node_id = " << parent_boundary_node_id << std::endl <<
          "createChild for parent boundary node failed!" << std::endl;

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

bool EasyTree::setNodeBoundaryPolygon(
    const size_t &node_id,
    const NodeType &node_type,
    const EasyPolygon2D &node_boundary_polygon)
{
    EasyNode* node_node = findNode(node_id, node_type);

    if(node_node == nullptr)
    {
        std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "this node not exist!" << std::endl;

        return false;
    }

    for(size_t i = 0; i < node_boundary_polygon.point_list.size(); ++i)
    {
        EasyNode* new_child_boundary_node = new EasyNode();

        if(!new_child_boundary_node->setID(i))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "setID for point " << i << " failed!" << std::endl;

            return false;
        }

        if(!new_child_boundary_node->setNodeType(NodeType::Boundary))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "setNodeType for point " << i << " failed!" << std::endl;

            return false;
        }

        if(!node_node->addChild(new_child_boundary_node))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "addChild for point " << i << " failed!" << std::endl;

            return false;
        }

        const EasyPoint2D &node_boundary_point =
          node_boundary_polygon.point_list[i];
        const EasyPoint2D &next_node_boundary_point =
          node_boundary_polygon.point_list[(i + 1) % node_boundary_polygon.point_list.size()];

        if(!new_child_boundary_node->setAxisInParent(
              node_boundary_point.x,
              node_boundary_point.y,
              next_node_boundary_point.x - node_boundary_point.x,
              next_node_boundary_point.y - node_boundary_point.y))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "setAxisInParent for point " << i << " failed!" << std::endl;

            return false;
        }

        EasyPoint2D node_boundary_point_in_node;
        EasyPoint2D next_node_boundary_point_in_node;

        if(!new_child_boundary_node->getPointInNode(
              node_boundary_point,
              node_boundary_point_in_node))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "getPointInNode for point " << i << " failed!" << std::endl;

            return false;
        }

        if(!new_child_boundary_node->getPointInNode(
              next_node_boundary_point,
              next_node_boundary_point_in_node))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "getPointInNode for point " << i << " failed!" << std::endl;

            return false;
        }

        EasyPolygon2D node_boundary_node_polygon;

        node_boundary_node_polygon.addPoint(node_boundary_point_in_node);
        node_boundary_node_polygon.addPoint(next_node_boundary_point_in_node);

        if(!new_child_boundary_node->setBoundaryPolygon(node_boundary_node_polygon))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "setBoundaryPolygon for point " << i << " failed!" << std::endl;

            return false;
        }
    }

    EasyNode* new_child_space_node = new EasyNode();

    if(!new_child_space_node->setID(0))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "setID for space node failed!" << std::endl;

        return false;
    }

    if(!new_child_space_node->setNodeType(NodeType::Space))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "setNodeType for space node failed!" << std::endl;

        return false;
    }

    if(!node_node->addChild(new_child_space_node))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "addChild for space node failed!" << std::endl;

        return false;
    }

    if(!new_child_space_node->setBoundaryPolygon(node_boundary_polygon))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "setBoundaryPolygon for space node failed!" << std::endl;

        return false;
    }

    return true;
}

bool EasyTree::setNodeBoundaryPolygonPointPosition(
    const size_t &node_id,
    const NodeType &node_type,
    const size_t &point_idx,
    const EasyPoint2D &point_new_position_in_world)
{
    EasyNode* node_node = findNode(node_id, node_type);

    if(node_node == nullptr)
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "this node not exist!" << std::endl;

        return false;
    }

    EasyPoint2D point_new_position_in_node_node;

    if(!node_node->getPointInNode(
          point_new_position_in_world,
          point_new_position_in_node_node))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "getPointInNode for new point in node node failed!" << std::endl;

        return false;
    }

    EasyNode* node_space_node =
      node_node->findChild(0, NodeType::Space);

    if(node_space_node == nullptr)
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "can't find node space node!" << std::endl;

        return false;
    }

    const EasyPolygon2D& node_space_polygon =
      node_space_node->getBoundaryPolygon();

    EasyNode* prev_boundary_node =
      node_node->findChild(
          (point_idx - 1 + node_space_polygon.point_list.size()) %
          node_space_polygon.point_list.size(), NodeType::Boundary);

    if(prev_boundary_node == nullptr)
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "can't find node prev boundary node!" << std::endl;

        return false;
    }

    const EasyPolygon2D &prev_boundary_polygon =
      prev_boundary_node->getBoundaryPolygon();

    EasyPoint2D prev_boundary_start_point_in_world;

    if(!prev_boundary_node->getPointInWorld(
        prev_boundary_polygon.point_list[0],
        prev_boundary_start_point_in_world))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "getPointInWorld for prev point failed!" << std::endl;

        return false;
    }

    EasyPoint2D prev_boundary_start_point_in_node_node;

    if(!node_node->getPointInNode(
          prev_boundary_start_point_in_world,
          prev_boundary_start_point_in_node_node))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "getPointInNode for prev point in node node failed!" << std::endl;

        return false;
    }

    if(!prev_boundary_node->setAxisInParent(
          prev_boundary_start_point_in_node_node.x,
          prev_boundary_start_point_in_node_node.y,
          point_new_position_in_node_node.x - prev_boundary_start_point_in_node_node.x,
          point_new_position_in_node_node.y - prev_boundary_start_point_in_node_node.y))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setAxisInParent for prev point failed!" << std::endl;

        return false;
    }

    EasyNode* current_boundary_node =
      node_node->findChild(point_idx, NodeType::Boundary);

    if(current_boundary_node == nullptr)
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "can't find node current boundary node!" << std::endl;

        return false;
    }

    const EasyPolygon2D &current_boundary_polygon =
      current_boundary_node->getBoundaryPolygon();

    EasyPoint2D current_boundary_end_point_in_world;

    if(!current_boundary_node->getPointInWorld(
        current_boundary_polygon.point_list[1],
        current_boundary_end_point_in_world))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "getPointInWorld for current point failed!" << std::endl;

        return false;
    }

    EasyPoint2D current_boundary_end_point_in_node_node;

    if(!node_node->getPointInNode(
          current_boundary_end_point_in_world,
          current_boundary_end_point_in_node_node))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "getPointInNode for current point in node node failed!" << std::endl;

        return false;
    }

    if(!current_boundary_node->setAxisInParent(
          point_new_position_in_node_node.x,
          point_new_position_in_node_node.y,
          current_boundary_end_point_in_node_node.x - point_new_position_in_node_node.x,
          current_boundary_end_point_in_node_node.y - point_new_position_in_node_node.y))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setAxisInParent for current point failed!" << std::endl;

        return false;
    }

    if(!node_space_node->setBoundaryPolygonPointPosition(
          point_idx, point_new_position_in_world))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setBoundaryPolygonPointPosition for space node failed!" << std::endl;

        return false;
    }

    if(!prev_boundary_node->setBoundaryPolygonPointPosition(
          1, point_new_position_in_world))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setBoundaryPolygonPointPosition for prev point node's end point failed!" << std::endl;

        return false;
    }

    if(!current_boundary_node->setBoundaryPolygonPointPosition(
          0, point_new_position_in_world))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setBoundaryPolygonPointPosition for current point node's start point failed!" << std::endl;

        return false;
    }

    if(!current_boundary_node->setBoundaryPolygonPointPosition(
          1, current_boundary_end_point_in_world))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "setBoundaryPolygonPointPosition for current point node's end point failed!" << std::endl;

        return false;
    }

    return true;
}

bool EasyTree::outputInfo() const
{
    std::cout << "EasyTree :" << std::endl;

    root_->outputInfo(0);

    return true;
}

