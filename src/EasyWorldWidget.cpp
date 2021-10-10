#include "EasyWorldWidget.h"
#include "qglobal.h"
#include "ui_EasyWorldWidget.h"

EasyWorldWidget::EasyWorldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EasyWorldWidget)
{
    ui->setupUi(this);

    axis_length_ = 10;

    run_example();
    
    this->show();
}

EasyWorldWidget::~EasyWorldWidget()
{
    delete ui;

    world_controller_.reset();
}

void EasyWorldWidget::run_example()
{
    createWorld();
    createWall();
    createRoom();
    createTeam();
    createPerson();

    // world_controller_.outputInfo();

    std::cout << "finish run_example!" << std::endl;
}

void EasyWorldWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    drawWallSpaceBoundary();
    drawRoomSpaceBoundary();
    drawTeamSpaceBoundary();
    // drawPersonSpaceBoundary();
    drawFurnitureSpaceBoundary();

    // drawWallBoundaryAxis();
    // drawRoomBoundaryAxis();
    // drawTeamBoundaryAxis();
    // drawPersonBoundaryAxis();
    // drawFurnitureBoundaryAxis();
}

void EasyWorldWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void EasyWorldWidget::mouseMoveEvent(QMouseEvent *event)
{
    // moveWallInWorld(0, NodeType::OuterWall, event);

    // moveRoomInWorld(0, NodeType::WallRoom, event);

    moveTeamInWorld(0, NodeType::Team, event);
}

void EasyWorldWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

bool EasyWorldWidget::createWorld()
{
    world_controller_.reset();

    world_controller_.createWorld(400, 400);

    return true;
}

bool EasyWorldWidget::createWall()
{
    world_controller_.createWall(0, NodeType::OuterWall);

    EasyPolygon2D wall_boundary_polygon;
    wall_boundary_polygon.point_list.resize(4);
    wall_boundary_polygon.point_list[0].setPosition(0, 0);
    wall_boundary_polygon.point_list[1].setPosition(300, 0);
    wall_boundary_polygon.point_list[2].setPosition(300, 300);
    wall_boundary_polygon.point_list[3].setPosition(0, 300);
    wall_boundary_polygon.setAntiClockWise();

    world_controller_.setWallBoundaryPolygon(0, NodeType::OuterWall, wall_boundary_polygon);

    return true;
}

bool EasyWorldWidget::createRoom()
{
    world_controller_.createRoom(0, NodeType::FreeRoom, 0, NodeType::OuterWall, 0);
    world_controller_.createRoom(0, NodeType::WallRoom, 0, NodeType::OuterWall, 0);
    world_controller_.createRoom(1, NodeType::WallRoom, 0, NodeType::OuterWall, 0);
    world_controller_.createRoom(2, NodeType::WallRoom, 0, NodeType::OuterWall, 0);
    world_controller_.createRoom(3, NodeType::WallRoom, 0, NodeType::OuterWall, 2);
    world_controller_.createRoom(4, NodeType::WallRoom, 0, NodeType::OuterWall, 2);

    EasyPolygon2D room_boundary_polygon;
    room_boundary_polygon.point_list.resize(4);
    room_boundary_polygon.point_list[0].setPosition(0, 0);
    room_boundary_polygon.point_list[1].setPosition(280, 0);
    room_boundary_polygon.point_list[2].setPosition(280, 80);
    room_boundary_polygon.point_list[3].setPosition(0, 80);
    room_boundary_polygon.setAntiClockWise();

    world_controller_.setRoomBoundaryPolygon(0, NodeType::FreeRoom, room_boundary_polygon);

    room_boundary_polygon.point_list[0].setPosition(0, 0);
    room_boundary_polygon.point_list[1].setPosition(100, 0);
    room_boundary_polygon.point_list[2].setPosition(100, 100);
    room_boundary_polygon.point_list[3].setPosition(0, 100);
    room_boundary_polygon.setAntiClockWise();

    world_controller_.setRoomBoundaryPolygon(0, NodeType::WallRoom, room_boundary_polygon);
    world_controller_.setRoomBoundaryPolygon(1, NodeType::WallRoom, room_boundary_polygon);
    world_controller_.setRoomBoundaryPolygon(2, NodeType::WallRoom, room_boundary_polygon);
    world_controller_.setRoomBoundaryPolygon(3, NodeType::WallRoom, room_boundary_polygon);
    world_controller_.setRoomBoundaryPolygon(4, NodeType::WallRoom, room_boundary_polygon);

    EasyPoint2D room_axis_center_position_in_parent;

    room_axis_center_position_in_parent.setPosition(10, 110);
    world_controller_.setRoomAxisCenterPositionInParent(0, NodeType::FreeRoom, room_axis_center_position_in_parent);

    room_axis_center_position_in_parent.setPosition(100, 0);
    world_controller_.setRoomAxisCenterPositionInParent(1, NodeType::WallRoom, room_axis_center_position_in_parent);

    room_axis_center_position_in_parent.setPosition(200, 0);
    world_controller_.setRoomAxisCenterPositionInParent(2, NodeType::WallRoom, room_axis_center_position_in_parent);
    world_controller_.setRoomAxisCenterPositionInParent(4, NodeType::WallRoom, room_axis_center_position_in_parent);

    return true;
}

bool EasyWorldWidget::createTeam()
{
    world_controller_.createTeam(0, NodeType::Team, 0, NodeType::WallRoom);
    world_controller_.createTeam(1, NodeType::Team, 1, NodeType::WallRoom);
    world_controller_.createTeam(2, NodeType::Team, 2, NodeType::WallRoom);
    world_controller_.createTeam(3, NodeType::Team, 3, NodeType::WallRoom);
    world_controller_.createTeam(4, NodeType::Team, 4, NodeType::WallRoom);

    world_controller_.createTeam(5, NodeType::Team, 0, NodeType::FreeRoom);
    world_controller_.createTeam(6, NodeType::Team, 0, NodeType::FreeRoom);
    world_controller_.createTeam(7, NodeType::Team, 0, NodeType::FreeRoom);

    EasyPolygon2D team_boundary_polygon;
    team_boundary_polygon.point_list.resize(4);
    team_boundary_polygon.point_list[0].setPosition(0, 0);
    team_boundary_polygon.point_list[1].setPosition(50, 0);
    team_boundary_polygon.point_list[2].setPosition(50, 50);
    team_boundary_polygon.point_list[3].setPosition(0, 50);
    team_boundary_polygon.setAntiClockWise();

    world_controller_.setTeamBoundaryPolygon(0, NodeType::Team, team_boundary_polygon);
    world_controller_.setTeamBoundaryPolygon(1, NodeType::Team, team_boundary_polygon);
    world_controller_.setTeamBoundaryPolygon(2, NodeType::Team, team_boundary_polygon);
    world_controller_.setTeamBoundaryPolygon(3, NodeType::Team, team_boundary_polygon);
    world_controller_.setTeamBoundaryPolygon(4, NodeType::Team, team_boundary_polygon);

    team_boundary_polygon.point_list[0].setPosition(0, 0);
    team_boundary_polygon.point_list[1].setPosition(80, 0);
    team_boundary_polygon.point_list[2].setPosition(80, 60);
    team_boundary_polygon.point_list[3].setPosition(0, 60);
    team_boundary_polygon.setAntiClockWise();

    world_controller_.setTeamBoundaryPolygon(5, NodeType::Team, team_boundary_polygon);
    world_controller_.setTeamBoundaryPolygon(6, NodeType::Team, team_boundary_polygon);
    world_controller_.setTeamBoundaryPolygon(7, NodeType::Team, team_boundary_polygon);

    EasyPoint2D team_axis_center_position_in_parent;
    team_axis_center_position_in_parent.setPosition(25, 25);

    world_controller_.setTeamAxisCenterPositionInParent(0, NodeType::Team, team_axis_center_position_in_parent);
    world_controller_.setTeamAxisCenterPositionInParent(1, NodeType::Team, team_axis_center_position_in_parent);
    world_controller_.setTeamAxisCenterPositionInParent(2, NodeType::Team, team_axis_center_position_in_parent);
    world_controller_.setTeamAxisCenterPositionInParent(3, NodeType::Team, team_axis_center_position_in_parent);
    world_controller_.setTeamAxisCenterPositionInParent(4, NodeType::Team, team_axis_center_position_in_parent);

    team_axis_center_position_in_parent.setPosition(190, 10);
    world_controller_.setTeamAxisCenterPositionInParent(7, NodeType::Team, team_axis_center_position_in_parent);
    team_axis_center_position_in_parent.setPosition(100, 10);
    world_controller_.setTeamAxisCenterPositionInParent(6, NodeType::Team, team_axis_center_position_in_parent);
    team_axis_center_position_in_parent.setPosition(10, 10);
    world_controller_.setTeamAxisCenterPositionInParent(5, NodeType::Team, team_axis_center_position_in_parent);

    return true;
}

bool EasyWorldWidget::createPerson()
{
    EasyAxis2D person_axis_in_parent;

    const float person_width = 50;
    const float person_height = 50;

    person_axis_in_parent.center_.setPosition(0, 0);
    person_axis_in_parent.x_direction_.setPosition(1, 0);

    world_controller_.createPersonForTeam(0, NodeType::Team, person_width, person_height, person_axis_in_parent);
    world_controller_.createPersonForTeam(1, NodeType::Team, person_width, person_height, person_axis_in_parent);
    world_controller_.createPersonForTeam(2, NodeType::Team, person_width, person_height, person_axis_in_parent);
    world_controller_.createPersonForTeam(3, NodeType::Team, person_width, person_height, person_axis_in_parent);
    world_controller_.createPersonForTeam(4, NodeType::Team, person_width, person_height, person_axis_in_parent);

    const bool is_face_horizontal = true;

    world_controller_.createPersonGroupForTeam(5, NodeType::Team, 4, 4, is_face_horizontal);
    world_controller_.createPersonGroupForTeam(6, NodeType::Team, 4, 4, is_face_horizontal);
    world_controller_.createPersonGroupForTeam(7, NodeType::Team, 4, 4, is_face_horizontal);

    return true;
}

bool EasyWorldWidget::moveWallInWorld(
    const size_t &wall_id,
    const NodeType &wall_type,
    QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        const QPoint &mouse_pos = event->pos();

        EasyPoint2D new_wall_pos;

        new_wall_pos.setPosition(mouse_pos.x(), mouse_pos.y());

        world_controller_.setWallAxisCenterPositionInWorld(
            wall_id, wall_type, new_wall_pos);

        update();
    }

    return true;
}

bool EasyWorldWidget::moveRoomInWorld(
    const size_t &room_id,
    const NodeType &room_type,
    QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        const QPoint &mouse_pos = event->pos();

        EasyPoint2D new_room_pos;

        new_room_pos.setPosition(mouse_pos.x(), mouse_pos.y());

        world_controller_.setRoomAxisCenterPositionInWorld(
            room_id, room_type, new_room_pos);

        update();
    }

    return true;
}

bool EasyWorldWidget::moveTeamInWorld(
    const size_t &team_id,
    const NodeType &team_type,
    QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        const QPoint &mouse_pos = event->pos();

        EasyPoint2D new_room_pos;

        new_room_pos.setPosition(mouse_pos.x(), mouse_pos.y());

        world_controller_.setTeamAxisCenterPositionInWorld(
            team_id, team_type, new_room_pos);

        update();
    }

    return true;
}

bool EasyWorldWidget::movePersonInWorld(
    const size_t &person_id,
    const NodeType &person_type,
    QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        const QPoint &mouse_pos = event->pos();

        EasyPoint2D new_room_pos;

        new_room_pos.setPosition(mouse_pos.x(), mouse_pos.y());

        world_controller_.setPersonAxisCenterPositionInWorld(
            person_id, person_type, new_room_pos);

        update();
    }

    return true;
}

bool EasyWorldWidget::moveFurnitureInWorld(
    const size_t &furniture_id,
    const NodeType &furniture_type,
    QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        const QPoint &mouse_pos = event->pos();

        EasyPoint2D new_room_pos;

        new_room_pos.setPosition(mouse_pos.x(), mouse_pos.y());

        world_controller_.setFurnitureAxisCenterPositionInWorld(
            furniture_id, furniture_type, new_room_pos);

        update();
    }

    return true;
}

bool EasyWorldWidget::drawWallBoundaryAxis()
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> wall_boundary_node_vec_vec;

    world_controller_.getWallBoundaryNodeVecVec(wall_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& wall_boundary_node_vec: wall_boundary_node_vec_vec)
    {
        for(const EasyNode* wall_boundary_node : wall_boundary_node_vec)
        {
            if(wall_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D wall_boundary_axis = wall_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                wall_boundary_axis.center_.x, wall_boundary_axis.center_.y,
                wall_boundary_axis.center_.x + axis_length_ * wall_boundary_axis.x_direction_.x,
                wall_boundary_axis.center_.y + axis_length_ * wall_boundary_axis.x_direction_.y);

            painter.setPen(pen_green);

            painter.drawLine(
                wall_boundary_axis.center_.x, wall_boundary_axis.center_.y,
                wall_boundary_axis.center_.x + axis_length_ * wall_boundary_axis.y_direction_.x,
                wall_boundary_axis.center_.y + axis_length_ * wall_boundary_axis.y_direction_.y);
        }
        
    }
    
    return true;
}

bool EasyWorldWidget::drawWallBoundaryPolygon()
{
    QPainter painter(this);

    QPen pen_black(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen_black);

    std::vector<std::vector<EasyNode*>> wall_boundary_node_vec_vec;

    world_controller_.getWallBoundaryNodeVecVec(wall_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &wall_boundary_node_vec :
        wall_boundary_node_vec_vec)
    {
        for(EasyNode* wall_boundary_node : wall_boundary_node_vec)
        {
            const EasyPolygon2D &wall_boundary_polygon =
              wall_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < wall_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point = wall_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point = wall_boundary_polygon.point_list[
                  (i + 1) % wall_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                wall_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                wall_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

            painter.drawLine(
                current_point_in_world.x, current_point_in_world.y,
                next_point_in_world.x, next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawWallSpaceBoundary()
{
    QPainter painter(this);

    QPen pen_black(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen_black);

    std::vector<EasyNode*> wall_space_node_vec;

    world_controller_.getWallSpaceNodeVec(wall_space_node_vec);

    for(EasyNode* wall_space_node : wall_space_node_vec)
    {
        if(wall_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &wall_space_polygon =
          wall_space_node->getBoundaryPolygon();

        for(size_t i = 0; i < wall_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = wall_space_polygon.point_list[i];
            const EasyPoint2D &next_point = wall_space_polygon.point_list[
              (i + 1) % wall_space_polygon.point_list.size()];

            EasyPoint2D current_point_in_world;
            EasyPoint2D next_point_in_world;
            wall_space_node->getPointInWorld(
                current_point, current_point_in_world);
            wall_space_node->getPointInWorld(
                next_point, next_point_in_world);

            painter.drawLine(
                current_point_in_world.x, current_point_in_world.y,
                next_point_in_world.x, next_point_in_world.y);
        }
    }

    return true;
}

bool EasyWorldWidget::drawRoomBoundaryAxis()
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> room_boundary_node_vec_vec;

    world_controller_.getRoomBoundaryNodeVecVec(room_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& room_boundary_node_vec: room_boundary_node_vec_vec)
    {
        for(const EasyNode* room_boundary_node : room_boundary_node_vec)
        {
            if(room_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D room_boundary_axis = room_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                room_boundary_axis.center_.x, room_boundary_axis.center_.y,
                room_boundary_axis.center_.x + axis_length_ * room_boundary_axis.x_direction_.x,
                room_boundary_axis.center_.y + axis_length_ * room_boundary_axis.x_direction_.y);

            painter.setPen(pen_green);

            painter.drawLine(
                room_boundary_axis.center_.x, room_boundary_axis.center_.y,
                room_boundary_axis.center_.x + axis_length_ * room_boundary_axis.y_direction_.x,
                room_boundary_axis.center_.y + axis_length_ * room_boundary_axis.y_direction_.y);
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawRoomBoundaryPolygon()
{
    QPainter painter(this);

    QPen pen_black(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen_black);

    std::vector<std::vector<EasyNode*>> room_boundary_node_vec_vec;

    world_controller_.getRoomBoundaryNodeVecVec(room_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &room_boundary_node_vec :
        room_boundary_node_vec_vec)
    {
        for(EasyNode* room_boundary_node : room_boundary_node_vec)
        {
            const EasyPolygon2D &room_boundary_polygon =
              room_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < room_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point =
                  room_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point =
                  room_boundary_polygon.point_list[
                  (i + 1) % room_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                room_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                room_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

                painter.drawLine(
                    current_point_in_world.x, current_point_in_world.y,
                    next_point_in_world.x, next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawRoomSpaceBoundary()
{
    QPainter painter(this);

    QPen pen_black(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen_black);

    std::vector<EasyNode*> room_space_node_vec;

    world_controller_.getRoomSpaceNodeVec(room_space_node_vec);

    for(EasyNode* room_space_node : room_space_node_vec)
    {
        if(room_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &room_space_polygon =
          room_space_node->getBoundaryPolygon();

        for(size_t i = 0; i < room_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = room_space_polygon.point_list[i];
            const EasyPoint2D &next_point = room_space_polygon.point_list[
              (i + 1) % room_space_polygon.point_list.size()];

            EasyPoint2D current_point_in_world;
            EasyPoint2D next_point_in_world;
            room_space_node->getPointInWorld(
                current_point, current_point_in_world);
            room_space_node->getPointInWorld(
                next_point, next_point_in_world);

            painter.drawLine(
                current_point_in_world.x, current_point_in_world.y,
                next_point_in_world.x, next_point_in_world.y);
        }
    }

    return true;
}

bool EasyWorldWidget::drawTeamBoundaryAxis()
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> team_boundary_node_vec_vec;

    world_controller_.getTeamBoundaryNodeVecVec(team_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& team_boundary_node_vec: team_boundary_node_vec_vec)
    {
        for(const EasyNode* team_boundary_node : team_boundary_node_vec)
        {
            if(team_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D team_boundary_axis = team_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                team_boundary_axis.center_.x, team_boundary_axis.center_.y,
                team_boundary_axis.center_.x + axis_length_ * team_boundary_axis.x_direction_.x,
                team_boundary_axis.center_.y + axis_length_ * team_boundary_axis.x_direction_.y);

            painter.setPen(pen_green);

            painter.drawLine(
                team_boundary_axis.center_.x, team_boundary_axis.center_.y,
                team_boundary_axis.center_.x + axis_length_ * team_boundary_axis.y_direction_.x,
                team_boundary_axis.center_.y + axis_length_ * team_boundary_axis.y_direction_.y);
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawTeamBoundaryPolygon()
{
    QPainter painter(this);

    QPen pen_black(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen_black);

    std::vector<std::vector<EasyNode*>> team_boundary_node_vec_vec;

    world_controller_.getTeamBoundaryNodeVecVec(team_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &team_boundary_node_vec :
        team_boundary_node_vec_vec)
    {
        for(EasyNode* team_boundary_node : team_boundary_node_vec)
        {
            const EasyPolygon2D &team_boundary_polygon =
              team_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < team_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point =
                  team_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point =
                  team_boundary_polygon.point_list[
                  (i + 1) % team_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                team_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                team_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

                painter.drawLine(
                    current_point_in_world.x, current_point_in_world.y,
                    next_point_in_world.x, next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawTeamSpaceBoundary()
{
    QPainter painter(this);

    QPen pen_black(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen_black);

    std::vector<EasyNode*> team_space_node_vec;

    world_controller_.getTeamSpaceNodeVec(team_space_node_vec);

    for(EasyNode* team_space_node : team_space_node_vec)
    {
        if(team_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &team_space_polygon =
          team_space_node->getBoundaryPolygon();

        for(size_t i = 0; i < team_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = team_space_polygon.point_list[i];
            const EasyPoint2D &next_point = team_space_polygon.point_list[
              (i + 1) % team_space_polygon.point_list.size()];

            EasyPoint2D current_point_in_world;
            EasyPoint2D next_point_in_world;
            team_space_node->getPointInWorld(
                current_point, current_point_in_world);
            team_space_node->getPointInWorld(
                next_point, next_point_in_world);

            painter.drawLine(
                current_point_in_world.x, current_point_in_world.y,
                next_point_in_world.x, next_point_in_world.y);
        }
    }

    return true;
}

bool EasyWorldWidget::drawPersonBoundaryAxis()
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> person_boundary_node_vec_vec;

    world_controller_.getPersonBoundaryNodeVecVec(person_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& person_boundary_node_vec: person_boundary_node_vec_vec)
    {
        for(const EasyNode* person_boundary_node : person_boundary_node_vec)
        {
            if(person_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D person_boundary_axis = person_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                person_boundary_axis.center_.x, person_boundary_axis.center_.y,
                person_boundary_axis.center_.x + axis_length_ * person_boundary_axis.x_direction_.x,
                person_boundary_axis.center_.y + axis_length_ * person_boundary_axis.x_direction_.y);

            painter.setPen(pen_green);

            painter.drawLine(
                person_boundary_axis.center_.x, person_boundary_axis.center_.y,
                person_boundary_axis.center_.x + axis_length_ * person_boundary_axis.y_direction_.x,
                person_boundary_axis.center_.y + axis_length_ * person_boundary_axis.y_direction_.y);
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawPersonBoundaryPolygon()
{
    QPainter painter(this);

    QPen pen_black(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen_black);

    std::vector<std::vector<EasyNode*>> person_boundary_node_vec_vec;

    world_controller_.getPersonBoundaryNodeVecVec(person_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &person_boundary_node_vec :
        person_boundary_node_vec_vec)
    {
        for(EasyNode* person_boundary_node : person_boundary_node_vec)
        {
            const EasyPolygon2D &person_boundary_polygon =
              person_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < person_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point =
                  person_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point =
                  person_boundary_polygon.point_list[
                  (i + 1) % person_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                person_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                person_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

                painter.drawLine(
                    current_point_in_world.x, current_point_in_world.y,
                    next_point_in_world.x, next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawPersonSpaceBoundary()
{
    QPainter painter(this);

    QPen pen_black(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen_black);

    std::vector<EasyNode*> person_space_node_vec;

    world_controller_.getPersonSpaceNodeVec(person_space_node_vec);

    for(EasyNode* person_space_node : person_space_node_vec)
    {
        if(person_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &person_space_polygon =
          person_space_node->getBoundaryPolygon();

        for(size_t i = 0; i < person_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = person_space_polygon.point_list[i];
            const EasyPoint2D &next_point = person_space_polygon.point_list[
              (i + 1) % person_space_polygon.point_list.size()];

            EasyPoint2D current_point_in_world;
            EasyPoint2D next_point_in_world;
            person_space_node->getPointInWorld(
                current_point, current_point_in_world);
            person_space_node->getPointInWorld(
                next_point, next_point_in_world);

            painter.drawLine(
                current_point_in_world.x, current_point_in_world.y,
                next_point_in_world.x, next_point_in_world.y);
        }
    }

    return true;
}


bool EasyWorldWidget::drawFurnitureBoundaryAxis()
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> furniture_boundary_node_vec_vec;

    world_controller_.getFurnitureBoundaryNodeVecVec(furniture_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& furniture_boundary_node_vec: furniture_boundary_node_vec_vec)
    {
        for(const EasyNode* furniture_boundary_node : furniture_boundary_node_vec)
        {
            if(furniture_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D furniture_boundary_axis = furniture_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                furniture_boundary_axis.center_.x, furniture_boundary_axis.center_.y,
                furniture_boundary_axis.center_.x + axis_length_ * furniture_boundary_axis.x_direction_.x,
                furniture_boundary_axis.center_.y + axis_length_ * furniture_boundary_axis.x_direction_.y);

            painter.setPen(pen_green);

            painter.drawLine(
                furniture_boundary_axis.center_.x, furniture_boundary_axis.center_.y,
                furniture_boundary_axis.center_.x + axis_length_ * furniture_boundary_axis.y_direction_.x,
                furniture_boundary_axis.center_.y + axis_length_ * furniture_boundary_axis.y_direction_.y);
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawFurnitureBoundaryPolygon()
{
    QPainter painter(this);

    QPen pen_black(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen_black);

    std::vector<std::vector<EasyNode*>> furniture_boundary_node_vec_vec;

    world_controller_.getFurnitureBoundaryNodeVecVec(furniture_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &furniture_boundary_node_vec :
        furniture_boundary_node_vec_vec)
    {
        for(EasyNode* furniture_boundary_node : furniture_boundary_node_vec)
        {
            const EasyPolygon2D &furniture_boundary_polygon =
              furniture_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < furniture_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point =
                  furniture_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point =
                  furniture_boundary_polygon.point_list[
                  (i + 1) % furniture_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                furniture_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                furniture_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

                painter.drawLine(
                    current_point_in_world.x, current_point_in_world.y,
                    next_point_in_world.x, next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawFurnitureSpaceBoundary()
{
    QPainter painter(this);

    QPen pen_black(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen_black);

    std::vector<EasyNode*> furniture_space_node_vec;

    world_controller_.getFurnitureSpaceNodeVec(furniture_space_node_vec);

    for(EasyNode* furniture_space_node : furniture_space_node_vec)
    {
        if(furniture_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &furniture_space_polygon =
          furniture_space_node->getBoundaryPolygon();

        for(size_t i = 0; i < furniture_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = furniture_space_polygon.point_list[i];
            const EasyPoint2D &next_point = furniture_space_polygon.point_list[
              (i + 1) % furniture_space_polygon.point_list.size()];

            EasyPoint2D current_point_in_world;
            EasyPoint2D next_point_in_world;
            furniture_space_node->getPointInWorld(
                current_point, current_point_in_world);
            furniture_space_node->getPointInWorld(
                next_point, next_point_in_world);

            painter.drawLine(
                current_point_in_world.x, current_point_in_world.y,
                next_point_in_world.x, next_point_in_world.y);
        }
    }

    return true;
}

bool EasyWorldWidget::setStartTime()
{
    clock_gettime(CLOCK_REALTIME_COARSE, &t_spc_);
    t_start_ = t_spc_.tv_sec;
    last_second_ = t_start_;

    return true;
}

bool EasyWorldWidget::getFPS(
    const long &cycle_num,
    float &average_fps)
{
    clock_gettime(CLOCK_REALTIME_COARSE, &t_spc_);

    const long t_end_ = t_spc_.tv_sec;

    if(t_end_ == last_second_)
    {
        return true;
    }

    last_second_ = t_end_;

    average_fps = 1.0 * cycle_num / (t_end_ - t_start_);

    return true;
}
