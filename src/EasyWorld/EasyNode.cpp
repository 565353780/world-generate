#include "EasyNode.h"

EasyNode::~EasyNode()
{
    if(parent_ != NULL)
    {
        // delete(parent_);
        parent_ = NULL;
    }

    if(child_vec_.size() > 0)
    {
        for(size_t i = 0; i < child_vec_.size(); ++i)
        {
            if(child_vec_[i] != NULL)
            {
                delete(child_vec_[i]);
                child_vec_[i] = NULL;
            }
        }
    }

    // child_vec_.clear();
}

bool EasyNode::reset()
{
    id_ = 0;

    type_ = Free;

    if(parent_ != NULL)
    {
        // delete(parent_);
        parent_ = NULL;
    }

    if(child_vec_.size() > 0)
    {
        for(size_t i = 0; i < child_vec_.size(); ++i)
        {
            if(child_vec_[i] != NULL)
            {
                delete(child_vec_[i]);
                child_vec_[i] = NULL;
            }
        }
    }

    child_vec_.clear();

    position_in_parent_.setPosition(0, 0);
    direction_in_parent_.setPosition(0, 0);

    position_.setPosition(0, 0);
    direction_.setPosition(0, 0);

    return true;
}

bool EasyNode::setParent(
    EasyNode* parent)
{
    if(parent == NULL)
    {
        std::cout << "EasyNode::setParent : " <<
          "parent is NULL!" << std::endl;

        return false;
    }

    parent_ = parent;

    return true;
}

bool EasyNode::findThisChild(
    const size_t &child_id,
    size_t &child_idx)
{
    if(child_vec_.size() == 0)
    {
        return false;
    }

    for(size_t i = 0; i < child_vec_.size(); ++i)
    {
        const EasyNode* child_node = child_vec_[i];
        if(child_node->id_ == child_id)
        {
            child_idx = i;

            return true;
        }
    }

    return false;
}

bool EasyNode::haveThisChild(
    const size_t &child_id)
{
    size_t child_idx;

    if(findThisChild(child_id, child_idx))
    {
        return true;
    }

    return false;
}

bool EasyNode::createChild(
    const size_t &child_id)
{
    if(haveThisChild(child_id))
    {
        std::cout << "EasyNode::createChild : " <<
          "this id already exist!" << std::endl;

        return false;
    }

    child_vec_.emplace_back(new EasyNode());

    EasyNode* new_child_node = child_vec_.back();

    new_child_node->id_ = child_id;
    new_child_node->parent_ = this;

    return true;
}

bool EasyNode::setChildType(
    const size_t &child_id,
    const NodeType &child_type)
{
    size_t child_idx;

    if(!findThisChild(child_id, child_idx))
    {
        std::cout << "EasyNode::setChildType : " <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "this id not exist!" << std::endl;

        return false;
    }

    EasyNode* child_node = child_vec_[child_idx];

    if(child_node == NULL)
    {
        std::cout << "EasyNode::setChildType : " <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "this child is NULL!" << std::endl;

        return false;
    }

    child_node->type_ = child_type;

    return true;
}

bool EasyNode::setChildPositionInParent(
    const size_t &child_id,
    const EasyPoint2D &child_position_in_parent)
{
    size_t child_idx;

    if(!findThisChild(child_id, child_idx))
    {
        std::cout << "EasyNode::setChildPositionInParent : " <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_position_in_parent = [" <<
          child_position_in_parent.x << "," <<
          child_position_in_parent.y << "]" << std::endl <<
          "this id not exist!" << std::endl;

        return false;
    }

    EasyNode* child_node = child_vec_[child_idx];

    if(child_node == NULL)
    {
        std::cout << "EasyNode::setChildPositionInParent : " <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_position_in_parent = [" <<
          child_position_in_parent.x << "," <<
          child_position_in_parent.y << "]" << std::endl <<
          "this child is NULL!" << std::endl;

        return false;
    }

    child_node->position_in_parent_ = child_position_in_parent;
    return true;
}

