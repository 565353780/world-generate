#include "WorldGenerator.h"

SplitNode::~SplitNode()
{
    reset();
}

bool SplitNode::reset()
{
    if(first_child != nullptr)
    {
        first_child->reset();
        delete(first_child);
        first_child = nullptr;
    }

    if(second_child != nullptr)
    {
        second_child->reset();
        delete(second_child);
        second_child = nullptr;
    }

    return true;
}

bool SplitNode::createChild(
    const bool &is_x_direction_split,
    const float &split_percent,
    const float &child_node_length_min)
{
    if(split_percent <= 0 || split_percent >= 1)
    {
        std::cout << "SplitNode::createChild : " << std::endl <<
          "Input :\n" <<
          "\tis_x_direction_split = " << is_x_direction_split << std::endl <<
          "\tsplit_percent = " << split_percent << std::endl <<
          "\tchild_node_length_min = " << child_node_length_min << std::endl <<
          "split percent not valid!" << std::endl;

        return false;
    }

    if(first_child != nullptr)
    {
        std::cout << "SplitNode::createChild : " << std::endl <<
          "Input :\n" <<
          "\tis_x_direction_split = " << is_x_direction_split << std::endl <<
          "\tsplit_percent = " << split_percent << std::endl <<
          "\tchild_node_length_min = " << child_node_length_min << std::endl <<
          "first child is already exist!" << std::endl;

        return false;
    }

    if(second_child != nullptr)
    {
        std::cout << "SplitNode::createChild : " << std::endl <<
          "Input :\n" <<
          "\tis_x_direction_split = " << is_x_direction_split << std::endl <<
          "\tsplit_percent = " << split_percent << std::endl <<
          "\tchild_node_length_min = " << child_node_length_min << std::endl <<
          "second child is already exist!" << std::endl;

        return false;
    }

    SplitNode* new_first_child = new SplitNode();
    new_first_child->parent = this;
    new_first_child->start_position = start_position;

    SplitNode* new_second_child = new SplitNode();
    new_second_child->parent = this;
    new_second_child->end_position = end_position;

    if(is_x_direction_split)
    {
        float valid_split_percent_min = 1.0 * child_node_length_min / (end_position.x - start_position.x);
        float valid_split_percent_max = 1.0 - valid_split_percent_min;
        float new_split_percent = split_percent;

        if(new_split_percent < valid_split_percent_min)
        {
            new_split_percent = valid_split_percent_min;
        }
        if(new_split_percent > valid_split_percent_max)
        {
            new_split_percent = valid_split_percent_max;
        }
        if(new_split_percent < valid_split_percent_min)
        {
            // std::cout << "SplitNode::createChild : " << std::endl <<
            //   "Input :\n" <<
            //   "\tis_x_direction_split = " << is_x_direction_split << std::endl <<
            //   "\tsplit_percent = " << split_percent << std::endl <<
            //   "\tchild_node_length_min = " << child_node_length_min << std::endl <<
            //   "can not keep child noe length min valid!" << std::endl;

            new_first_child->reset();
            delete(new_first_child);
            new_second_child->reset();
            delete(new_second_child);
            return false;
        }

        float valid_split_x_position =
          new_split_percent * start_position.x + (1.0 - new_split_percent) * end_position.x;

        new_first_child->end_position.setPosition(valid_split_x_position, end_position.y);

        new_second_child->start_position.setPosition(valid_split_x_position, start_position.y);
    }
    else
    {
        float valid_split_percent_min = 1.0 * child_node_length_min / (end_position.y - start_position.y);
        float valid_split_percent_max = 1.0 - valid_split_percent_min;
        float new_split_percent = split_percent;

        if(new_split_percent < valid_split_percent_min)
        {
            new_split_percent = valid_split_percent_min;
        }
        if(new_split_percent > valid_split_percent_max)
        {
            new_split_percent = valid_split_percent_max;
        }
        if(new_split_percent < valid_split_percent_min)
        {
            // std::cout << "SplitNode::createChild : " << std::endl <<
            //   "Input :\n" <<
            //   "\tis_x_direction_split = " << is_x_direction_split << std::endl <<
            //   "\tsplit_percent = " << split_percent << std::endl <<
            //   "\tchild_node_length_min = " << child_node_length_min << std::endl <<
            //   "can not keep child noe length min valid!" << std::endl;

            new_first_child->reset();
            delete(new_first_child);
            new_second_child->reset();
            delete(new_second_child);
            return false;
        }

        float valid_split_y_position =
          new_split_percent * start_position.y + (1.0 - new_split_percent) * end_position.y;

        new_first_child->end_position.setPosition(end_position.x, valid_split_y_position);

        new_second_child->start_position.setPosition(start_position.x, valid_split_y_position);
    }

    first_child = new_first_child;
    second_child = new_second_child;

    return true;
}

SplitNode* SplitNode::getRandomLeafNode()
{
    if(first_child == nullptr && second_child == nullptr)
    {
        return this;
    }

    if(first_child == nullptr || second_child == nullptr)
    {
        std::cout << "SplitNode::getRandomLeafNode : " << std::endl <<
          "this node only have one child!" << std::endl;

        return nullptr;
    }

    const size_t random_child_idx = std::rand() % 2;

    if(random_child_idx == 0)
    {
        if(first_child != nullptr)
        {
            return first_child->getRandomLeafNode();
        }

        std::cout << "SplitNode::getRandomLeafNode : " << std::endl <<
          "the first child is nullptr!" << std::endl;

        return this;
    }

    if(second_child != nullptr)
    {
        return second_child->getRandomLeafNode();
    }

    std::cout << "SplitNode::getRandomLeafNode : " << std::endl <<
      "the second child is nullptr!" << std::endl;

    return this;
}

bool SplitNode::getAllLeafNode(
    std::vector<SplitNode*> &leaf_node_vec)
{
    if(first_child == nullptr && second_child == nullptr)
    {
        leaf_node_vec.emplace_back(this);

        return true;
    }

    if(first_child != nullptr)
    {
        first_child->getAllLeafNode(leaf_node_vec);
    }

    if(second_child != nullptr)
    {
        second_child->getAllLeafNode(leaf_node_vec);
    }

    return true;
}

WorldGenerator::~WorldGenerator()
{
    split_room_tree_->reset();

    delete(split_room_tree_);
}

bool WorldGenerator::reset()
{
    if(!world_controller_.reset())
    {
        std::cout << "WorldGenerator::reset : " <<
          "reset for world_controller_ failed!" << std::endl;

        return false;
    }

    wall_boundary_polygon_.point_list.clear();
    wall_boundary_length_vec_.clear();
    split_room_tree_->reset();
    is_wall_boundary_polygon_set_ = false;

    person_num_ = 0;
    is_person_num_set_ = false;

    return true;
}

bool WorldGenerator::setWallBoundaryPolygon(
    const EasyPolygon2D &wall_boundary_polygon)
{
    wall_boundary_polygon_.point_list.clear();
    wall_boundary_length_vec_.clear();
    split_room_tree_->reset();

    is_wall_boundary_polygon_set_ = false;

    if(wall_boundary_polygon.point_list.size() == 0)
    {
        std::cout << "WorldGenerator::setArea : " << std::endl <<
          "wall boundary polygon is empty!" << std::endl;

        return false;
    }

    wall_boundary_polygon_ = wall_boundary_polygon;

    wall_boundary_length_vec_.resize(wall_boundary_polygon_.point_list.size(), -1);

    for(size_t i = 0; i < wall_boundary_polygon_.point_list.size(); ++i)
    {
        const EasyPoint2D &current_point = wall_boundary_polygon_.point_list[i];
        const EasyPoint2D &next_point = wall_boundary_polygon_.point_list[
          (i + 1) % wall_boundary_polygon_.point_list.size()];

        const float wall_boundary_length = EasyComputation::pointDist(current_point, next_point);

        wall_boundary_length_vec_[i] = wall_boundary_length;
    }

    is_wall_boundary_polygon_set_ = true;

    split_room_tree_->start_position.setPosition(0, 0);
    split_room_tree_->end_position = wall_boundary_polygon_.point_list[2];

    return true;
}

bool WorldGenerator::setPersonNum(
    const size_t &person_num)
{
    person_num_ = 0;
    is_person_num_set_ = false;

    if(person_num == 0)
    {
        std::cout << "WorldGenerator::setPersonNum : " << std::endl <<
          "Input :\n" <<
          "\tperson_num = " << person_num << std::endl <<
          "perosn num not valid!" << std::endl;

        return false;
    }

    person_num_ = person_num;
    is_person_num_set_ = true;

    return true;
}

bool WorldGenerator::setRoomNum(
    const size_t &room_num)
{
    room_num_ = 0;
    is_room_num_set_ = false;

    if(room_num == 0)
    {
        std::cout << "WorldGenerator::setPersonNum : " << std::endl <<
          "Input :\n" <<
          "\troom_num = " << room_num << std::endl <<
          "perosn num not valid!" << std::endl;

        return false;
    }

    room_num_ = room_num;
    is_room_num_set_ = true;

    return true;
}

bool WorldGenerator::generateWorld()
{
    if(!isReadyToGenerate())
    {
        if(!is_wall_boundary_polygon_set_)
        {
            std::cout << "WorldGenerator::generateWorld : " << std::endl <<
              "wall_boundary_polygon not set!" << std::endl;

            return false;
        }
        
        if(!is_person_num_set_)
        {
            std::cout << "WorldGenerator::generateWorld : " << std::endl <<
              "person_num not set!" << std::endl;

            return false;
        }

        std::cout << "WorldGenerator::generateWorld : " << std::endl <<
          "room_num not set!" << std::endl;

        return false;
    }

    if(!world_controller_.reset())
    {
        std::cout << "WorldGenerator::generateWorld : " << std::endl <<
          "reset for world_controller_ failed!" << std::endl;

        return false;
    }

    if(!generateWall())
    {
        std::cout << "WorldGenerator::generateWorld : " << std::endl <<
          "generateWall failed!" << std::endl;

        return false;
    }

    if(!splitWallSpace())
    {
        std::cout << "WorldGenerator::generateWorld : " << std::endl <<
          "splitWallSpace failed!" << std::endl;

        return false;
    }

    if(!generateRoom())
    {
        std::cout << "WorldGenerator::generateWorld : " << std::endl <<
          "generateWallRoom failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldGenerator::isReadyToGenerate()
{
    if(is_wall_boundary_polygon_set_ &&
        is_person_num_set_ &&
        is_room_num_set_)
    {
        return true;
    }

    return false;
}

bool WorldGenerator::generateWall()
{
    if(!world_controller_.createWorld(1, 1))
    {
        std::cout << "WorldGenerator::generateWall : " << std::endl <<
          "createWorld failed!" << std::endl;

        return false;
    }

    if(!world_controller_.createWall(0, NodeType::OuterWall))
    {
        std::cout << "WorldGenerator::generateWall : " << std::endl <<
          "createWall failed!" << std::endl;

        return false;
    }

    if(!world_controller_.setWallBoundaryPolygon(0, NodeType::OuterWall, wall_boundary_polygon_))
    {
        std::cout << "WorldGenerator::generateWall : " << std::endl <<
          "setWallBoundaryPolygon failed!" << std::endl;

        return false;
    }

    return true;
}

bool WorldGenerator::splitWallSpace()
{
    const size_t wall_room_edge_max = 8;

    const size_t split_time = room_num_;

    for(size_t i = 0; i < split_time; ++i)
    {
        SplitNode* random_child_node = split_room_tree_->getRandomLeafNode();
        bool is_x_direction_split = (std::rand() % 2) == 1;
        float random_split_percent = 1.0 * (std::rand() % 100) / 100.0;

        const size_t try_time = 100;
        size_t current_try_time = 0;
        while(!random_child_node->createChild(is_x_direction_split, random_split_percent, wall_room_edge_max))
        {
            ++current_try_time;
            random_child_node = split_room_tree_->getRandomLeafNode();
            is_x_direction_split = (std::rand() % 2) == 1;
            random_split_percent = 1.0 * (std::rand() % 100) / 100.0;
            if(current_try_time > try_time)
            {
                // std::cout << "WorldGenerator::splitWallSpace : " << std::endl <<
                //   "createChild for random leaf node failed!" << std::endl;

                break;
            }
        }
    }

    return true;
}

bool WorldGenerator::generateRoom()
{
    const float person_edge = 2;
    const size_t room_edge_min = 4;

    std::vector<SplitNode*> leaf_node_vec;

    split_room_tree_->getAllLeafNode(leaf_node_vec);
    std::cout << "leaf_node_vec.size() = " << leaf_node_vec.size() << std::endl;

    size_t current_wallroom_idx = 0;
    size_t current_freeroom_idx = 0;

    for(SplitNode* leaf_node : leaf_node_vec)
    {
        const bool is_use_this_node = (std::rand() % 2) == 1;
        if(!is_use_this_node)
        {
            continue;
        }

        const EasyPoint2D &roomcontainer_start_position = leaf_node->start_position;
        const EasyPoint2D &roomcontainer_end_position = leaf_node->end_position;

        const float roomcontainer_width = roomcontainer_end_position.x - roomcontainer_start_position.x;
        const float roomcontainer_height = roomcontainer_end_position.y - roomcontainer_start_position.y;

        const size_t x_direction_wall_room_num = size_t(roomcontainer_width / room_edge_min);
        const float room_real_width = roomcontainer_width / x_direction_wall_room_num;

        const bool is_room_on_wall =
          roomcontainer_start_position.x == 0 || roomcontainer_start_position.y == 0 ||
          roomcontainer_end_position.x == wall_boundary_length_vec_[0] ||
          roomcontainer_end_position.y == wall_boundary_length_vec_[1];

        EasyAxis2D room_axis;
        room_axis.setXDirection(1, 0);
        room_axis.setCenter(roomcontainer_start_position.x, roomcontainer_start_position.y);
        EasyAxis2D team_axis;
        team_axis.setXDirection(1, 0);

        const bool is_this_wall_room = (std::rand() % 2) == 1;
        if(is_room_on_wall && is_this_wall_room)
        {
            if(!world_controller_.createWallRoomContainerForWall(
                  0,
                  NodeType::OuterWall,
                  0,
                  roomcontainer_width,
                  roomcontainer_height,
                  room_axis,
                  x_direction_wall_room_num))
            {
                std::cout << "WorldGenerator::splitWallSpace : " << std::endl <<
                  "createWallRoomContainerForWall for leaf node failed!" << std::endl;

                return false;
            }

            for(size_t j = 0; j < x_direction_wall_room_num; ++j)
            {
                const size_t current_new_wallroom_idx = current_wallroom_idx + j;
                const size_t current_random_person_x_direction_num = std::rand() % 3;
                const size_t current_random_person_y_direction_num = std::rand() % 3;
                const bool is_face_horizontal = (std::rand() % 2) == 1;

                if(current_random_person_x_direction_num == 0 ||
                    current_random_person_y_direction_num == 0)
                {
                    continue;
                }

                team_axis.setCenter(
                    (room_real_width - current_random_person_x_direction_num * person_edge) / 2.0,
                    (roomcontainer_height - current_random_person_x_direction_num * person_edge) / 2.0);

                if(!world_controller_.createTeamForRoom(
                      current_new_wallroom_idx,
                      NodeType::WallRoom,
                      current_random_person_x_direction_num * person_edge,
                      current_random_person_y_direction_num * person_edge,
                      team_axis,
                      current_random_person_x_direction_num,
                      current_random_person_y_direction_num,
                      is_face_horizontal))
                {
                    std::cout << "WorldGenerator::splitWallSpace : " << std::endl <<
                      "createTeamForRoom for leaf node failed!" << std::endl;

                    return false;
                }
            }

            current_wallroom_idx += x_direction_wall_room_num;
        }
        else
        {
            if(!world_controller_.createFreeRoomContainerForWall(
                  0,
                  NodeType::OuterWall,
                  0,
                  roomcontainer_width,
                  roomcontainer_height,
                  room_axis,
                  1))
            {
                std::cout << "WorldGenerator::splitWallSpace : " << std::endl <<
                  "createFreeRoomContainerForWall for leaf node failed!" << std::endl;

                return false;
            }

            const size_t current_person_x_direction_num = size_t(roomcontainer_width / person_edge) - 2;
            const size_t current_person_y_direction_num = size_t(roomcontainer_height / person_edge) - 2;
            const bool is_face_horizontal = (std::rand() % 2) == 1;

            team_axis.setCenter(2, 2);

            if(!world_controller_.createTeamForRoom(
                  current_freeroom_idx,
                  NodeType::FreeRoom,
                  roomcontainer_width - 4,
                  roomcontainer_height - 4,
                  team_axis,
                  current_person_x_direction_num,
                  current_person_y_direction_num,
                  is_face_horizontal))
            {
                std::cout << "WorldGenerator::splitWallSpace : " << std::endl <<
                  "createTeamForRoom for leaf node failed!" << std::endl;

                return false;
            }

            ++current_freeroom_idx;
        }
    }

    return true;
}

