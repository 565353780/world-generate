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
    name = "";
    id = 0;
    type = NodeType::NodeFree;

    boundary_polygon.reset();
    right_down_point_idx = 0;
    right_up_point_idx = 0;
    left_up_point_idx = 0;

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

    polygon_point_on_parent_polygon.reset();
    dist_to_parent_polygon = -1;
    width = -1;
    height = -1;
    left_angle = 0;
    right_angle = 0;

    real_right_width = -1;
    real_left_width = -1;

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

    UnitNode* child_node = new UnitNode();

    child_node->name = child_name;
    child_node->id = child_id;
    child_node->type = child_type;
    child_node->parent = this;

    child_vec.emplace_back(child_node);

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

bool UnitNode::setPositionOnParentPolygonByPolygonParam(
    const float& point_param_on_parent_polygon,
    const float& target_dist_to_parent_polygon,
    const float& target_width,
    const float& target_height,
    const float& target_left_angle,
    const float& target_right_angle)
{
    polygon_point_on_parent_polygon.reset();

    if(parent == nullptr)
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByPolygonParam :\n" <<
          "\t point_param_on_parent_polygon = " << point_param_on_parent_polygon << std::endl <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "parent not exist!\n";

        return false;
    }

    if(!polygon_point_on_parent_polygon.updateByPolygonParam(
          parent->boundary_polygon, point_param_on_parent_polygon))
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByPolygonParam :\n" <<
          "\t point_param_on_parent_polygon = " << point_param_on_parent_polygon << std::endl <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "updateByPolygonParam failed!\n";

        return false;
    }

    dist_to_parent_polygon = target_dist_to_parent_polygon;
    width = target_width;
    height = target_height;
    left_angle = target_left_angle;
    right_angle = target_right_angle;

    if(!updateWidth())
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByPolygonParam :\n" <<
          "\t point_param_on_parent_polygon = " << point_param_on_parent_polygon << std::endl <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "updateWidth failed!\n";

        return false;
    }

    return true;
}

bool UnitNode::setPositionOnParentPolygonByLineParam(
    const size_t& parent_polygon_line_idx,
    const float& point_param_on_line,
    const float& target_dist_to_parent_polygon,
    const float& target_width,
    const float& target_height,
    const float& target_left_angle,
    const float& target_right_angle)
{
    polygon_point_on_parent_polygon.reset();

    if(parent == nullptr)
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByLineParam :\n" <<
          "\t parent_polygon_line_idx = " << parent_polygon_line_idx << std::endl <<
          "\t point_param_on_line = " << point_param_on_line << std::endl <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "parent not exist!\n";

        return false;
    }

    if(!polygon_point_on_parent_polygon.updateByLineParam(
          parent->boundary_polygon, parent_polygon_line_idx, point_param_on_line))
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByLineParam :\n" <<
          "\t parent_polygon_line_idx = " << parent_polygon_line_idx << std::endl <<
          "\t point_param_on_line = " << point_param_on_line << std::endl <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "updateByPolygonParam failed!\n";

        return false;
    }

    dist_to_parent_polygon = target_dist_to_parent_polygon;
    width = target_width;
    height = target_height;
    left_angle = target_left_angle;
    right_angle = target_right_angle;

    if(!updateWidth())
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByLineParam :\n" <<
          "\t parent_polygon_line_idx = " << parent_polygon_line_idx << std::endl <<
          "\t point_param_on_line = " << point_param_on_line << std::endl <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "updateWidth failed!\n";

        return false;
    }

    return true;
}

bool UnitNode::setPositionOnParentPolygonByLength(
    const float& point_length,
    const float& target_dist_to_parent_polygon,
    const float& target_width,
    const float& target_height,
    const float& target_left_angle,
    const float& target_right_angle)
{
    polygon_point_on_parent_polygon.reset();

    if(parent == nullptr)
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByLength :\n" <<
          "\t point_length = " << point_length << std::endl <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "parent not exist!\n";

        return false;
    }

    if(!polygon_point_on_parent_polygon.updateByLength(
          parent->boundary_polygon, point_length))
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByLength :\n" <<
          "\t point_length = " << point_length << std::endl <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "updateByPolygonParam failed!\n";

        return false;
    }

    dist_to_parent_polygon = target_dist_to_parent_polygon;
    width = target_width;
    height = target_height;
    left_angle = target_left_angle;
    right_angle = target_right_angle;

    if(!updateWidth())
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByLength :\n" <<
          "\t point_length = " << point_length << std::endl <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "updateWidth failed!\n";

        return false;
    }

    return true;
}

bool UnitNode::setPositionOnParentPolygonByPosition(
    const EasyPoint2D& point_position,
    const float& target_dist_to_parent_polygon,
    const float& target_width,
    const float& target_height,
    const float& target_left_angle,
    const float& target_right_angle)
{
    polygon_point_on_parent_polygon.reset();

    if(parent == nullptr)
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByLineParam :\n" <<
          "\t point_position = [" << point_position.x << "," <<
          point_position.y << "]\n" <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "parent not exist!\n";

        return false;
    }

    if(!polygon_point_on_parent_polygon.updateByPosition(
          parent->boundary_polygon, point_position))
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByLineParam :\n" <<
          "\t point_position = [" << point_position.x << "," <<
          point_position.y << "]\n" <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "updateByPolygonParam failed!\n";

        return false;
    }

    dist_to_parent_polygon = target_dist_to_parent_polygon;
    width = target_width;
    height = target_height;
    left_angle = target_left_angle;
    right_angle = target_right_angle;

    if(!updateWidth())
    {
        std::cout << "UnitNode::setPositionOnParentPolygonByLineParam :\n" <<
          "\t point_position = [" << point_position.x << "," <<
          point_position.y << "]\n" <<
          "\t target_dist_to_parent_polygon = " << target_dist_to_parent_polygon << std::endl <<
          "\t target_size = [" << target_width << "," <<
          target_height << "]\n" <<
          "\t target_angle = [" << target_left_angle << "," <<
          target_right_angle << "]\n" <<
          "updateWidth failed!\n";

        return false;
    }

    return true;
}

bool UnitNode::updateWidth()
{
    test_intersection_vec_.clear();

    const float error_max = 0.01;

    EasyPolygon2D polygon;

    EasyPolygonPoint2D left_point_on_parent_polygon;
    float left_length = polygon_point_on_parent_polygon.length - width / 2.0;
    if(left_length < 0)
    {
        left_length += parent->boundary_polygon.perimeter;
    }

    if(!left_point_on_parent_polygon.updateByLength(parent->boundary_polygon, left_length))
    {
        std::cout << "UnitNode::updateWidth :\n" <<
          "updateByLength for left point failed!\n";

        return false;
    }

    EasyPolygonPoint2D right_point_on_parent_polygon;
    float right_length = polygon_point_on_parent_polygon.length + width / 2.0;
    if(right_length >= parent->boundary_polygon.perimeter)
    {
        right_length -= parent->boundary_polygon.perimeter;
    }

    if(!right_point_on_parent_polygon.updateByLength(parent->boundary_polygon, right_length))
    {
        std::cout << "UnitNode::updateWidth :\n" <<
          "updateByLength for right point failed!\n";

        return false;
    }

    polygon.addPoint(left_point_on_parent_polygon.position);

    if(left_point_on_parent_polygon.line_idx < right_point_on_parent_polygon.line_idx)
    {
        for(size_t i = left_point_on_parent_polygon.line_idx + 1;
            i <= right_point_on_parent_polygon.line_idx; ++i)
        {
            polygon.addPoint(parent->boundary_polygon.point_list[i]);
        }
    }
    else if(left_point_on_parent_polygon.line_idx > right_point_on_parent_polygon.line_idx)
    {
        const size_t right_point_line_real_idx =
          right_point_on_parent_polygon.line_idx + parent->boundary_polygon.point_list.size();

        for(size_t i = left_point_on_parent_polygon.line_idx + 1;
            i <= right_point_line_real_idx; ++i)
        {
            polygon.addPoint(parent->boundary_polygon.point_list[
                i % parent->boundary_polygon.point_list.size()]);
        }

    }

    polygon.addPoint(right_point_on_parent_polygon.position);

    EasyPoint2D left_line_direction;
    left_line_direction.setPosition(
        std::cos(left_angle) * left_point_on_parent_polygon.left_direction.x -
        std::sin(left_angle) * left_point_on_parent_polygon.left_direction.y,
        std::sin(left_angle) * left_point_on_parent_polygon.left_direction.x +
        std::cos(left_angle) * left_point_on_parent_polygon.left_direction.y);

    EasyPoint2D right_line_direction;
    right_line_direction.setPosition(
        std::cos(right_angle) * right_point_on_parent_polygon.right_direction.x -
        std::sin(right_angle) * right_point_on_parent_polygon.right_direction.y,
        std::sin(right_angle) * right_point_on_parent_polygon.right_direction.x +
        std::cos(right_angle) * right_point_on_parent_polygon.right_direction.y);

    EasyPoint2D left_end_point;
    left_end_point.setPosition(
        left_point_on_parent_polygon.position.x + left_line_direction.x * height,
        left_point_on_parent_polygon.position.y + left_line_direction.y * height);

    EasyPoint2D right_end_point;
    right_end_point.setPosition(
        right_point_on_parent_polygon.position.x + right_line_direction.x * height,
        right_point_on_parent_polygon.position.y + right_line_direction.y * height);

    EasyLine2D left_line;
    left_line.setPosition(left_point_on_parent_polygon.position, left_end_point);

    EasyLine2D right_line;
    right_line.setPosition(right_point_on_parent_polygon.position, right_end_point);

    if(EasyComputation::isLineCross(left_line, right_line))
    {
        EasyPoint2D line_cross_point;
        if(!EasyComputation::getLineCrossPoint(left_line, right_line, line_cross_point))
        {
            std::cout << "UnitNode::updateWidth :\n" <<
              "getLineCrossPoint failed!\n";

            return false;
        }

        real_right_width = width / 2.0;
        real_left_width = width / 2.0;

        return true;
    }

    polygon.addPoint(right_end_point);
    polygon.addPoint(left_end_point);

    std::vector<EasyPolygon2D> polygon_vec;
    std::vector<EasyIntersection2D> intersection_vec;
    polygon_vec.emplace_back(polygon);
    polygon_vec.emplace_back(parent->boundary_polygon);
    if(!EasyComputation::getPolygonIntersection(polygon_vec, intersection_vec))
    {
        std::cout << "UnitNode::updateWidth :\n" <<
          "getPolygonIntersection failed!\n";

        return false;
    }

    std::vector<EasyPolygonPoint2D> intersection_polygon_point_vec;

    for(const EasyIntersection2D& intersection : intersection_vec)
    {
        EasyPolygonPoint2D intersection_polygon_point;
        if(!intersection_polygon_point.updateByPosition(parent->boundary_polygon, intersection.point))
        {
            std::cout << "UnitNode::updateWidth :\n" <<
              "getPolygonIntersection failed!\n";

            return false;
        }

        const float length_diff = std::abs(intersection_polygon_point.length - polygon_point_on_parent_polygon.length);

        if(length_diff <= width / 2.0 + error_max)
        {
            continue;
        }

        intersection_polygon_point_vec.emplace_back(intersection_polygon_point);

        test_intersection_vec_.emplace_back(intersection_polygon_point.position);
    }

    if(intersection_polygon_point_vec.size() == 0)
    {
        real_right_width = width / 2.0;
        real_left_width = width / 2.0;

        return true;
    }

    float max_right_param_diff = 0;
    float max_left_param_diff = 0;

    for(const EasyPolygonPoint2D& intersection_polygon_point : intersection_polygon_point_vec)
    {
        float current_right_param_diff =
          intersection_polygon_point.param_on_polygon - polygon_point_on_parent_polygon.param_on_polygon;

        if(current_right_param_diff < 0)
        {
            current_right_param_diff += 1.0;
        }

        if(current_right_param_diff > max_right_param_diff)
        {
            // if(intersection_polygon_point.line_idx == polygon_point_on_parent_polygon.line_idx)
            // {
            //     continue;
            // }

            max_right_param_diff = current_right_param_diff;
        }

        const float current_left_param_diff = 1.0 - current_right_param_diff;
        if(current_left_param_diff > max_left_param_diff)
        {
            // if(intersection_polygon_point.line_idx == polygon_point_on_parent_polygon.line_idx)
            // {
            //     continue;
            // }

            max_left_param_diff = current_left_param_diff;
        }
    }

    if(max_right_param_diff < max_left_param_diff)
    {
        real_left_width = width / 2.0;

        for(const EasyPolygonPoint2D& intersection_polygon_point : intersection_polygon_point_vec)
        {
            if(EasyComputation::isPointOnLine(intersection_polygon_point.position, left_line))
            {
                real_right_width =  intersection_polygon_point.length - polygon_point_on_parent_polygon.length;

                return true;
            }
        }

        real_right_width = max_right_param_diff * parent->boundary_polygon.perimeter;

        return true;
    }

    real_right_width = width / 2.0;

    for(const EasyPolygonPoint2D& intersection_polygon_point : intersection_polygon_point_vec)
    {
        if(EasyComputation::isPointOnLine(intersection_polygon_point.position, right_line))
        {
            real_left_width = polygon_point_on_parent_polygon.length - intersection_polygon_point.length;

            return true;
        }
    }

    real_left_width = max_left_param_diff * parent->boundary_polygon.perimeter;

    return true;
}

bool UnitNode::updatePolygon()
{
    boundary_polygon.reset();

    EasyPolygonPoint2D left_point_on_parent_polygon;
    float left_length = polygon_point_on_parent_polygon.length - real_left_width;
    if(left_length < 0)
    {
        left_length += parent->boundary_polygon.perimeter;
    }

    if(!left_point_on_parent_polygon.updateByLength(parent->boundary_polygon, left_length))
    {
        std::cout << "UnitNode::updatePolygon :\n" <<
          "updateByLength for left point failed!\n";

        return false;
    }

    EasyPolygonPoint2D right_point_on_parent_polygon;
    float right_length = polygon_point_on_parent_polygon.length + real_right_width;
    if(right_length >= parent->boundary_polygon.perimeter)
    {
        right_length -= parent->boundary_polygon.perimeter;
    }

    if(!right_point_on_parent_polygon.updateByLength(parent->boundary_polygon, right_length))
    {
        std::cout << "UnitNode::updatePolygon :\n" <<
          "updateByLength for right point failed!\n";

        return false;
    }

    boundary_polygon.addPoint(left_point_on_parent_polygon.position);

    if(left_point_on_parent_polygon.line_idx < right_point_on_parent_polygon.line_idx)
    {
        for(size_t i = left_point_on_parent_polygon.line_idx + 1;
            i <= right_point_on_parent_polygon.line_idx; ++i)
        {
            boundary_polygon.addPoint(parent->boundary_polygon.point_list[i]);
        }
    }
    else if(left_point_on_parent_polygon.line_idx > right_point_on_parent_polygon.line_idx)
    {
        const size_t right_point_line_real_idx =
          right_point_on_parent_polygon.line_idx + parent->boundary_polygon.point_list.size();

        for(size_t i = left_point_on_parent_polygon.line_idx + 1;
            i <= right_point_line_real_idx; ++i)
        {
            boundary_polygon.addPoint(parent->boundary_polygon.point_list[
                i % parent->boundary_polygon.point_list.size()]);
        }

    }

    right_down_point_idx = boundary_polygon.point_list.size();
    boundary_polygon.addPoint(right_point_on_parent_polygon.position);

    EasyPoint2D left_line_direction;
    left_line_direction.setPosition(
        std::cos(left_angle) * left_point_on_parent_polygon.left_direction.x -
        std::sin(left_angle) * left_point_on_parent_polygon.left_direction.y,
        std::sin(left_angle) * left_point_on_parent_polygon.left_direction.x +
        std::cos(left_angle) * left_point_on_parent_polygon.left_direction.y);

    EasyPoint2D right_line_direction;
    right_line_direction.setPosition(
        std::cos(right_angle) * right_point_on_parent_polygon.right_direction.x -
        std::sin(right_angle) * right_point_on_parent_polygon.right_direction.y,
        std::sin(right_angle) * right_point_on_parent_polygon.right_direction.x +
        std::cos(right_angle) * right_point_on_parent_polygon.right_direction.y);

    EasyPoint2D left_end_point;
    left_end_point.setPosition(
        left_point_on_parent_polygon.position.x + left_line_direction.x * height,
        left_point_on_parent_polygon.position.y + left_line_direction.y * height);

    EasyPoint2D right_end_point;
    right_end_point.setPosition(
        right_point_on_parent_polygon.position.x + right_line_direction.x * height,
        right_point_on_parent_polygon.position.y + right_line_direction.y * height);

    EasyLine2D left_line;
    left_line.setPosition(left_point_on_parent_polygon.position, left_end_point);

    EasyLine2D right_line;
    right_line.setPosition(right_point_on_parent_polygon.position, right_end_point);

    if(EasyComputation::isLineCross(left_line, right_line))
    {
        const float real_width2 = EasyComputation::pointDist2(left_line.point_1, right_line.point_1);

        if(real_width2 > 0.0001)
        {

            // std::cout << "=================\n";
            // std::cout << "Line Cross :\n";
            // left_line.outputInfo(1);
            // right_line.outputInfo(1);
            // std::cout << "width = " << EasyComputation::pointDist(right_point_on_parent_polygon.position,
                // left_point_on_parent_polygon.position) << std::endl;
            // std::cout << "=================\n";

            EasyPoint2D line_cross_point;
            if(!EasyComputation::getLineCrossPoint(left_line, right_line, line_cross_point))
            {
                std::cout << "UnitNode::updatePolygon :\n" <<
                  "getLineCrossPoint failed!\n";

                return false;
            }

            right_up_point_idx = boundary_polygon.point_list.size();
            left_up_point_idx = boundary_polygon.point_list.size();
            boundary_polygon.addPoint(line_cross_point);

            return true;
        }
    }

    std::cout << "width compare : " << width / 2.0 << "," <<
      real_left_width << "," <<
      real_right_width << std::endl;

    if(real_right_width != width / 2.0)
    {
        right_up_point_idx = boundary_polygon.point_list.size();
        left_up_point_idx = boundary_polygon.point_list.size();
        std::cout << "line cross 2!\n";
        boundary_polygon.addPoint(left_end_point);

        return true;
    }

    if(real_left_width != width / 2.0)
    {
        right_up_point_idx = boundary_polygon.point_list.size();
        left_up_point_idx = boundary_polygon.point_list.size();
        std::cout << "line cross 3!\n";
        boundary_polygon.addPoint(right_end_point);

        return true;
    }

    right_up_point_idx = boundary_polygon.point_list.size();
    boundary_polygon.addPoint(right_end_point);

    left_up_point_idx = boundary_polygon.point_list.size();
    boundary_polygon.addPoint(left_end_point);

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

    std::cout << line_start << "UnitNode :\n" <<
      line_start << "\t name = " << name << std::endl <<
      line_start << "\t id = " << id << std::endl <<
      line_start << "\t type = " << type << std::endl;

    if(parent != nullptr)
    {
        std::cout << line_start << "\t parent : id = " << parent->id <<
          " type = " << parent->type << std::endl;
    }

    if(child_vec.size() > 0)
    {
        std::cout << line_start << "\t child :\n";
        for(const UnitNode* child_node : child_vec)
        {
            child_node->outputInfo(info_level + 1);
        }
    }

    return true;
}

