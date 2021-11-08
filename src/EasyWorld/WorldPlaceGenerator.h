#ifndef WORLD_PLACE_GENERATOR
#define WORLD_PLACE_GENERATOR

#include "WorldController.h"
#include "BoundaryLineManager.h"
#include "PointMatrix.h"

class WorldPlaceGenerator
{
public:
    WorldPlaceGenerator()
    {
        free_room_error_max_ = 1;

        team_x_direction_person_num_ = 2 * (std::rand() % 3 + 1);
        team_y_direction_person_num_ = 2 * (std::rand() % 3 + 1);
        team_dist_ = 0.5;
        person_edge_ = 2.0;
    }

    bool reset();

    bool resetButRemainWall(
        WorldController &world_controller);

    bool createNewWorld(
        WorldController &world_controller,
        const float &world_center_x,
        const float &world_center_y);

    bool generateWall(
        WorldController &world_controller,
        const std::string &wall_name,
        const NodeType &wall_type,
        const EasyPolygon2D &wall_polygon);

    bool generateOuterWall(
        WorldController &world_controller,
        const std::string &wall_name,
        const EasyPolygon2D &wall_polygon);

    bool generateInnerWall(
        WorldController &world_controller,
        const std::string &wall_name,
        const EasyPolygon2D &wall_polygon);

    bool generateWorld(
        WorldController &world_controller);

    bool placeWallRoomContainer(
        WorldController &world_controller,
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &boundary_idx,
        const float &roomcontainer_start_position,
        const float &roomcontainer_width,
        const float &roomcontainer_height,
        const size_t &room_num,
        const std::vector<std::string> &room_name_vec);

    bool placeWallRoomContainer(
        WorldController &world_controller,
        const size_t &wall_id,
        const NodeType &wall_type,
        const size_t &boundary_idx,
        const float &roomcontainer_start_position,
        const float &roomcontainer_width,
        const float &roomcontainer_height);

    bool generateFreeRoomContainer(
        WorldController &world_controller,
        const size_t &team_x_direction_person_num,
        const size_t &team_y_direction_person_num,
        const float &team_dist,
        const float &person_edge);

private:
    bool generateRoom(
        WorldController &world_controller);

public:
    BoundaryLineManager boundary_line_manager_;
    PointMatrix point_matrix_;

    float free_room_error_max_;

    size_t current_new_innerwall_id_;
    size_t current_new_outerwall_id_;
    size_t current_new_room_id_;

    bool is_outerwall_boundary_polygon_set_;
    EasyPolygon2D outerwall_boundary_polygon_;

    size_t team_x_direction_person_num_;
    size_t team_y_direction_person_num_;
    float team_dist_;
    float person_edge_;
};

#endif //WORLD_PLACE_GENERATOR
