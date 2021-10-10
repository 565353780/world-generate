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

bool EasyTree::createWorld(
    const float &world_center_x,
    const float &world_center_y)
{
    if(root_ != nullptr)
    {
        std::cout << "EasyTree::createWorld : " << std::endl <<
          "Input :\n" <<
          "\tworld_center = [" << world_center_x << "," <<
          world_center_y << "]" << std::endl <<
          "tree root already exist!" << std::endl;

        return false;
    }

    root_ = new EasyNode();

    if(!root_->setID(0))
    {
        std::cout << "EasyTree::createWorld : " << std::endl <<
          "Input :\n" <<
          "\tworld_center = [" << world_center_x << "," <<
          world_center_y << "]" << std::endl <<
          "setID for root failed!" << std::endl;

        return false;
    }

    if(!root_->setNodeType(NodeType::World))
    {
        std::cout << "EasyTree::createWorld : " << std::endl <<
          "Input :\n" <<
          "\tworld_center = [" << world_center_x << "," <<
          world_center_y << "]" << std::endl <<
          "setNodeType for root failed!" << std::endl;

        return false;
    }

    if(!root_->setAxisInParent(0, 0, 1, 0))
    {
        std::cout << "EasyTree::createWorld : " << std::endl <<
          "Input :\n" <<
          "\tworld_center = [" << world_center_x << "," <<
          world_center_y << "]" << std::endl <<
          "setAxisInParent for root failed!" << std::endl;

        return false;
    }

    if(!root_->setAxisInWorld(world_center_x, world_center_y, 1, 0))
    {
        std::cout << "EasyTree::createWorld : " << std::endl <<
          "Input :\n" <<
          "\tworld_center = [" << world_center_x << "," <<
          world_center_y << "]" << std::endl <<
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

    return search_node;
}

bool EasyTree::setNodeAxisCenterPositionInParent(
    const size_t &node_id,
    const NodeType &node_type,
    const EasyPoint2D &axis_new_center_position_in_parent,
    const bool &is_allow_x_direction_move_in_parent_axis,
    const bool &is_allow_y_direction_move_in_parent_axis)
{
    if(!is_allow_x_direction_move_in_parent_axis &&
        !is_allow_y_direction_move_in_parent_axis)
    {
        std::cout << "EasyTree::setNodeAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "\tis_allow_x_direction_move_in_parent_axis = " <<
          is_allow_x_direction_move_in_parent_axis << std::endl <<
          "\tis_allow_y_direction_move_in_parent_axis = " <<
          is_allow_y_direction_move_in_parent_axis << std::endl <<
          "can't move this axis in any direction!" << std::endl;

        return false;
    }

    EasyNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "\tis_allow_x_direction_move_in_parent_axis = " <<
          is_allow_x_direction_move_in_parent_axis << std::endl <<
          "\tis_allow_y_direction_move_in_parent_axis = " <<
          is_allow_y_direction_move_in_parent_axis << std::endl <<
          "this node not exist!" << std::endl;

        return false;
    }

    EasyNode* parent_node = search_node->getParent();

    if(parent_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "\tis_allow_x_direction_move_in_parent_axis = " <<
          is_allow_x_direction_move_in_parent_axis << std::endl <<
          "\tis_allow_y_direction_move_in_parent_axis = " <<
          is_allow_y_direction_move_in_parent_axis << std::endl <<
          "parent node not exist!" << std::endl;

        return false;
    }

    const EasyAxis2D &search_node_axis_in_parent = search_node->getAxisInParent();

    const EasyAxis2D search_node_axis_in_parent_copy = search_node_axis_in_parent;
    EasyAxis2D new_search_node_axis_in_parent = search_node_axis_in_parent;

    if(is_allow_x_direction_move_in_parent_axis)
    {
        new_search_node_axis_in_parent.center_.x = axis_new_center_position_in_parent.x;
    }

    if(is_allow_y_direction_move_in_parent_axis)
    {
        new_search_node_axis_in_parent.center_.y = axis_new_center_position_in_parent.y;
    }

    if(!search_node->setAxisInParent(
          new_search_node_axis_in_parent.center_.x,
          new_search_node_axis_in_parent.center_.y,
          new_search_node_axis_in_parent.x_direction_.x,
          new_search_node_axis_in_parent.x_direction_.y))
    {
        std::cout << "EasyTree::setNodeAxisCenterPositionInParent : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
          axis_new_center_position_in_parent.y << "]" << std::endl <<
          "\tis_allow_x_direction_move_in_parent_axis = " <<
          is_allow_x_direction_move_in_parent_axis << std::endl <<
          "\tis_allow_y_direction_move_in_parent_axis = " <<
          is_allow_y_direction_move_in_parent_axis << std::endl <<
          "setAxisInParent for node failed!" << std::endl;

        return false;
    }

    if(!isNodeSpaceValid(search_node))
    {
        if(!search_node->setAxisInParent(
              search_node_axis_in_parent_copy.center_.x,
              search_node_axis_in_parent_copy.center_.y,
              search_node_axis_in_parent_copy.x_direction_.x,
              search_node_axis_in_parent_copy.x_direction_.y))
        {
            std::cout << "EasyTree::setNodeAxisCenterPositionInParent : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "\taxis_new_position_in_parent = [" << axis_new_center_position_in_parent.x << "," <<
              axis_new_center_position_in_parent.y << "]" << std::endl <<
              "\tis_allow_x_direction_move_in_parent_axis = " <<
              is_allow_x_direction_move_in_parent_axis << std::endl <<
              "\tis_allow_y_direction_move_in_parent_axis = " <<
              is_allow_y_direction_move_in_parent_axis << std::endl <<
              "setAxisInParent for node to reset failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool EasyTree::setNodeAxisCenterPositionInWorld(
    const size_t &node_id,
    const NodeType &node_type,
    const EasyPoint2D &axis_new_center_position_in_world,
    const bool &is_allow_x_direction_move_in_parent_axis,
    const bool &is_allow_y_direction_move_in_parent_axis)
{
    if(!is_allow_x_direction_move_in_parent_axis &&
        !is_allow_y_direction_move_in_parent_axis)
    {
        std::cout << "EasyTree::setNodeAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "\tis_allow_x_direction_move_in_parent_axis = " <<
          is_allow_x_direction_move_in_parent_axis << std::endl <<
          "\tis_allow_y_direction_move_in_parent_axis = " <<
          is_allow_y_direction_move_in_parent_axis << std::endl <<
          "can't move this axis in any direction!" << std::endl;

        return false;
    }

    EasyNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "\tis_allow_x_direction_move_in_parent_axis = " <<
          is_allow_x_direction_move_in_parent_axis << std::endl <<
          "\tis_allow_y_direction_move_in_parent_axis = " <<
          is_allow_y_direction_move_in_parent_axis << std::endl <<
          "this node not exist!" << std::endl;

        return false;
    }

    EasyNode* parent_node = search_node->getParent();

    if(parent_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "\tis_allow_x_direction_move_in_parent_axis = " <<
          is_allow_x_direction_move_in_parent_axis << std::endl <<
          "\tis_allow_y_direction_move_in_parent_axis = " <<
          is_allow_y_direction_move_in_parent_axis << std::endl <<
          "parent node not exist!" << std::endl;

        return false;
    }

    EasyPoint2D axis_new_center_position_in_parent;

    if(!parent_node->getPointInNode(
          axis_new_center_position_in_world,
          axis_new_center_position_in_parent))
    {
        std::cout << "EasyTree::setNodeAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "\tis_allow_x_direction_move_in_parent_axis = " <<
          is_allow_x_direction_move_in_parent_axis << std::endl <<
          "\tis_allow_y_direction_move_in_parent_axis = " <<
          is_allow_y_direction_move_in_parent_axis << std::endl <<
          "getPointInNode for axis_center in parent failed!" << std::endl;

        return false;
    }

    const EasyAxis2D &search_node_axis_in_parent = search_node->getAxisInParent();

    const EasyAxis2D search_node_axis_in_parent_copy = search_node_axis_in_parent;
    EasyAxis2D new_search_node_axis_in_parent = search_node_axis_in_parent;

    if(is_allow_x_direction_move_in_parent_axis)
    {
        new_search_node_axis_in_parent.center_.x = axis_new_center_position_in_parent.x;
    }

    if(is_allow_y_direction_move_in_parent_axis)
    {
        new_search_node_axis_in_parent.center_.y = axis_new_center_position_in_parent.y;
    }

    if(!search_node->setAxisInParent(
          new_search_node_axis_in_parent.center_.x,
          new_search_node_axis_in_parent.center_.y,
          new_search_node_axis_in_parent.x_direction_.x,
          new_search_node_axis_in_parent.x_direction_.y))
    {
        std::cout << "EasyTree::setNodeAxisCenterPositionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
          axis_new_center_position_in_world.y << "]" << std::endl <<
          "\tis_allow_x_direction_move_in_parent_axis = " <<
          is_allow_x_direction_move_in_parent_axis << std::endl <<
          "\tis_allow_y_direction_move_in_parent_axis = " <<
          is_allow_y_direction_move_in_parent_axis << std::endl <<
          "setAxisInParent for node failed!" << std::endl;

        return false;
    }

    if(!isNodeSpaceValid(search_node))
    {
        if(!search_node->setAxisInParent(
              search_node_axis_in_parent_copy.center_.x,
              search_node_axis_in_parent_copy.center_.y,
              search_node_axis_in_parent_copy.x_direction_.x,
              search_node_axis_in_parent_copy.x_direction_.y))
        {
            std::cout << "EasyTree::setNodeAxisCenterPositionInWorld : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "\taxis_new_position_in_world = [" << axis_new_center_position_in_world.x << "," <<
              axis_new_center_position_in_world.y << "]" << std::endl <<
              "\tis_allow_x_direction_move_in_parent_axis = " <<
              is_allow_x_direction_move_in_parent_axis << std::endl <<
              "\tis_allow_y_direction_move_in_parent_axis = " <<
              is_allow_y_direction_move_in_parent_axis << std::endl <<
              "setAxisInParent for node to reset failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool EasyTree::setNodeAxisXDirectionInParent(
    const size_t &node_id,
    const NodeType &node_type,
    const EasyPoint2D &axis_new_x_direction_in_parent)
{
    EasyNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisXDirectionInParent : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_x_direction_in_parent = [" << axis_new_x_direction_in_parent.x << "," <<
          axis_new_x_direction_in_parent.y << "]" << std::endl <<
          "this node not exist!" << std::endl;

        return false;
    }

    EasyNode* parent_node = search_node->getParent();

    if(parent_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisXDirectionInParent : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_x_direction_in_parent = [" << axis_new_x_direction_in_parent.x << "," <<
          axis_new_x_direction_in_parent.y << "]" << std::endl <<
          "parent node not exist!" << std::endl;

        return false;
    }

    const EasyAxis2D &search_node_axis_in_parent = search_node->getAxisInParent();

    const EasyAxis2D search_node_axis_in_parent_copy = search_node_axis_in_parent;
    EasyAxis2D new_search_node_axis_in_parent = search_node_axis_in_parent;

    if(!new_search_node_axis_in_parent.setXDirection(
          axis_new_x_direction_in_parent.x,
          axis_new_x_direction_in_parent.y))
    {
        std::cout << "EasyTree::setNodeAxisXDirectionInParent : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_x_direction_in_parent = [" << axis_new_x_direction_in_parent.x << "," <<
          axis_new_x_direction_in_parent.y << "]" << std::endl <<
          "setXDirection for axis failed!" << std::endl;

        return false;
    }

    if(!search_node->setAxisInParent(
          new_search_node_axis_in_parent.center_.x,
          new_search_node_axis_in_parent.center_.y,
          new_search_node_axis_in_parent.x_direction_.x,
          new_search_node_axis_in_parent.x_direction_.y))
    {
        std::cout << "EasyTree::setNodeAxisXDirectionInParent : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_x_direction_in_parent = [" << axis_new_x_direction_in_parent.x << "," <<
          axis_new_x_direction_in_parent.y << "]" << std::endl <<
          "setAxisInParent for node failed!" << std::endl;

        return false;
    }

    if(!isNodeSpaceValid(search_node))
    {
        if(!search_node->setAxisInParent(
              search_node_axis_in_parent_copy.center_.x,
              search_node_axis_in_parent_copy.center_.y,
              search_node_axis_in_parent_copy.x_direction_.x,
              search_node_axis_in_parent_copy.x_direction_.y))
        {
            std::cout << "EasyTree::setNodeAxisXDirectionInParent : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "\taxis_new_x_direction_in_parent = [" << axis_new_x_direction_in_parent.x << "," <<
              axis_new_x_direction_in_parent.y << "]" << std::endl <<
              "setAxisInParent for node to reset failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool EasyTree::setNodeAxisXDirectionInWorld(
    const size_t &node_id,
    const NodeType &node_type,
    const EasyPoint2D &axis_new_x_direction_in_world)
{
    EasyNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisXDirectionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_x_direction_in_world = [" << axis_new_x_direction_in_world.x << "," <<
          axis_new_x_direction_in_world.y << "]" << std::endl <<
          "this node not exist!" << std::endl;

        return false;
    }

    EasyNode* parent_node = search_node->getParent();

    if(parent_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisXDirectionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_x_direction_in_world = [" << axis_new_x_direction_in_world.x << "," <<
          axis_new_x_direction_in_world.y << "]" << std::endl <<
          "parent node not exist!" << std::endl;

        return false;
    }

    EasyPoint2D axis_new_x_direction_in_parent;

    if(!parent_node->getPointInNode(
          axis_new_x_direction_in_world,
          axis_new_x_direction_in_parent))
    {
        std::cout << "EasyTree::setNodeAxisXDirectionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_x_direction_in_world = [" << axis_new_x_direction_in_world.x << "," <<
          axis_new_x_direction_in_world.y << "]" << std::endl <<
          "getPointInNode for axis_center in parent failed!" << std::endl;

        return false;
    }

    const EasyAxis2D &search_node_axis_in_parent = search_node->getAxisInParent();

    const EasyAxis2D search_node_axis_in_parent_copy = search_node_axis_in_parent;
    EasyAxis2D new_search_node_axis_in_parent = search_node_axis_in_parent;

    if(!new_search_node_axis_in_parent.setXDirection(
          axis_new_x_direction_in_parent.x,
          axis_new_x_direction_in_parent.y))
    {
        std::cout << "EasyTree::setNodeAxisXDirectionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_x_direction_in_world = [" << axis_new_x_direction_in_world.x << "," <<
          axis_new_x_direction_in_world.y << "]" << std::endl <<
          "setXDirection for new axis failed!" << std::endl;

        return false;
    }

    if(!search_node->setAxisInParent(
          new_search_node_axis_in_parent.center_.x,
          new_search_node_axis_in_parent.center_.y,
          new_search_node_axis_in_parent.x_direction_.x,
          new_search_node_axis_in_parent.x_direction_.y))
    {
        std::cout << "EasyTree::setNodeAxisXDirectionInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_new_x_direction_in_world = [" << axis_new_x_direction_in_world.x << "," <<
          axis_new_x_direction_in_world.y << "]" << std::endl <<
          "setAxisInParent for node failed!" << std::endl;

        return false;
    }

    if(!isNodeSpaceValid(search_node))
    {
        if(!search_node->setAxisInParent(
              search_node_axis_in_parent_copy.center_.x,
              search_node_axis_in_parent_copy.center_.y,
              search_node_axis_in_parent_copy.x_direction_.x,
              search_node_axis_in_parent_copy.x_direction_.y))
        {
            std::cout << "EasyTree::setNodeAxisXDirectionInWorld : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "\taxis_new_x_direction_in_world = [" << axis_new_x_direction_in_world.x << "," <<
              axis_new_x_direction_in_world.y << "]" << std::endl <<
              "setAxisInParent for node to reset failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool EasyTree::setNodeAxisInParent(
    const size_t &node_id,
    const NodeType &node_type,
    const EasyAxis2D &axis_in_parent)
{
    EasyNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisInParent : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\taxis_in_parent :" << std::endl;
        axis_in_parent.outputInfo(1);
        std::cout << "this node not exist!" << std::endl;

        return false;
    }

    EasyNode* parent_node = search_node->getParent();

    if(parent_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisInParent : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl;
        axis_in_parent.outputInfo(1);
        std::cout << "parent node not exist!" << std::endl;

        return false;
    }

    const EasyAxis2D &search_node_axis_in_parent = search_node->getAxisInParent();

    const EasyAxis2D search_node_axis_in_parent_copy = search_node_axis_in_parent;

    if(!search_node->setAxisInParent(
          axis_in_parent.center_.x,
          axis_in_parent.center_.y,
          axis_in_parent.x_direction_.x,
          axis_in_parent.x_direction_.y))
    {
        std::cout << "EasyTree::setNodeAxisInParent : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl;
        axis_in_parent.outputInfo(1);
        std::cout << "setAxisInParent for node failed!" << std::endl;

        return false;
    }

    if(!isNodeSpaceValid(search_node))
    {
        if(!search_node->setAxisInParent(
              search_node_axis_in_parent_copy.center_.x,
              search_node_axis_in_parent_copy.center_.y,
              search_node_axis_in_parent_copy.x_direction_.x,
              search_node_axis_in_parent_copy.x_direction_.y))
        {
            std::cout << "EasyTree::setNodeAxisInParent : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl;
            axis_in_parent.outputInfo(1);
            std::cout << "setAxisInParent for node to reset failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool EasyTree::setNodeAxisInWorld(
    const size_t &node_id,
    const NodeType &node_type,
    const EasyAxis2D &axis_in_world)
{
    EasyNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl;
        axis_in_world.outputInfo(1);
        std::cout << "this node not exist!" << std::endl;

        return false;
    }

    EasyNode* parent_node = search_node->getParent();

    if(parent_node == nullptr)
    {
        std::cout << "EasyTree::setNodeAxisInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl;
        axis_in_world.outputInfo(1);
        std::cout << "parent node not exist!" << std::endl;

        return false;
    }

    EasyPoint2D axis_center_in_parent;
    EasyPoint2D axis_x_direction_in_parent;

    if(!parent_node->getPointInNode(
          axis_in_world.center_,
          axis_center_in_parent))
    {
        std::cout << "EasyTree::setNodeAxisInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl;
        axis_in_world.outputInfo(1);
        std::cout << "getPointInNode for axis center in parent failed!" << std::endl;

        return false;
    }

    if(!parent_node->getPointInNode(
          axis_in_world.x_direction_,
          axis_x_direction_in_parent))
    {
        std::cout << "EasyTree::setNodeAxisInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl;
        axis_in_world.outputInfo(1);
        std::cout << "getPointInNode for axis x direction in parent failed!" << std::endl;

        return false;
    }

    const EasyAxis2D &search_node_axis_in_parent = search_node->getAxisInParent();

    const EasyAxis2D search_node_axis_in_parent_copy = search_node_axis_in_parent;

    if(!search_node->setAxisInParent(
          axis_center_in_parent.x,
          axis_center_in_parent.y,
          axis_x_direction_in_parent.x,
          axis_x_direction_in_parent.y))
    {
        std::cout << "EasyTree::setNodeAxisInWorld : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl;
        axis_in_world.outputInfo(1);
        std::cout << "setAxisInParent for node failed!" << std::endl;

        return false;
    }

    if(!isNodeSpaceValid(search_node))
    {
        if(!search_node->setAxisInParent(
              search_node_axis_in_parent_copy.center_.x,
              search_node_axis_in_parent_copy.center_.y,
              search_node_axis_in_parent_copy.x_direction_.x,
              search_node_axis_in_parent_copy.x_direction_.y))
        {
            std::cout << "EasyTree::setNodeAxisXDirectionInWorld : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl;
            axis_in_world.outputInfo(1);
            std::cout << "setAxisInParent for node to reset failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool EasyTree::setNodeBoundaryPolygon(
    const size_t &node_id,
    const NodeType &node_type,
    const EasyPolygon2D &node_boundary_polygon)
{
    EasyNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
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

        if(!search_node->addChild(new_child_boundary_node))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "addChild for point " << i << " failed!" << std::endl;

            return false;
        }

        const EasyPoint2D &current_boundary_point_in_search_node =
          node_boundary_polygon.point_list[i];
        const EasyPoint2D &next_boundary_point_in_search_node =
          node_boundary_polygon.point_list[(i + 1) % node_boundary_polygon.point_list.size()];

        if(!new_child_boundary_node->setAxisInParent(
              current_boundary_point_in_search_node.x,
              current_boundary_point_in_search_node.y,
              next_boundary_point_in_search_node.x - current_boundary_point_in_search_node.x,
              next_boundary_point_in_search_node.y - current_boundary_point_in_search_node.y))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "setAxisInParent for point " << i << " failed!" << std::endl;

            return false;
        }

        EasyPoint2D current_boundary_point_in_world;
        EasyPoint2D next_boundary_point_in_world;

        if(!search_node->getPointInWorld(
              current_boundary_point_in_search_node,
              current_boundary_point_in_world))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "getPointInWorld for current point " << i << " failed!" << std::endl;

            return false;
        }

        if(!search_node->getPointInWorld(
              next_boundary_point_in_search_node,
              next_boundary_point_in_world))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "getPointInWorld for next point " << i << " failed!" << std::endl;

            return false;
        }

        EasyPoint2D current_boundary_point_in_boundary_node;
        EasyPoint2D next_boundary_point_in_boundary_node;

        if(!new_child_boundary_node->getPointInNode(
              current_boundary_point_in_world,
              current_boundary_point_in_boundary_node))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "getPointInNode for current point " << i << " failed!" << std::endl;

            return false;
        }

        if(!new_child_boundary_node->getPointInNode(
              next_boundary_point_in_world,
              next_boundary_point_in_boundary_node))
        {
            std::cout << "EasyTree::setNodeBoundaryPolygon : " << std::endl <<
              "Input :\n" <<
              "\tnode_id = " << node_id << std::endl <<
              "\tnode_type = " << node_type << std::endl <<
              "getPointInNode for next point " << i << " failed!" << std::endl;

            return false;
        }

        EasyPolygon2D boundary_node_polygon;

        boundary_node_polygon.addPoint(current_boundary_point_in_boundary_node);
        boundary_node_polygon.addPoint(next_boundary_point_in_boundary_node);

        if(!new_child_boundary_node->setBoundaryPolygon(boundary_node_polygon))
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

    if(!search_node->addChild(new_child_space_node))
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
    EasyNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
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

    EasyPoint2D point_new_position_in_search_node;

    if(!search_node->getPointInNode(
          point_new_position_in_world,
          point_new_position_in_search_node))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "getPointInNode for new point in search node failed!" << std::endl;

        return false;
    }

    EasyNode* search_space_node =
      search_node->findChild(0, NodeType::Space);

    if(search_space_node == nullptr)
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "can't find space node!" << std::endl;

        return false;
    }

    const EasyPolygon2D& space_node_polygon =
      search_space_node->getBoundaryPolygon();

    EasyNode* prev_boundary_node =
      search_node->findChild(
          (point_idx - 1 + space_node_polygon.point_list.size()) %
          space_node_polygon.point_list.size(), NodeType::Boundary);

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
          "can't find prev boundary node!" << std::endl;

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

    EasyPoint2D prev_boundary_start_point_in_search_node;

    if(!search_node->getPointInNode(
          prev_boundary_start_point_in_world,
          prev_boundary_start_point_in_search_node))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "getPointInNode for prev point in node failed!" << std::endl;

        return false;
    }

    if(!prev_boundary_node->setAxisInParent(
          prev_boundary_start_point_in_search_node.x,
          prev_boundary_start_point_in_search_node.y,
          point_new_position_in_search_node.x - prev_boundary_start_point_in_search_node.x,
          point_new_position_in_search_node.y - prev_boundary_start_point_in_search_node.y))
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
      search_node->findChild(point_idx, NodeType::Boundary);

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

    EasyPoint2D current_boundary_end_point_in_search_node;

    if(!search_node->getPointInNode(
          current_boundary_end_point_in_world,
          current_boundary_end_point_in_search_node))
    {
        std::cout << "EasyTree::setNodeBoundaryPolygonPointPosition : " << std::endl <<
          "Input :\n" <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tpoint_idx = " << point_idx << std::endl <<
          "\tpoint_new_position_in_world = [" <<
          point_new_position_in_world.x << "," <<
          point_new_position_in_world.y << "]" << std::endl <<
          "getPointInNode for current point in node failed!" << std::endl;

        return false;
    }

    if(!current_boundary_node->setAxisInParent(
          point_new_position_in_search_node.x,
          point_new_position_in_search_node.y,
          current_boundary_end_point_in_search_node.x - point_new_position_in_search_node.x,
          current_boundary_end_point_in_search_node.y - point_new_position_in_search_node.y))
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

    if(!search_space_node->setBoundaryPolygonPointPosition(
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

bool EasyTree::isNodeInParentSpace(
    EasyNode* node)
{
    if(node == nullptr)
    {
        std::cout << "EasyTree::isNodeInParentSpace : " << std::endl <<
          "node is nullptr!" << std::endl;

        return false;
    }

    const NodeType &node_type = node->getNodeType();

    if(node_type == NodeType::OuterWall ||
        node_type == NodeType::InnerWall)
    {
        return true;
    }

    EasyNode* space_node = node->findChild(0, NodeType::Space);

    if(space_node == nullptr)
    {
        std::cout << "EasyTree::isNodeInParentSpace : " << std::endl <<
          "space node is nullptr!" << std::endl;

        return false;
    }

    EasyNode* parent_boundary_node = node->getParent();

    if(parent_boundary_node == nullptr)
    {
        std::cout << "EasyTree::isNodeInParentSpace : " << std::endl <<
          "parent boundary node is nullptr!" << std::endl;

        return false;
    }

    EasyNode* parent_node = parent_boundary_node->getParent();

    if(parent_node == nullptr)
    {
        std::cout << "EasyTree::isNodeInParentSpace : " << std::endl <<
          "parent node is nullptr!" << std::endl;

        return false;
    }

    EasyNode* parent_space_node = parent_node->findChild(0, NodeType::Space);

    if(parent_space_node == nullptr)
    {
        std::cout << "EasyTree::isNodeInParentSpace : " << std::endl <<
          "parent space node is nullptr!" << std::endl;

        return false;
    }

    const EasyPolygon2D &parent_space_boundary_polygon_in_parent = parent_space_node->getBoundaryPolygon();

    if(parent_space_boundary_polygon_in_parent.point_list.size() == 0)
    {
        std::cout << "EasyTree::isNodeInParentSpace : " << std::endl <<
          "parent space node boundary polygon is empty!" << std::endl;

        return false;
    }

    const EasyPolygon2D &space_boundary_polygon_in_parent = space_node->getBoundaryPolygon();

    if(space_boundary_polygon_in_parent.point_list.size() == 0)
    {
        std::cout << "EasyTree::isNodeInParentSpace : " << std::endl <<
          "space node boundary polygon is empty!" << std::endl;

        return false;
    }

    for(const EasyPoint2D &space_boundary_point_in_parent : space_boundary_polygon_in_parent.point_list)
    {
        EasyPoint2D space_boundary_point_in_world;

        if(!space_node->getPointInWorld(
              space_boundary_point_in_parent,
              space_boundary_point_in_world))
        {
            std::cout << "EasyTree::isNodeInParentSpace : " << std::endl <<
              "getPointInWorld for space boundary point failed!" << std::endl;

            return false;
        }

        EasyPoint2D space_boundary_point_in_parent_space;

        if(!parent_space_node->getPointInNode(
              space_boundary_point_in_world,
              space_boundary_point_in_parent_space))
        {
            std::cout << "EasyTree::isNodeInParentSpace : " << std::endl <<
              "getPointInNode for space boundary point to parent space failed!" << std::endl;

            return false;
        }

        if(!EasyComputation::isPointInPolygon(
              space_boundary_point_in_parent_space,
              parent_space_boundary_polygon_in_parent,
              true))
        {
            return false;
        }
    }

    return true;
}

bool EasyTree::isNodeInParentChildNodeSpace(
    EasyNode* node)
{
    if(node == nullptr)
    {
        std::cout << "EasyTree::isNodeInParentChildNodeSpace : " << std::endl <<
          "node is nullptr!" << std::endl;

        return false;
    }

    const NodeType &node_type = node->getNodeType();

    if(node_type == NodeType::OuterWall ||
        node_type == NodeType::InnerWall)
    {
        return false;
    }

    EasyNode* space_node = node->findChild(0, NodeType::Space);

    if(space_node == nullptr)
    {
        std::cout << "EasyTree::isNodeInParentChildNodeSpace : " << std::endl <<
          "space node is nullptr!" << std::endl;

        return false;
    }

    const EasyPolygon2D &space_boundary_polygon_in_parent =
      space_node->getBoundaryPolygon();

    if(space_boundary_polygon_in_parent.point_list.size() == 0)
    {
        std::cout << "EasyTree::isNodeInParentChildNodeSpace : " << std::endl <<
          "space boundary polygon is empty!" << std::endl;

        return false;
    }

    EasyNode* parent_boundary_node = node->getParent();

    if(parent_boundary_node == nullptr)
    {
        std::cout << "EasyTree::isNodeInParentChildNodeSpace : " << std::endl <<
          "parent boundary node is nullptr!" << std::endl;

        return false;
    }

    EasyNode* parent_node = parent_boundary_node->getParent();

    if(parent_node == nullptr)
    {
        std::cout << "EasyTree::isNodeInParentChildNodeSpace : " << std::endl <<
          "parent node is nullptr!" << std::endl;

        return false;
    }

    const std::vector<EasyNode*> &parent_boundary_node_vec = parent_node->getChildNodeVec();

    for(EasyNode* parent_boundary_node : parent_boundary_node_vec)
    {
        if(parent_boundary_node == nullptr)
        {
            std::cout << "EasyTree::isNodeInParentChildNodeSpace : " << std::endl <<
              "parent boundary node is nullptr!" << std::endl;

            return false;
        }

        if(parent_boundary_node->getNodeType() != NodeType::Boundary)
        {
            continue;
        }

        const std::vector<EasyNode*> &parent_child_node_vec =
          parent_boundary_node->getChildNodeVec();

        for(EasyNode* parent_child_node : parent_child_node_vec)
        {
            if(parent_child_node == nullptr)
            {
                std::cout << "EasyTree::isNodeInParentChildNodeSpace : " << std::endl <<
                  "parent child node is nullptr!" << std::endl;

                return false;
            }

            if(parent_child_node == node)
            {
                continue;
            }

            EasyNode* parent_child_space_node = parent_child_node->findChild(0, NodeType::Space);

            if(parent_child_space_node == nullptr)
            {
                std::cout << "EasyTree::isNodeInParentChildNodeSpace : " << std::endl <<
                  "parent child space node is nullptr!" << std::endl;

                return false;
            }

            const EasyPolygon2D &parent_child_space_boundary_polygon_in_parent =
              parent_child_space_node->getBoundaryPolygon();

            for(const EasyPoint2D &parent_child_space_boundary_point_in_parent :
                parent_child_space_boundary_polygon_in_parent.point_list)
            {
                EasyPoint2D parent_child_space_boundary_point_in_world;

                if(!parent_child_space_node->getPointInWorld(
                      parent_child_space_boundary_point_in_parent,
                      parent_child_space_boundary_point_in_world))
                {
                    std::cout << "EasyTree::isNodeInParentChildNodeSpace : " << std::endl <<
                      "getPointInWorld for parent child space boundary point failed!" << std::endl;

                    return false;
                }

                EasyPoint2D parent_child_space_boundary_point_in_space_node;

                if(!space_node->getPointInNode(
                      parent_child_space_boundary_point_in_world,
                      parent_child_space_boundary_point_in_space_node))
                {
                    std::cout << "EasyTree::isNodeInParentChildNodeSpace : " << std::endl <<
                      "getPointInNode for parent child space boundary point failed!" << std::endl;

                    return false;
                }

                if(EasyComputation::isPointInPolygon(
                      parent_child_space_boundary_point_in_space_node,
                      space_boundary_polygon_in_parent,
                      false))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool EasyTree::isNodeSpaceValid(
    EasyNode* node)
{
    if(!isNodeInParentSpace(node))
    {
        // std::cout << "EasyTree::isNodeSpaceValid : " << std::endl <<
        //   "node not in parent node space!" << std::endl;

        return false;
    }

    if(isNodeInParentChildNodeSpace(node))
    {
        // std::cout << "EasyTree::isNodeSpaceValid : " << std::endl <<
        //   "node in parent child node space!" << std::endl;

        return false;
    }

    return true;
}

