#include "EasyWorldWidget.h"
#include "qglobal.h"
#include "ui_EasyWorldWidget.h"

EasyWorldWidget::EasyWorldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EasyWorldWidget)
{
    ui->setupUi(this);

    axis_length_ = 10;
    zoom_ = 1;
    wall_color_ = QColor(0, 0, 0);
    roomcontainer_color_ = QColor(0, 0, 0);
    room_color_ = QColor(0, 0, 0);
    team_color_ = QColor(0, 0, 0);
    person_color_ = QColor(0, 0, 0);
    furniture_color_ = QColor(0, 0, 0);

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
    size_t demo_mode = 2;

    switch(demo_mode)
    {
    case 0:
        {
            zoom_ = 1;

            world_controller_.reset();
            world_controller_.createWorld(400, 400);

            world_controller_.createWall(0, NodeType::OuterWall);
            EasyPolygon2D wall_boundary_polygon;
            wall_boundary_polygon.addPoint(0, 0);
            wall_boundary_polygon.addPoint(300, 0);
            wall_boundary_polygon.addPoint(300, 300);
            wall_boundary_polygon.addPoint(0, 300);
            wall_boundary_polygon.setAntiClockWise();
            world_controller_.setWallBoundaryPolygon(0, NodeType::OuterWall, wall_boundary_polygon);

            EasyAxis2D axis;
            axis.setXDirection(1, 0);
            axis.setCenter(10, 110);
            world_controller_.createFreeRoomContainerForWall(0, NodeType::OuterWall, 0, 280, 80, axis, 3);
            axis.setCenter(0, 0);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 0, 300, 100, axis, 3);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 2, 100, 100, axis, 1);
            axis.setCenter(200, 0);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 2, 100, 100, axis, 1);

            axis.setCenter(25, 25);
            world_controller_.createTeamForRoom(0, NodeType::WallRoom, 50, 50, axis, 2, 2, true);
            world_controller_.createTeamForRoom(1, NodeType::WallRoom, 50, 50, axis, 2, 2, false);
            world_controller_.createTeamForRoom(2, NodeType::WallRoom, 50, 50, axis, 2, 2, true);
            world_controller_.createTeamForRoom(3, NodeType::WallRoom, 50, 50, axis, 1, 1, false);
            world_controller_.createTeamForRoom(4, NodeType::WallRoom, 50, 50, axis, 1, 1, false);
            axis.setCenter(10, 10);
            world_controller_.createTeamForRoom(0, NodeType::FreeRoom, 80, 60, axis, 4, 4, true);
            world_controller_.createTeamForRoom(1, NodeType::FreeRoom, 80, 60, axis, 4, 4, true);
            world_controller_.createTeamForRoom(2, NodeType::FreeRoom, 80, 60, axis, 4, 4, true);
            break;
        }
    case 1:
        {
            zoom_ = 22;

            world_controller_.reset();
            world_controller_.createWorld(1, 1);

            world_controller_.createWall(0, NodeType::OuterWall);
            EasyPolygon2D wall_boundary_polygon;
            wall_boundary_polygon.addPoint(0, 0);
            wall_boundary_polygon.addPoint(20, 0);
            wall_boundary_polygon.addPoint(20, 40);
            wall_boundary_polygon.addPoint(0, 40);
            wall_boundary_polygon.setAntiClockWise();
            world_controller_.setWallBoundaryPolygon(0, NodeType::OuterWall, wall_boundary_polygon);

            EasyAxis2D axis;
            axis.setXDirection(1, 0);
            axis.setCenter(24, 0);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 3, 16, 8, axis, 2);
            axis.setCenter(18, 0);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 3, 6, 4, axis, 1);
            axis.setCenter(18, 4);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 3, 1, 3, axis, 1);
            axis.setCenter(18, 7);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 3, 4, 1, axis, 1);
            axis.setCenter(12, 0);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 0, 8, 2, axis, 1);
            axis.setCenter(2, 0);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 1, 4, 4, axis, 1);
            axis.setCenter(6, 0);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 1, 4, 8, axis, 1);
            axis.setCenter(16, 0);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 1, 4, 8, axis, 1);
            axis.setCenter(20, 2);
            world_controller_.createWallRoomContainerForWall(0, NodeType::OuterWall, 1, 2, 6, axis, 1);
            axis.setCenter(0, 0);
            world_controller_.createFreeRoomContainerForWall(0, NodeType::OuterWall, 2, 20, 18, axis, 2);

            axis.setCenter(1, 2);
            world_controller_.createTeamForRoom(0, NodeType::FreeRoom, 8, 14, axis, 5, 10, false);
            world_controller_.createTeamForRoom(1, NodeType::FreeRoom, 8, 14, axis, 5, 10, false);
            axis.setCenter(3, 1);
            world_controller_.createTeamForRoom(1, NodeType::WallRoom, 2, 2, axis, 1, 1, false);
            axis.setCenter(3, 1);
            world_controller_.createTeamForRoom(0, NodeType::WallRoom, 2, 6, axis, 2, 6, true);
            axis.setCenter(2.5, 0.5);
            world_controller_.createTeamForRoom(2, NodeType::WallRoom, 1, 1, axis, 1, 1, false);
            break;
        }
    case 2:
        {
            zoom_ = 20;

            EasyPolygon2D wall_boundary_polygon;
            wall_boundary_polygon.addPoint(0, 0);
            wall_boundary_polygon.addPoint(20, 0);
            wall_boundary_polygon.addPoint(20, 40);
            wall_boundary_polygon.addPoint(0, 40);
            wall_boundary_polygon.setAntiClockWise();

            world_generator_.setWallBoundaryPolygon(wall_boundary_polygon);
            world_generator_.setPersonNum(80);
            world_generator_.setRoomNum(6);
            world_generator_.generateWorld();

            // long cycle_num = 0;
            // float avg_fps = -1;
            // setStartTime();
            // while(true)
            // {
            //     world_generator_.generateWorld();
            //     ++cycle_num;
            //     getFPS(cycle_num, avg_fps);
            //
            //     std::cout << "fps = " << avg_fps << std::endl;
            // }
            break;
        }
    }

    // world_controller_.outputInfo();

    std::cout << "finish run_example!" << std::endl;
}

void EasyWorldWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    drawWallSpaceBoundary(world_generator_.world_controller_);
    // drawRoomContainerSpaceBoundary(world_generator_.world_controller_);
    drawRoomSpaceBoundary(world_generator_.world_controller_);
    // drawTeamSpaceBoundary(world_generator_.world_controller_);
    // drawPersonSpaceBoundary(world_generator_.world_controller_);
    drawFurnitureSpaceBoundary(world_generator_.world_controller_);

    // drawWallBoundaryAxis(world_generator_.world_controller_);
    // drawRoomContainerBoundaryAxis(world_generator_.world_controller_);
    // drawRoomBoundaryAxis(world_generator_.world_controller_);
    // drawTeamBoundaryAxis(world_generator_.world_controller_);
    // drawPersonBoundaryAxis(world_generator_.world_controller_);
    // drawFurnitureBoundaryAxis(world_generator_.world_controller_);
}

void EasyWorldWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    world_generator_.generateWorld();

    update();
}

void EasyWorldWidget::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    // moveWallInWorld(0, NodeType::OuterWall, event);

    // moveRoomContainerInWorld(0, NodeType::RoomContainer, event);

    // moveRoomInWorld(0, NodeType::WallRoom, event);

    // moveTeamInWorld(0, NodeType::Team, event);
}

void EasyWorldWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
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

bool EasyWorldWidget::moveRoomContainerInWorld(
    const size_t &roomcontainer_id,
    const NodeType &roomcontainer_type,
    QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        const QPoint &mouse_pos = event->pos();

        EasyPoint2D new_roomcontainer_pos;

        new_roomcontainer_pos.setPosition(mouse_pos.x(), mouse_pos.y());

        world_controller_.setRoomContainerAxisCenterPositionInWorld(
            roomcontainer_id, roomcontainer_type, new_roomcontainer_pos);

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

bool EasyWorldWidget::drawWallBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> wall_boundary_node_vec_vec;

    world_controller.getWallBoundaryNodeVecVec(wall_boundary_node_vec_vec);

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
                zoom_ * wall_boundary_axis.center_.x, zoom_ * wall_boundary_axis.center_.y,
                zoom_ * (wall_boundary_axis.center_.x + axis_length_ * wall_boundary_axis.x_direction_.x),
                zoom_ * (wall_boundary_axis.center_.y + axis_length_ * wall_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * wall_boundary_axis.center_.x, zoom_ * wall_boundary_axis.center_.y,
                zoom_ * (wall_boundary_axis.center_.x + axis_length_ * wall_boundary_axis.y_direction_.x),
                zoom_ * (wall_boundary_axis.center_.y + axis_length_ * wall_boundary_axis.y_direction_.y));
        }
        
    }
    
    return true;
}

bool EasyWorldWidget::drawWallBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(wall_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> wall_boundary_node_vec_vec;

    world_controller.getWallBoundaryNodeVecVec(wall_boundary_node_vec_vec);

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
                zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawWallSpaceBoundary(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(wall_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<EasyNode*> wall_space_node_vec;

    world_controller.getWallSpaceNodeVec(wall_space_node_vec);

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
                zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
        }
    }

    return true;
}

bool EasyWorldWidget::drawRoomContainerBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> roomcontainer_boundary_node_vec_vec;

    world_controller.getRoomContainerBoundaryNodeVecVec(roomcontainer_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& roomcontainer_boundary_node_vec: roomcontainer_boundary_node_vec_vec)
    {
        for(const EasyNode* roomcontainer_boundary_node : roomcontainer_boundary_node_vec)
        {
            if(roomcontainer_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D roomcontainer_boundary_axis = roomcontainer_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                zoom_ * roomcontainer_boundary_axis.center_.x, zoom_ * roomcontainer_boundary_axis.center_.y,
                zoom_ * (roomcontainer_boundary_axis.center_.x + axis_length_ * roomcontainer_boundary_axis.x_direction_.x),
                zoom_ * (roomcontainer_boundary_axis.center_.y + axis_length_ * roomcontainer_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * roomcontainer_boundary_axis.center_.x, zoom_ * roomcontainer_boundary_axis.center_.y,
                zoom_ * (roomcontainer_boundary_axis.center_.x + axis_length_ * roomcontainer_boundary_axis.y_direction_.x),
                zoom_ * (roomcontainer_boundary_axis.center_.y + axis_length_ * roomcontainer_boundary_axis.y_direction_.y));
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawRoomContainerBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(roomcontainer_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> roomcontainer_boundary_node_vec_vec;

    world_controller.getRoomContainerBoundaryNodeVecVec(roomcontainer_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &roomcontainer_boundary_node_vec :
        roomcontainer_boundary_node_vec_vec)
    {
        for(EasyNode* roomcontainer_boundary_node : roomcontainer_boundary_node_vec)
        {
            const EasyPolygon2D &roomcontainer_boundary_polygon =
              roomcontainer_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < roomcontainer_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point =
                  roomcontainer_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point =
                  roomcontainer_boundary_polygon.point_list[
                  (i + 1) % roomcontainer_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                roomcontainer_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                roomcontainer_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

                painter.drawLine(
                    zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                    zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawRoomContainerSpaceBoundary(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(roomcontainer_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<EasyNode*> roomcontainer_space_node_vec;

    world_controller.getRoomContainerSpaceNodeVec(roomcontainer_space_node_vec);

    for(EasyNode* roomcontainer_space_node : roomcontainer_space_node_vec)
    {
        if(roomcontainer_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &roomcontainer_space_polygon =
          roomcontainer_space_node->getBoundaryPolygon();

        for(size_t i = 0; i < roomcontainer_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = roomcontainer_space_polygon.point_list[i];
            const EasyPoint2D &next_point = roomcontainer_space_polygon.point_list[
              (i + 1) % roomcontainer_space_polygon.point_list.size()];

            EasyPoint2D current_point_in_world;
            EasyPoint2D next_point_in_world;
            roomcontainer_space_node->getPointInWorld(
                current_point, current_point_in_world);
            roomcontainer_space_node->getPointInWorld(
                next_point, next_point_in_world);

            painter.drawLine(
                zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
        }
    }

    return true;
}

bool EasyWorldWidget::drawRoomBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> room_boundary_node_vec_vec;

    world_controller.getRoomBoundaryNodeVecVec(room_boundary_node_vec_vec);

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
                zoom_ * room_boundary_axis.center_.x, zoom_ * room_boundary_axis.center_.y,
                zoom_ * (room_boundary_axis.center_.x + axis_length_ * room_boundary_axis.x_direction_.x),
                zoom_ * (room_boundary_axis.center_.y + axis_length_ * room_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * room_boundary_axis.center_.x, zoom_ * room_boundary_axis.center_.y,
                zoom_ * (room_boundary_axis.center_.x + axis_length_ * room_boundary_axis.y_direction_.x),
                zoom_ * (room_boundary_axis.center_.y + axis_length_ * room_boundary_axis.y_direction_.y));
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawRoomBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(room_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> room_boundary_node_vec_vec;

    world_controller.getRoomBoundaryNodeVecVec(room_boundary_node_vec_vec);

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
                    zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                    zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawRoomSpaceBoundary(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(room_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<EasyNode*> room_space_node_vec;

    world_controller.getRoomSpaceNodeVec(room_space_node_vec);

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
                zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
        }
    }

    return true;
}

bool EasyWorldWidget::drawTeamBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> team_boundary_node_vec_vec;

    world_controller.getTeamBoundaryNodeVecVec(team_boundary_node_vec_vec);

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
                zoom_ * team_boundary_axis.center_.x, zoom_ * team_boundary_axis.center_.y,
                zoom_ * (team_boundary_axis.center_.x + axis_length_ * team_boundary_axis.x_direction_.x),
                zoom_ * (team_boundary_axis.center_.y + axis_length_ * team_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * team_boundary_axis.center_.x, zoom_ * team_boundary_axis.center_.y,
                zoom_ * (team_boundary_axis.center_.x + axis_length_ * team_boundary_axis.y_direction_.x),
                zoom_ * (team_boundary_axis.center_.y + axis_length_ * team_boundary_axis.y_direction_.y));
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawTeamBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(team_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> team_boundary_node_vec_vec;

    world_controller.getTeamBoundaryNodeVecVec(team_boundary_node_vec_vec);

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
                    zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                    zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawTeamSpaceBoundary(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(team_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<EasyNode*> team_space_node_vec;

    world_controller.getTeamSpaceNodeVec(team_space_node_vec);

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
                zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
        }
    }

    return true;
}

bool EasyWorldWidget::drawPersonBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> person_boundary_node_vec_vec;

    world_controller.getPersonBoundaryNodeVecVec(person_boundary_node_vec_vec);

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
                zoom_ * person_boundary_axis.center_.x, zoom_ * person_boundary_axis.center_.y,
                zoom_ * (person_boundary_axis.center_.x + axis_length_ * person_boundary_axis.x_direction_.x),
                zoom_ * (person_boundary_axis.center_.y + axis_length_ * person_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * person_boundary_axis.center_.x, zoom_ * person_boundary_axis.center_.y,
                zoom_ * (person_boundary_axis.center_.x + axis_length_ * person_boundary_axis.y_direction_.x),
                zoom_ * (person_boundary_axis.center_.y + axis_length_ * person_boundary_axis.y_direction_.y));
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawPersonBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(person_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> person_boundary_node_vec_vec;

    world_controller.getPersonBoundaryNodeVecVec(person_boundary_node_vec_vec);

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
                    zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                    zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawPersonSpaceBoundary(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(person_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<EasyNode*> person_space_node_vec;

    world_controller.getPersonSpaceNodeVec(person_space_node_vec);

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
                zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
        }
    }

    return true;
}


bool EasyWorldWidget::drawFurnitureBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> furniture_boundary_node_vec_vec;

    world_controller.getFurnitureBoundaryNodeVecVec(furniture_boundary_node_vec_vec);

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
                zoom_ * furniture_boundary_axis.center_.x, zoom_ * furniture_boundary_axis.center_.y,
                zoom_ * (furniture_boundary_axis.center_.x + axis_length_ * furniture_boundary_axis.x_direction_.x),
                zoom_ * (furniture_boundary_axis.center_.y + axis_length_ * furniture_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * furniture_boundary_axis.center_.x, zoom_ * furniture_boundary_axis.center_.y,
                zoom_ * (furniture_boundary_axis.center_.x + axis_length_ * furniture_boundary_axis.y_direction_.x),
                zoom_ * (furniture_boundary_axis.center_.y + axis_length_ * furniture_boundary_axis.y_direction_.y));
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawFurnitureBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(furniture_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> furniture_boundary_node_vec_vec;

    world_controller.getFurnitureBoundaryNodeVecVec(furniture_boundary_node_vec_vec);

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
                    zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                    zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawFurnitureSpaceBoundary(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(furniture_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<EasyNode*> furniture_space_node_vec;

    world_controller.getFurnitureSpaceNodeVec(furniture_space_node_vec);

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
                zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
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
