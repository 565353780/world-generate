#ifndef WORLD_SPLIT_GENERATOR_H
#define WORLD_SPLIT_GENERATOR_H

#include <iostream>
#include <string>

#include "WorldController.h"

class SplitNode
{
public:
    SplitNode()
    {
        parent = nullptr;
        first_child = nullptr;
        second_child = nullptr;
    }
    ~SplitNode();

    bool reset();

    bool createChild(
        const bool &is_x_direction_split,
        const float &split_percent,
        const float &child_node_length_min);

    SplitNode* getRandomLeafNode();

    bool getAllLeafNode(
        std::vector<SplitNode*> &leaf_node_vec);

    SplitNode* parent;
    SplitNode* first_child;
    SplitNode* second_child;
    EasyPoint2D start_position;
    EasyPoint2D end_position;
};

class WorldSplitGenerator
{
public:
    WorldSplitGenerator()
    {
        is_wall_boundary_polygon_set_ = false;
        is_person_num_set_ = false;
        is_room_num_set_ = false;

        split_room_tree_ = new SplitNode();
    }
    ~WorldSplitGenerator();

    bool reset();

    bool setWallBoundaryPolygon(
        const EasyPolygon2D &wall_boundary_polygon);
    
    bool setPersonNum(
        const size_t &person_num);

    bool setRoomNum(
        const size_t &room_num);

    bool generateWorld();

private:
    bool isReadyToGenerate();

    bool generateWall();
    bool splitWallSpace();
    bool generateRoom();

public:
    WorldController world_controller_;

    bool is_wall_boundary_polygon_set_;
    EasyPolygon2D wall_boundary_polygon_;
    std::vector<float> wall_boundary_length_vec_;
    SplitNode* split_room_tree_;

    bool is_person_num_set_;
    size_t person_num_;

    bool is_room_num_set_;
    size_t room_num_;
};

#endif //WORLD_SPLIT_GENERATOR_H
