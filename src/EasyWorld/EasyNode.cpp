#include "EasyNode.h"

EasyNode::~EasyNode()
{
    if(parent_ != nullptr)
    {
        // delete(parent_);
        parent_ = nullptr;
    }

    if(child_vec_.size() > 0)
    {
        for(size_t i = 0; i < child_vec_.size(); ++i)
        {
            if(child_vec_[i] != nullptr)
            {
                delete(child_vec_[i]);
                child_vec_[i] = nullptr;
            }
        }
    }

    // child_vec_.clear();
}

bool EasyNode::reset()
{
    id_ = 0;

    type_ = NodeType::NodeFree;

    if(parent_ != nullptr)
    {
        // delete(parent_);
        parent_ = nullptr;
    }

    if(child_vec_.size() > 0)
    {
        for(size_t i = 0; i < child_vec_.size(); ++i)
        {
            if(child_vec_[i] != nullptr)
            {
                delete(child_vec_[i]);
                child_vec_[i] = nullptr;
            }
        }
    }

    child_vec_.clear();

    axis_.reset();

    return true;
}

bool EasyNode::setID(
    const size_t &id)
{
    id_ = id;

    return true;
}

bool EasyNode::setNodeType(
    const NodeType& type)
{
    type_ = type;

    return true;
}

bool EasyNode::setAxis(
    const float &axis_center_x_in_parent,
    const float &axis_center_y_in_parent,
    const float &axis_x_direction_x_in_parent,
    const float &axis_x_direction_y_in_parent)
{
    if(!axis_.setCenter(
          axis_center_x_in_parent,
          axis_center_y_in_parent))
    {
        std::cout << "EasyNode::setAxis : " << std::endl <<
          "Input :\n" <<
          "\tCenter = [" << axis_center_x_in_parent << "," <<
          axis_center_y_in_parent << "]" << std::endl <<
          "\tXDirection = [" << axis_x_direction_x_in_parent << "," <<
          axis_x_direction_y_in_parent << "]" << std::endl <<
          "setCenter failed!" << std::endl;

        return false;
    }

    if(!axis_.setXDirection(
          axis_x_direction_x_in_parent,
          axis_x_direction_y_in_parent))
    {
        std::cout << "EasyNode::setAxis : " << std::endl <<
          "Input :\n" <<
          "\tCenter = [" << axis_center_x_in_parent << "," <<
          axis_center_y_in_parent << "]" << std::endl <<
          "\tXDirection = [" << axis_x_direction_x_in_parent << "," <<
          axis_x_direction_y_in_parent << "]" << std::endl <<
          "setXDirection failed!" << std::endl;

        return false;
    }

    return true;
}

bool EasyNode::setParent(
    EasyNode* parent)
{
    if(parent == nullptr)
    {
        std::cout << "EasyNode::setParent : " << std::endl <<
          "parent is nullptr!" << std::endl;

        return false;
    }

    parent_ = parent;

    return true;
}

bool EasyNode::setBoundaryPolygon(
    const EasyPolygon2D &boundary_polygon)
{
    boundary_polygon_ = boundary_polygon;

    return true;
}

bool EasyNode::findChild(
    const size_t &child_id,
    const NodeType &child_type,
    size_t &child_idx)
{
    if(child_vec_.size() == 0)
    {
        return false;
    }

    for(size_t i = 0; i < child_vec_.size(); ++i)
    {
        EasyNode* child_node = child_vec_[i];
        if(child_node->getID() == child_id &&
            child_node->getNodeType() == child_type)
        {
            child_idx = i;

            return true;
        }
    }

    return false;
}

EasyNode* EasyNode::findFromAllChild(
    const size_t &child_id,
    const NodeType &child_type)
{
    if(child_vec_.size() == 0)
    {
        return nullptr;
    }

    size_t child_idx;
    if(findChild(child_id, child_type, child_idx))
    {
        return child_vec_[child_idx];
    }

    for(EasyNode *child_node : child_vec_)
    {
        if(child_node == nullptr)
        {
            continue;
        }

        EasyNode* deep_child_node = child_node->findFromAllChild(child_id, child_type);

        if(deep_child_node != nullptr)
        {
            return deep_child_node;
        }
    }

    return nullptr;
}

bool EasyNode::haveThisChild(
    const size_t &child_id,
    const NodeType &child_type)
{
    size_t child_idx;

    if(findChild(child_id, child_type, child_idx))
    {
        return true;
    }

    return false;
}

bool EasyNode::createChild(
    const size_t &child_id,
    const NodeType &child_type)
{
    if(haveThisChild(child_id, child_type))
    {
        std::cout << "EasyNode::createChild : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "this id already exist!" << std::endl;

        return false;
    }

    child_vec_.emplace_back(new EasyNode());

    EasyNode* new_child_node = child_vec_.back();

    if(!new_child_node->setID(child_id))
    {
        std::cout << "EasyNode::createChild : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "setID for child failed!" << std::endl;

        return false;
    }

    if(!new_child_node->setNodeType(child_type))
    {
        std::cout << "EasyNode::createChild : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "setNodeType for child failed!" << std::endl;

        return false;
    }

    if(!new_child_node->setParent(this))
    {
        std::cout << "EasyNode::createChild : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "setParent for child failed!" << std::endl;

        return false;
    }

    return true;
}

bool EasyNode::removeChild(
    const size_t &child_id,
    const NodeType &child_type)
{
    size_t child_idx;

    if(!findChild(child_id, child_type, child_idx))
    {
        std::cout << "EasyNode::removeChild : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "this id not found for parent " << id_ << "!" << std::endl;

        return false;
    }

    EasyNode* child_node = child_vec_[child_idx];

    if(!child_node->removeAllChild())
    {
        std::cout << "EasyNode::removeChild : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "removeAllChild for child " << child_node->getID() << " failed!" << std::endl;

        return false;
    }

    delete(child_node);

    child_vec_.erase(child_vec_.begin() + child_idx);

    return true;
}

bool EasyNode::removeChildButRemainData(
    const size_t &child_id,
    const NodeType &child_type)
{
    size_t child_idx;

    if(!findChild(child_id, child_type, child_idx))
    {
        std::cout << "EasyNode::removeChildButRemainData : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "this id not found for parent " << id_ << "!" << std::endl;

        return false;
    }

    child_vec_[child_idx] = nullptr;

    child_vec_.erase(child_vec_.begin() + child_idx);

    return true;
}

bool EasyNode::removeAllChild()
{
    if(child_vec_.size() == 0)
    {
        return true;
    }

    for(EasyNode* child_node : child_vec_)
    {
        if(child_node == nullptr)
        {
            continue;
        }

        if(!child_node->removeAllChild())
        {
            std::cout << "EasyNode::removeAllChild : " << std::endl <<
              "removeAllChild on node " << id_ << " failed!" << std::endl;

            return false;
        }
    }

    for(size_t i = 0; i < child_vec_.size(); ++i)
    {
        if(child_vec_[i] != nullptr)
        {
            delete(child_vec_[i]);
            child_vec_[i] = nullptr;
        }
    }

    return true;
}

bool EasyNode::setChildAxisInParent(
    const size_t &child_id,
    const NodeType &child_type,
    const float &child_axis_center_x_in_parent,
    const float &child_axis_center_y_in_parent,
    const float &child_axis_x_direction_x_in_parent,
    const float &child_axis_x_direction_y_in_parent)
{
    size_t child_idx;

    if(!findChild(child_id, child_type, child_idx))
    {
        std::cout << "EasyNode::setChildAxisInParent : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "\tchild_axis_center_in_parent = [" <<
          child_axis_center_x_in_parent << "," <<
          child_axis_center_y_in_parent << "]" << std::endl <<
          "\t child_axis_x_direction_in_parent = [" <<
          child_axis_x_direction_x_in_parent << "," <<
          child_axis_x_direction_y_in_parent << "]" << std::endl <<
          "this child not exist!" << std::endl;

        return false;
    }

    EasyNode* child_node = child_vec_[child_idx];

    if(child_node == nullptr)
    {
        std::cout << "EasyNode::setChildAxisInParent : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "\tchild_axis_center_in_parent = [" <<
          child_axis_center_x_in_parent << "," <<
          child_axis_center_y_in_parent << "]" << std::endl <<
          "\t child_axis_x_direction_in_parent = [" <<
          child_axis_x_direction_x_in_parent << "," <<
          child_axis_x_direction_y_in_parent << "]" << std::endl <<
          "this child is nullptr!" << std::endl;

        return false;
    }

    if(!child_node->setAxis(
          child_axis_center_x_in_parent,
          child_axis_center_y_in_parent,
          child_axis_x_direction_x_in_parent,
          child_axis_x_direction_y_in_parent))
    {
        std::cout << "EasyNode::setChildAxisInParent : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "\tchild_axis_center_in_parent = [" <<
          child_axis_center_x_in_parent << "," <<
          child_axis_center_y_in_parent << "]" << std::endl <<
          "\t child_axis_x_direction_in_parent = [" <<
          child_axis_x_direction_x_in_parent << "," <<
          child_axis_x_direction_y_in_parent << "]" << std::endl <<
          "setAxis for child failed!" << std::endl;

        return false;
    }

    return true;
}

bool EasyNode::setChildBoundaryPolygon(
    const size_t &child_id,
    const NodeType &child_type,
    const EasyPolygon2D &child_boundary_polygon)
{
    size_t child_idx;

    if(!findChild(child_id, child_type, child_idx))
    {
        std::cout << "EasyNode::setChildBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "this child not exist!" << std::endl;

        return false;
    }

    EasyNode* child_node = child_vec_[child_idx];

    if(child_node == nullptr)
    {
        std::cout << "EasyNode::setChildBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "this child is nullptr!" << std::endl;

        return false;
    }

    if(!child_node->setBoundaryPolygon(child_boundary_polygon))
    {
        std::cout << "EasyNode::setChildBoundaryPolygon : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "setBoundaryPolygon for child failed!" << std::endl;

        return false;
    }

    return true;
}

