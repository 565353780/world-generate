#include "EasyTree.h"

bool EasyTree::reset()
{
    if(root_ != NULL)
    {
        if(!root_->removeAllChild())
        {
            std::cout << "EasyTree::reset : " << std::endl <<
              "removeAllChild for root failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool EasyTree::createWorld()
{
    if(root_ != NULL)
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

    return true;
}

EasyNode* EasyTree::findNode(
    const size_t &id,
    const NodeType &type)
{
    if(root_ == NULL)
    {
        std::cout << "EasyTree::findNode : " << std::endl <<
          "Input :\n" <<
          "\tid = " << id << std::endl <<
          "\ttype = " << type << std::endl <<
          "tree is empty!" << std::endl;

        return NULL;
    }

    EasyNode* search_node = root_->findFromAllChild(id, type);

    if(search_node == NULL)
    {
        std::cout << "EasyTree::findNode : " << std::endl <<
          "Input :\n" <<
          "\tid = " << id << std::endl <<
          "\ttype = " << type << std::endl <<
          "findFromNode start from root failed!" << std::endl;

        return NULL;
    }

    return search_node;
}

