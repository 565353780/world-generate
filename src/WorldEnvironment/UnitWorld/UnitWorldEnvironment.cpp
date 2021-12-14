#include "UnitWorldEnvironment.h"

bool UnitWorldEnvironment::reset()
{
    if(!unit_world_controller_.reset())
    {
        std::cout << "UnitWorldEnvironment::reset :\n" <<
          "reset for unit_world_controller_ failed!\n";

        return false;
    }

    if(!unit_world_transformer_.resetTransform())
    {
        std::cout << "UnitWorldEnvironment::reset :\n" <<
          "resetTransform failed!\n";

        return false;
    }

    outer_wall_info_vec_.clear();
    inner_wall_info_vec_.clear();
    wall_room_info_vec_.clear();

    return true;
}

bool UnitWorldEnvironment::resetButRemainWall()
{
    if(!unit_world_controller_.resetButRemainWall())
    {
        std::cout << "UnitWorldEnvironment::resetButRemainWall :\n" <<
          "resetButRemainWall for unit_world_controller_ failed!\n";

        return false;
    }

    wall_room_info_vec_.clear();

    return true;
}

bool UnitWorldEnvironment::setImageSize(
    const size_t& image_width,
    const size_t& image_height,
    const size_t& free_area_width)
{
    if(!unit_world_transformer_.setImageSize(
          image_width, image_height, free_area_width))
    {
        std::cout << "UnitWorldEnvironment::setImageSize :\n" <<
          "Input :\n" <<
          "\t image_size = [" << image_width << "," <<
          image_height << "]\n" <<
          "\t free_area_width = " << free_area_width << std::endl <<
          "setImageSize failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldEnvironment::createNewWorld()
{
    if(!unit_world_controller_.createWorld())
    {
        std::cout << "UnitWorldEnvironment::createNewWorld :\n" <<
          "createWorld for unit_world_controller_ failed!\n";

        return false;
    }

    if(!unit_world_transformer_.resetTransform())
    {
        std::cout << "UnitWorldEnvironment::createNewWorld :\n" <<
          "resetTransform failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldEnvironment::createOuterWall()
{
    EasyNodeInfo new_outer_wall_info;
    new_outer_wall_info.name = "OuterWall";
    new_outer_wall_info.id = outer_wall_info_vec_.size();
    new_outer_wall_info.type = NodeType::OuterWall;

    outer_wall_info_vec_.emplace_back(new_outer_wall_info);

    return true;
}

bool UnitWorldEnvironment::createInnerWall()
{
    EasyNodeInfo new_inner_wall_info;
    new_inner_wall_info.name = "InnerWall";
    new_inner_wall_info.id = inner_wall_info_vec_.size();
    new_inner_wall_info.type = NodeType::InnerWall;

    inner_wall_info_vec_.emplace_back(new_inner_wall_info);

    return true;
}

bool UnitWorldEnvironment::addPointForOuterWall(
    const size_t& outerwall_idx,
    const float& point_x,
    const float& point_y)
{
    if(outerwall_idx >= outer_wall_info_vec_.size())
    {
        std::cout << "UnitWorldEnvironment::addPointForOuterWall :\n" <<
          "Input :\n" <<
          "\t outerwall_idx = " << outerwall_idx << std::endl <<
          "\t point = [" << point_x << "," <<
          point_y << "]\n" <<
          "outerwall_idx out of range!\n";

        return false;
    }

    if(!outer_wall_info_vec_[outerwall_idx].boundary_polygon.addPoint(point_x, point_y))
    {
        std::cout << "UnitWorldEnvironment::addPointForOuterWall :\n" <<
          "Input :\n" <<
          "\t outerwall_idx = " << outerwall_idx << std::endl <<
          "\t point = [" << point_x << "," <<
          point_y << "]\n" <<
          "addPoint failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldEnvironment::addPointForInnerWall(
    const size_t& innerwall_idx,
    const float& point_x,
    const float& point_y)
{
    if(innerwall_idx >= inner_wall_info_vec_.size())
    {
        std::cout << "UnitWorldEnvironment::addPointForInnerWall :\n" <<
          "Input :\n" <<
          "\t innerwall_idx = " << innerwall_idx << std::endl <<
          "\t point = [" << point_x << "," <<
          point_y << "]\n" <<
          "innerwall_idx out of range!\n";

        return false;
    }

    if(!inner_wall_info_vec_[innerwall_idx].boundary_polygon.addPoint(point_x, point_y))
    {
        std::cout << "UnitWorldEnvironment::addPointForInnerWall :\n" <<
          "Input :\n" <<
          "\t innerwall_idx = " << innerwall_idx << std::endl <<
          "\t point = [" << point_x << "," <<
          point_y << "]\n" <<
          "addPoint failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldEnvironment::generateWall()
{
    if(!unit_world_transformer_.resetTransform())
    {
        std::cout << "UnitWorldEnvironment::generateWall :\n" <<
          "resetTransform failed!\n";

        return false;
    }

    for(const EasyNodeInfo& outer_wall_info : outer_wall_info_vec_)
    {
        if(!unit_world_controller_.createWall(
              outer_wall_info.name, outer_wall_info.id, outer_wall_info.type))
        {
            std::cout << "UnitWorldEnvironment::generateWall :\n" <<
              "createWall for outer wall failed!\n";

            return false;
        }

        const EasyPolygon2D& outer_wall_boundary_polygon =
          outer_wall_info.boundary_polygon;

        if(!unit_world_controller_.setWallBoundaryPolygon(
              outer_wall_info.id, outer_wall_info.type, outer_wall_boundary_polygon))
        {
            std::cout << "UnitWorldEnvironment::generateWall :\n" <<
              "setWallBoundaryPolygon for outer wall failed!\n";

            return false;
        }

        for(const EasyPoint2D& outer_wall_boundary_point : outer_wall_boundary_polygon.point_list)
        {
            if(!unit_world_transformer_.expandArea(
                  outer_wall_boundary_point.x, outer_wall_boundary_point.y))
            {
                std::cout << "UnitWorldEnvironment::generateWall :\n" <<
                  "expandArea for outer wall boundary point failed!\n";

                return false;
            }
        }
    }

    for(const EasyNodeInfo& inner_wall_info : inner_wall_info_vec_)
    {
        if(!unit_world_controller_.createWall(
              inner_wall_info.name, inner_wall_info.id, inner_wall_info.type))
        {
            std::cout << "UnitWorldEnvironment::generateWall :\n" <<
              "createWall for inner wall failed!\n";

            return false;
        }

        const EasyPolygon2D& inner_wall_boundary_polygon =
          inner_wall_info.boundary_polygon;

        if(!unit_world_controller_.setWallBoundaryPolygon(
              inner_wall_info.id, inner_wall_info.type, inner_wall_boundary_polygon))
        {
            std::cout << "UnitWorldEnvironment::generateWall :\n" <<
              "setWallBoundaryPolygon for inner wall failed!\n";

            return false;
        }

        for(const EasyPoint2D& inner_wall_boundary_point : inner_wall_boundary_polygon.point_list)
        {
            if(!unit_world_transformer_.expandArea(
                  inner_wall_boundary_point.x, inner_wall_boundary_point.y))
            {
                std::cout << "UnitWorldEnvironment::generateWall :\n" <<
                  "expandArea for inner wall boundary point failed!\n";

                return false;
            }
        }
    }

    if(!unit_world_transformer_.updateTransform())
    {
        std::cout << "UnitWorldEnvironment::generateWall :\n" <<
          "updateTransform failed!\n";

        return false;
    }

    return true;
}

bool UnitWorldEnvironment::placeWallRoomByPosition(
    const size_t& point_x_in_image,
    const size_t& point_y_in_image)
{
    float point_x_in_world, point_y_in_world;

    if(!unit_world_transformer_.transPointToWorld(
          point_x_in_image, point_y_in_image,
          point_x_in_world, point_y_in_world))
    {
        std::cout << "UnitWorldEnvironment::placeWallRoomByPosition :\n" <<
          "Input :\n" <<
          "\t point_in_image = [" << point_x_in_image << "," <<
          point_y_in_image << "]\n" <<
          "transPointToWorld failed!\n";

        return false;
    }

    EasyNodeInfo new_wall_room_info;
    new_wall_room_info.name = "WallRoom";
    new_wall_room_info.id = wall_room_info_vec_.size();
    new_wall_room_info.type = NodeType::WallRoom;

    EasyPoint2D point_in_world;
    point_in_world.setPosition(point_x_in_world, point_y_in_world);

    if(!unit_world_controller_.setRoomPositionOnTreeByPosition(
          new_wall_room_info.id, new_wall_room_info.type, point_in_world))
    {
        std::cout << "UnitWorldEnvironment::placeWallRoomByPosition :\n" <<
          "Input :\n" <<
          "\t point_in_image = [" << point_x_in_image << "," <<
          point_y_in_image << "]\n" <<
          "setRoomPositionOnTreeByPosition failed!\n";

        return false;
    }

    if(!unit_world_controller_.unit_tree.updateNodePolygon(
          new_wall_room_info.id, new_wall_room_info.type))
    {
        std::cout << "UnitWorldEnvironment::placeWallRoomByPosition :\n" <<
          "Input :\n" <<
          "\t point_in_image = [" << point_x_in_image << "," <<
          point_y_in_image << "]\n" <<
          "updateNodePolygon failed!\n";

        return false;
    }

    wall_room_info_vec_.emplace_back(new_wall_room_info);

    return true;
}

bool UnitWorldEnvironment::setWallRoomPositionByPosition(
    const size_t& wall_room_idx,
    const size_t& point_x_in_image,
    const size_t& point_y_in_image)
{
    if(wall_room_idx >= wall_room_info_vec_.size())
    {
        std::cout << "UnitWorldEnvironment::setWallRoomPositionByPosition :\n" <<
          "Input :\n" <<
          "\t wall_room_idx = " << wall_room_idx << std::endl <<
          "\t point_in_image = [" << point_x_in_image << "," <<
          point_y_in_image << "]\n" <<
          "wall_room_idx out of range!\n";

        return false;
    }

    float point_x_in_world, point_y_in_world;

    if(!unit_world_transformer_.transPointToWorld(
          point_x_in_image, point_y_in_image,
          point_x_in_world, point_y_in_world))
    {
        std::cout << "UnitWorldEnvironment::setWallRoomPositionByPosition :\n" <<
          "Input :\n" <<
          "\t wall_room_idx = " << wall_room_idx << std::endl <<
          "\t point_in_image = [" << point_x_in_image << "," <<
          point_y_in_image << "]\n" <<
          "transPointToWorld failed!\n";

        return false;
    }

    const EasyNodeInfo& wall_room_info = wall_room_info_vec_[wall_room_idx];

    EasyPoint2D point_in_world;
    point_in_world.setPosition(point_x_in_world, point_y_in_world);

    if(!unit_world_controller_.setRoomPositionOnTreeByPosition(
          wall_room_info.id, wall_room_info.type, point_in_world))
    {
        std::cout << "UnitWorldEnvironment::setWallRoomPositionByPosition :\n" <<
          "Input :\n" <<
          "\t wall_room_idx = " << wall_room_idx << std::endl <<
          "\t point_in_image = [" << point_x_in_image << "," <<
          point_y_in_image << "]\n" <<
          "setRoomPositionOnTreeByPosition failed!\n";

        return false;
    }

    if(!unit_world_controller_.unit_tree.updateNodePolygon(
          wall_room_info.id, wall_room_info.type))
    {
        std::cout << "UnitWorldEnvironment::setWallRoomPositionByPosition :\n" <<
          "Input :\n" <<
          "\t wall_room_idx = " << wall_room_idx << std::endl <<
          "\t point_in_image = [" << point_x_in_image << "," <<
          point_y_in_image << "]\n" <<
          "updateNodePolygon failed!\n";

        return false;
    }

    return true;
}

std::vector<std::vector<std::vector<size_t>>> UnitWorldEnvironment::getNodeBoundaryDataVec(
    const std::vector<EasyNodeInfo>& node_info_vec)
{
    std::vector<std::vector<std::vector<size_t>>> node_boundary_data_vec;

    node_boundary_data_vec.resize(node_info_vec.size());

    for(size_t i = 0; i < node_info_vec.size(); ++i)
    {
        const EasyNodeInfo& node_info = node_info_vec[i];

        UnitNode* search_node = unit_world_controller_.unit_tree.findNode(
            node_info.id, node_info.type);

        if(search_node == nullptr)
        {
            std::cout << "UnitWorldEnvironment::getNodeBoundaryDataVec :\n" <<
              "find node failed!\n";

            continue;
        }

        const EasyPolygon2D& node_boundary_polygon = search_node->boundary_polygon;

        std::vector<std::vector<size_t>>& node_boundary_data = node_boundary_data_vec[i];
        node_boundary_data.resize(node_boundary_polygon.point_list.size());

        for(size_t j = 0; j < node_boundary_polygon.point_list.size(); ++j)
        {
            std::vector<size_t>& node_boundary_point_data = node_boundary_data[j];

            node_boundary_point_data.resize(2);

            const EasyPoint2D& node_boundary_point = node_boundary_polygon.point_list[j];

            size_t node_boundary_point_x_in_image, node_boundary_point_y_in_image;

            if(!unit_world_transformer_.transPointToImage(
                  node_boundary_point.x, node_boundary_point.y,
                  node_boundary_point_x_in_image, node_boundary_point_y_in_image))
            {
                std::cout << "UnitWorldEnvironment::getNodeBoundaryDataVec :\n" <<
                  "transPointToImage failed!\n";

                continue;
            }

            node_boundary_point_data[0] = node_boundary_point_x_in_image;
            node_boundary_point_data[1] = node_boundary_point_y_in_image;
        }

    }

    return node_boundary_data_vec;
}

std::vector<std::vector<std::vector<size_t>>> UnitWorldEnvironment::getOuterWallBoundaryDataVec()
{
    return getNodeBoundaryDataVec(outer_wall_info_vec_);
}

std::vector<std::vector<std::vector<size_t>>> UnitWorldEnvironment::getInnerWallBoundaryDataVec()
{
    return getNodeBoundaryDataVec(inner_wall_info_vec_);
}

std::vector<std::vector<std::vector<size_t>>> UnitWorldEnvironment::getWallRoomBoundaryDataVec()
{
    return getNodeBoundaryDataVec(wall_room_info_vec_);
}

