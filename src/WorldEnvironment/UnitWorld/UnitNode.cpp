#include "UnitNode.h"

UnitNode::~UnitNode()
{
    if(parent != nullptr)
    {
        parent = nullptr;
    }

    if(child_vec.size() > 0)
    {
        for(size_t i = 0; i < child_vec.size(); ++i)
        {
            if(child_vec[i] != nullptr)
            {
                delete(child_vec[i]);
                child_vec[i] = nullptr;
            }
        }
    }
}

bool UnitNode::reset()
{
    id = 0;

    type = NodeType::NodeFree;

    if(parent != nullptr)
    {
        parent = nullptr;
    }

    if(child_vec.size() > 0)
    {
        for(size_t i = 0; i < child_vec.size(); ++i)
        {
            if(child_vec[i] != nullptr)
            {
                delete(child_vec[i]);
                child_vec[i] = nullptr;
            }
        }
    }

    child_vec.clear();

    boundary_polygon.reset();

    param_on_parent_polygon = -1;

    return true;
}

UnitNode* UnitNode::findChild(
    const size_t &child_id,
    const NodeType &child_type)
{
    if(child_vec.size() == 0)
    {
        return nullptr;
    }

    for(UnitNode* child_node : child_vec)
    {
        if(child_node->id == child_id &&
            child_node->type == child_type)
        {
            return child_node;
        }
    }

    return nullptr;
}

UnitNode* UnitNode::findFromAllChild(
    const size_t &child_id,
    const NodeType &child_type)
{
    if(child_vec.size() == 0)
    {
        return nullptr;
    }

    UnitNode* search_node = findChild(child_id, child_type);

    if(search_node != nullptr)
    {
        return search_node;
    }

    for(UnitNode *child_node : child_vec)
    {
        if(child_node == nullptr)
        {
            continue;
        }

        UnitNode* deep_child_node = child_node->findFromAllChild(child_id, child_type);

        if(deep_child_node != nullptr)
        {
            return deep_child_node;
        }
    }

    return nullptr;
}

bool UnitNode::haveThisChild(
    const size_t &child_id,
    const NodeType &child_type)
{
    UnitNode* search_node = findChild(child_id, child_type);

    if(search_node == nullptr)
    {
        return false;
    }

    return true;
}

bool UnitNode::createChild(
    const std::string &child_name,
    const size_t &child_id,
    const NodeType &child_type)
{
    if(haveThisChild(child_id, child_type))
    {
        std::cout << "UnitNode::createChild : " << std::endl <<
          "Input :\n" <<
          "\tchild_name = " << child_name << std::endl <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "this child already exist!" << std::endl;

        return false;
    }

    UnitNode* new_child_node = new UnitNode();

    new_child_node->name = child_name;
    new_child_node->id = child_id;
    new_child_node->type = child_type;
    new_child_node->parent = this;

    child_vec.emplace_back(new_child_node);

    return true;
}

bool UnitNode::addChild(
    UnitNode* child_node)
{
    if(child_node == nullptr)
    {
        std::cout << "UnitNode::addChild : " << std::endl <<
          "child_node is nullptr!" << std::endl;

        return false;
    }

    if(haveThisChild(child_node->id, child_node->type))
    {
        std::cout << "UnitNode::createChild : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_node->id << std::endl <<
          "\tchild_type = " << child_node->type << std::endl <<
          "this child already exist!" << std::endl;

        return false;
    }

    child_node->parent = this;

    child_vec.emplace_back(child_node);

    return true;
}

bool UnitNode::removeChild(
    const size_t &child_id,
    const NodeType &child_type)
{
    UnitNode* search_node = findChild(child_id, child_type);

    if(search_node == nullptr)
    {
        std::cout << "UnitNode::removeChild : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "this id not found for parent " << id << "!" << std::endl;

        return false;
    }

    if(!search_node->removeAllChild())
    {
        std::cout << "UnitNode::removeChild : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "removeAllChild for child " << search_node->id << " failed!" << std::endl;

        return false;
    }

    child_vec.erase(remove(child_vec.begin(), child_vec.end(), search_node));

    delete(search_node);

    return true;
}

bool UnitNode::removeChildButRemainData(
    const size_t &child_id,
    const NodeType &child_type)
{
    UnitNode* search_node = findChild(child_id, child_type);

    if(search_node == nullptr)
    {
        std::cout << "UnitNode::removeChildButRemainData : " << std::endl <<
          "Input :\n" <<
          "\tchild_id = " << child_id << std::endl <<
          "\tchild_type = " << child_type << std::endl <<
          "this child not found for parent " << id << "!" << std::endl;

        return false;
    }

    child_vec.erase(remove(child_vec.begin(), child_vec.end(), search_node));

    return true;
}

bool UnitNode::removeAllChild()
{
    if(child_vec.size() == 0)
    {
        return true;
    }

    for(UnitNode* child_node : child_vec)
    {
        if(child_node == nullptr)
        {
            continue;
        }

        if(!child_node->removeAllChild())
        {
            std::cout << "UnitNode::removeAllChild : " << std::endl <<
              "removeAllChild on node " << id << " failed!" << std::endl;

            return false;
        }
    }

    for(size_t i = 0; i < child_vec.size(); ++i)
    {
        if(child_vec[i] != nullptr)
        {
            delete(child_vec[i]);
            child_vec[i] = nullptr;
        }
    }

    child_vec.clear();

    return true;
}

bool UnitNode::outputInfo(
    const size_t &info_level) const
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "UnitNode :" << std::endl <<
      line_start << "\tname = " << name << std::endl <<
      line_start << "\tid = " << id << std::endl <<
      line_start << "\ttype = " << type << std::endl;

    if(parent != nullptr)
    {
        std::cout << line_start << "\tparent : id = " << parent->id <<
          " type = " << parent->type << std::endl;
    }

    if(child_vec.size() > 0)
    {
        std::cout << line_start << "\tchild :" << std::endl;
        for(const UnitNode* child_node : child_vec)
        {
            child_node->outputInfo(info_level + 1);
        }
    }

    return true;
}

