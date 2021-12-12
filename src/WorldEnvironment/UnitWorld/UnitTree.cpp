#include "UnitTree.h"

UnitTree::~UnitTree()
{
    reset();

    if(root != nullptr)
    {
        delete(root);
        root = nullptr;
    }
}

bool UnitTree::reset()
{
    if(root != nullptr)
    {
        if(!root->removeAllChild())
        {
            std::cout << "UnitTree::reset :\n" <<
              "removeAllChild failed!\n";

            return false;
        }

        delete(root);
        root = nullptr;
    }

    return true;
}

bool UnitTree::resetButRemainWall()
{
    if(root == nullptr)
    {
        std::cout << "UnitTree::resetButRemainWall :\n" <<
          "root is nullptr!\n";

        return false;
    }

    for(UnitNode* wall_node : root->child_vec)
    {
        for(UnitNode* wall_child_node : wall_node->child_vec)
        {
            if(!wall_child_node->removeAllChild())
            {
                std::cout << "UnitTree::resetButRemainWall :\n" <<
                  "removeAllChild failed!\n";

                return false;
            }
        }
    }

    return true;
}

bool UnitTree::createTree()
{
    if(root != nullptr)
    {
        std::cout << "UnitTree::createTree :\n" <<
          "tree root already exist!\n";

        return false;
    }

    root = new UnitNode();

    root->name = "ROOT";
    root->id = 0;
    root->type = NodeType::World;

    return true;
}

UnitNode* UnitTree::findNode(
    const size_t &id,
    const NodeType &type)
{
    if(root == nullptr)
    {
        std::cout << "UnitTree::findNode :\n" <<
          "Input :\n" <<
          "\t id = " << id << std::endl <<
          "\t type = " << type << std::endl <<
          "tree is empty!\n";

        return nullptr;
    }

    if(root->id == id && root->type == type)
    {
        return root;
    }

    return root->findFromAllChild(id, type);
}

bool UnitTree::createNode(
    const std::string &node_name,
    const size_t &node_id,
    const NodeType &node_type,
    const size_t &parent_node_id,
    const NodeType &parent_node_type)
{
    if(findNode(node_id, node_type) != nullptr)
    {
        std::cout << "UnitTree::createNode :\n" <<
          "Input :\n" <<
          "\tnode_name = " << node_name << std::endl <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tparent_node_id = " << parent_node_id << std::endl <<
          "\tparent_node_type = " << parent_node_type << std::endl <<
          "this node already exist!" << std::endl;

        return false;
    }

    UnitNode* parent_node = findNode(parent_node_id, parent_node_type);

    if(parent_node == nullptr)
    {
        std::cout << "UnitTree::createNode :\n" <<
          "Input :\n" <<
          "\tnode_name = " << node_name << std::endl <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tparent_node_id = " << parent_node_id << std::endl <<
          "\tparent_node_type = " << parent_node_type << std::endl <<
          "this parent node not exist!" << std::endl;

        return false;
    }

    if(!parent_node->createChild(node_name, node_id, node_type))
    {
        std::cout << "UnitTree::createNode :\n" <<
          "Input :\n" <<
          "\tnode_name = " << node_name << std::endl <<
          "\tnode_id = " << node_id << std::endl <<
          "\tnode_type = " << node_type << std::endl <<
          "\tparent_node_id = " << parent_node_id << std::endl <<
          "\tparent_node_type = " << parent_node_type << std::endl <<
          "createChild failed!" << std::endl;

        return false;
    }

    return true;
}

bool UnitTree::setNodeParent(
    const size_t& node_id,
    const NodeType& node_type,
    const size_t& parent_node_id,
    const NodeType& parent_node_type)
{
    UnitNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "UnitTree::setNodeParent :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "\t parent_node_id = " << parent_node_id << std::endl <<
          "\t parent_node_type = " << parent_node_type << std::endl <<
          "this node not exist!\n";

        return false;
    }

    UnitNode* search_node_parent = search_node->parent;

    if(search_node_parent != nullptr)
    {
        if(search_node_parent->id == parent_node_id &&
            search_node_parent->type == parent_node_type)
        {
            return true;
        }
    }

    UnitNode* search_parent_node = findNode(parent_node_id, parent_node_type);

    if(search_parent_node == nullptr)
    {
        std::cout << "UnitTree::setNodeParent :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "\t parent_node_id = " << parent_node_id << std::endl <<
          "\t parent_node_type = " << parent_node_type << std::endl <<
          "parent node not exist!\n";

        return false;
    }

    if(search_node_parent != nullptr)
    {
        search_node_parent->removeChildButRemainData(node_id, node_type);
    }

    search_parent_node->addChild(search_node);

    return true;
}

bool UnitTree::setBoundaryPolygon(
    const size_t& node_id,
    const NodeType& node_type,
    const EasyPolygon2D& new_boundary_polygon)
{
    UnitNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "UnitTree::setBoundaryPolygon :\n" <<
          "Input :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "this node not exist!\n";

        return false;
    }

    search_node->boundary_polygon = new_boundary_polygon;

    return true;
}

bool UnitTree::setNodePositionOnParentPolygonByPolygonParam(
    const size_t& node_id,
    const NodeType& node_type,
    const float& point_param_on_parent_polygon,
    const float& new_dist_to_parent_polygon,
    const float& new_target_width,
    const float& new_target_height,
    const float& new_left_angle,
    const float& new_right_angle)
{
    UnitNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "UnitTree::setNodePositionOnParentPolygonByPolygonParam :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "\t point_param_on_parent_polygon = " << point_param_on_parent_polygon << std::endl <<
          "\t new_dist_to_parent_polygon = " << new_dist_to_parent_polygon << std::endl <<
          "\t new_target_size = [" << new_target_width << "," <<
          new_target_height << "]\n" <<
          "\t new_angle = [" << new_left_angle << "," <<
          new_right_angle << "]\n" <<
          "this node not exist!\n";

        return false;
    }

    if(!search_node->setPositionOnParentPolygonByPolygonParam(
          point_param_on_parent_polygon,
          new_dist_to_parent_polygon,
          new_target_width,
          new_target_height,
          new_left_angle,
          new_right_angle))
    {
        std::cout << "UnitTree::setNodePositionOnParentPolygonByPolygonParam :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "\t point_param_on_parent_polygon = " << point_param_on_parent_polygon << std::endl <<
          "\t new_dist_to_parent_polygon = " << new_dist_to_parent_polygon << std::endl <<
          "\t new_target_size = [" << new_target_width << "," <<
          new_target_height << "]\n" <<
          "\t new_angle = [" << new_left_angle << "," <<
          new_right_angle << "]\n" <<
          "setPositionOnParentPolygonByPolygonParam failed!\n";

        return false;
    }

    std::cout << "room " << node_id << " now at " <<
      search_node->polygon_point_on_parent_polygon.position.x << "," <<
      search_node->polygon_point_on_parent_polygon.position.y << std::endl;

    return true;
}

bool UnitTree::setNodePositionOnParentPolygonByLineParam(
    const size_t& node_id,
    const NodeType& node_type,
    const size_t& parent_polygon_line_idx,
    const float& point_param_on_line,
    const float& new_dist_to_parent_polygon,
    const float& new_target_width,
    const float& new_target_height,
    const float& new_left_angle,
    const float& new_right_angle)
{
    UnitNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "UnitTree::setNodePositionOnParentPolygonByLineParam :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "\t parent_polygon_line_idx = " << parent_polygon_line_idx << std::endl <<
          "\t point_param_on_line = " << point_param_on_line << std::endl <<
          "\t new_dist_to_parent_polygon = " << new_dist_to_parent_polygon << std::endl <<
          "\t new_target_size = [" << new_target_width << "," <<
          new_target_height << "]\n" <<
          "\t new_angle = [" << new_left_angle << "," <<
          new_right_angle << "]\n" <<
          "this node not exist!\n";

        return false;
    }

    if(!search_node->setPositionOnParentPolygonByLineParam(
          parent_polygon_line_idx,
          point_param_on_line,
          new_dist_to_parent_polygon,
          new_target_width,
          new_target_height,
          new_left_angle,
          new_right_angle))
    {
        std::cout << "UnitTree::setNodePositionOnParentPolygonByLineParam :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "\t parent_polygon_line_idx = " << parent_polygon_line_idx << std::endl <<
          "\t point_param_on_line = " << point_param_on_line << std::endl <<
          "\t new_dist_to_parent_polygon = " << new_dist_to_parent_polygon << std::endl <<
          "\t new_target_size = [" << new_target_width << "," <<
          new_target_height << "]\n" <<
          "\t new_angle = [" << new_left_angle << "," <<
          new_right_angle << "]\n" <<
          "setPositionOnParentPolygonByPolygonParam failed!\n";

        return false;
    }

    return true;
}

bool UnitTree::setNodePositionOnParentPolygonByLength(
    const size_t& node_id,
    const NodeType& node_type,
    const float& point_length,
    const float& new_dist_to_parent_polygon,
    const float& new_target_width,
    const float& new_target_height,
    const float& new_left_angle,
    const float& new_right_angle)
{
    UnitNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "UnitTree::setNodePositionOnParentPolygonByLength :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "\t point_length = " << point_length << std::endl <<
          "\t new_dist_to_parent_polygon = " << new_dist_to_parent_polygon << std::endl <<
          "\t new_target_size = [" << new_target_width << "," <<
          new_target_height << "]\n" <<
          "\t new_angle = [" << new_left_angle << "," <<
          new_right_angle << "]\n" <<
          "this node not exist!\n";

        return false;
    }

    if(!search_node->setPositionOnParentPolygonByLength(
          point_length,
          new_dist_to_parent_polygon,
          new_target_width,
          new_target_height,
          new_left_angle,
          new_right_angle))
    {
        std::cout << "UnitTree::setNodePositionOnParentPolygonByLineParam :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "\t point_length = " << point_length << std::endl <<
          "\t new_dist_to_parent_polygon = " << new_dist_to_parent_polygon << std::endl <<
          "\t new_target_size = [" << new_target_width << "," <<
          new_target_height << "]\n" <<
          "\t new_angle = [" << new_left_angle << "," <<
          new_right_angle << "]\n" <<
          "setPositionOnParentPolygonByPolygonParam failed!\n";

        return false;
    }

    return true;
}

bool UnitTree::setNodePositionOnParentPolygonByPosition(
    const size_t& node_id,
    const NodeType& node_type,
    const EasyPoint2D& point_position,
    const float& new_dist_to_parent_polygon,
    const float& new_target_width,
    const float& new_target_height,
    const float& new_left_angle,
    const float& new_right_angle)
{
    UnitNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "UnitTree::setNodePositionOnParentPolygonByLineParam :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "\t point_position = [" << point_position.x << "," <<
          point_position.y << "]\n" <<
          "\t new_dist_to_parent_polygon = " << new_dist_to_parent_polygon << std::endl <<
          "\t new_target_size = [" << new_target_width << "," <<
          new_target_height << "]\n" <<
          "\t new_angle = [" << new_left_angle << "," <<
          new_right_angle << "]\n" <<
          "this node not exist!\n";

        return false;
    }

    if(!search_node->setPositionOnParentPolygonByPosition(
          point_position,
          new_dist_to_parent_polygon,
          new_target_width,
          new_target_height,
          new_left_angle,
          new_right_angle))
    {
        std::cout << "UnitTree::setNodePositionOnParentPolygonByLineParam :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "\t point_position = [" << point_position.x << "," <<
          point_position.y << "]\n" <<
          "\t new_dist_to_parent_polygon = " << new_dist_to_parent_polygon << std::endl <<
          "\t new_target_size = [" << new_target_width << "," <<
          new_target_height << "]\n" <<
          "\t new_angle = [" << new_left_angle << "," <<
          new_right_angle << "]\n" <<
          "setPositionOnParentPolygonByPolygonParam failed!\n";

        return false;
    }

    return true;
}

bool UnitTree::updateNodePolygon(
    const size_t& node_id,
    const NodeType& node_type)
{
    UnitNode* search_node = findNode(node_id, node_type);

    if(search_node == nullptr)
    {
        std::cout << "UnitTree::updateNodePolygon :\n" <<
          "Input :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "this node not exist!\n";

        return false;
    }

    if(!search_node->updatePolygon())
    {
        std::cout << "UnitTree::updateNodePolygon :\n" <<
          "Input :\n" <<
          "\t node_id = " << node_id << std::endl <<
          "\t node_type = " << node_type << std::endl <<
          "updatePolygon failed!\n";

        return false;
    }

    return true;
}

bool UnitTree::outputInfo(
    const size_t& info_level) const
{
    std::cout << "UnitTree :\n";

    root->outputInfo(info_level + 1);

    return true;
}

