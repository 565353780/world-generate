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
    wall_brush_color_ = QColor(0, 0, 0);
    roomcontainer_color_ = QColor(0, 0, 0);
    roomcontainer_brush_color_ = QColor(0, 0, 0);
    room_color_ = QColor(102,102,104);
    room_brush_color_ = QColor(166,145,110);
    door_color_ = QColor(200, 200, 200);
    door_brush_color_ = QColor(200, 200, 200);
    window_color_ = QColor(200,200,200);
    window_brush_color_ = QColor(200,200,200);
    team_color_ = QColor(0, 0, 0);
    team_brush_color_ = QColor(0, 0, 0);
    person_color_ = QColor(0, 0, 0);
    person_brush_color_ = QColor(0, 0, 0);
    furniture_color_ = QColor(157,157,161);
    furniture_brush_color_ = QColor(255,255,255);

    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;

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
    size_t demo_mode = 4;

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

            world_split_generator_.setWallBoundaryPolygon(wall_boundary_polygon);
            world_split_generator_.setPersonNum(80);
            world_split_generator_.setRoomNum(6);
            world_split_generator_.generateWorld();

            // long cycle_num = 0;
            // float avg_fps = -1;
            // setStartTime();
            // while(true)
            // {
            //     world_split_generator_.generateWorld();
            //     ++cycle_num;
            //     getFPS(cycle_num, avg_fps);
            //
            //     std::cout << "fps = " << avg_fps << std::endl;
            // }
            break;
        }
    case 3:
        {
            zoom_ = 20;

            EasyPolygon2D wall_boundary_polygon;
            wall_boundary_polygon.addPoint(0, 0);
            wall_boundary_polygon.addPoint(20, 0);
            wall_boundary_polygon.addPoint(20, 40);
            wall_boundary_polygon.addPoint(0, 40);
            wall_boundary_polygon.setAntiClockWise();

            world_place_generator_.setWallBoundaryPolygon(wall_boundary_polygon);
            world_place_generator_.generateWorld();

            // long cycle_num = 0;
            // float avg_fps = 0;
            // setStartTime();
            // while(true)
            // {
            //     world_editer_.world_place_generator_.generateWorld();
            //     ++cycle_num;
            //     getFPS(cycle_num, avg_fps);
            //
            //     std::cout << "fps = " << size_t(avg_fps) << std::endl;
            // }

            break;
        }
    case 4:
        {
            zoom_ = 20;

            EasyPolygon2D wall_boundary_polygon;
            wall_boundary_polygon.addPoint(0, 0);
            wall_boundary_polygon.addPoint(20, 0);
            wall_boundary_polygon.addPoint(20, 40);
            wall_boundary_polygon.addPoint(0, 40);
            wall_boundary_polygon.setAntiClockWise();

            world_place_generator_.setWallBoundaryPolygon(wall_boundary_polygon);
            world_place_generator_.generateWorld();

            // long cycle_num = 0;
            // float avg_fps = 0;
            // setStartTime();
            // while(true)
            // {
            //     world_editer_.world_place_generator_.generateWorld();
            //     ++cycle_num;
            //     getFPS(cycle_num, avg_fps);
            //
            //     std::cout << "fps = " << size_t(avg_fps) << std::endl;
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

    WorldController &world_controller = world_place_generator_.world_controller_;

    drawWallSpaceBoundary(world_controller);
    // drawRoomContainerSpaceBoundary(world_controller);
    drawRoomSpaceBoundary(world_controller);
    // drawTeamSpaceBoundary(world_controller);
    // drawPersonSpaceBoundary(world_controller);
    drawFurnitureSpaceBoundary(world_controller);
    drawDoorSpaceBoundary(world_controller);
    drawWindowSpaceBoundary(world_controller);

    // drawWallBoundaryAxis(world_controller);
    // drawRoomContainerBoundaryAxis(world_controller);
    // drawRoomBoundaryAxis(world_controller);
    // drawDoorBoundaryAxis(world_controller);
    // drawWindowBoundaryAxis(world_controller);
    // drawTeamBoundaryAxis(world_controller);
    // drawPersonBoundaryAxis(world_controller);
    // drawFurnitureBoundaryAxis(world_controller);
}

void EasyWorldWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    if(event->buttons() == Qt::LeftButton)
    {
        chooseRoomContainer(event);
    }
    else if(event->buttons() == Qt::RightButton)
    {
        world_place_generator_.generateWorld();
        update();
    }

}

void EasyWorldWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        if(current_choose_node_type_ == NodeType::RoomContainer)
        {
            moveWallRoomContainer(current_choose_node_id_, event);
        }
    }
}

void EasyWorldWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

bool EasyWorldWidget::chooseRoomContainer(
    QMouseEvent *event)
{
    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;

    std::vector<EasyNode*> roomcontainer_space_node_vec;

    world_place_generator_.world_controller_.getRoomContainerSpaceNodeVec(
        roomcontainer_space_node_vec);

    for(EasyNode* roomcontainer_space_node : roomcontainer_space_node_vec)
    {
        const EasyPolygon2D &polygon = roomcontainer_space_node->getBoundaryPolygon();

        EasyPoint2D mouse_pos_in_world;
        EasyPoint2D mouse_pos_in_node;
        mouse_pos_in_world.setPosition(event->x() / zoom_, event->y() / zoom_);

        roomcontainer_space_node->getPointInNode(
            mouse_pos_in_world, mouse_pos_in_node);

        if(EasyComputation::isPointInPolygon(
              mouse_pos_in_node, polygon))
        {
            EasyNode* roomcontainer_node = roomcontainer_space_node->getParent();
            current_choose_node_id_ = roomcontainer_node->getID();
            current_choose_node_type_ = roomcontainer_node->getNodeType();

            current_press_position_to_start_position = mouse_pos_in_node.x;

            return true;
        }
    }

    return false;
}

bool EasyWorldWidget::moveWallRoomContainer(
    const size_t &wall_roomcontainer_id,
    QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        const QPoint &mouse_pos = event->pos();

        const float new_position_x =
          1.0 * mouse_pos.x() / zoom_;
        const float new_position_y =
          1.0 * mouse_pos.y() / zoom_;

        world_editer_.setWallRoomContainerPosition(
            world_place_generator_,
            wall_roomcontainer_id,
            new_position_x,
            new_position_y,
            current_press_position_to_start_position);

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

    if(wall_brush_color_.red() != 0 ||
        wall_brush_color_.green() != 0 ||
        wall_brush_color_.blue() != 0)
    {
        QBrush brush;
        brush.setColor(wall_brush_color_);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }

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

        QPolygon polygon;
        polygon.resize(wall_space_polygon.point_list.size());

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

            polygon.setPoint(i, QPoint(
                  zoom_ * current_point_in_world.x,
                  zoom_ * current_point_in_world.y));
        }
        painter.drawPolygon(polygon);
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

    if(room_brush_color_.red() != 0 ||
        room_brush_color_.green() != 0 ||
        room_brush_color_.blue() != 0)
    {
        QBrush brush;
        brush.setColor(room_brush_color_);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }

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

        QPolygon polygon;
        polygon.resize(room_space_polygon.point_list.size());

        for(size_t i = 0; i < room_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = room_space_polygon.point_list[i];

            EasyPoint2D current_point_in_world;
            room_space_node->getPointInWorld(
                current_point, current_point_in_world);

            polygon.setPoint(i, QPoint(
                  zoom_ * current_point_in_world.x,
                  zoom_ * current_point_in_world.y));
        }
        painter.drawPolygon(polygon);
    }

    return true;
}

bool EasyWorldWidget::drawDoorBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> door_boundary_node_vec_vec;

    world_controller.getDoorBoundaryNodeVecVec(door_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& door_boundary_node_vec: door_boundary_node_vec_vec)
    {
        for(const EasyNode* door_boundary_node : door_boundary_node_vec)
        {
            if(door_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D door_boundary_axis = door_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                zoom_ * door_boundary_axis.center_.x, zoom_ * door_boundary_axis.center_.y,
                zoom_ * (door_boundary_axis.center_.x + axis_length_ * door_boundary_axis.x_direction_.x),
                zoom_ * (door_boundary_axis.center_.y + axis_length_ * door_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * door_boundary_axis.center_.x, zoom_ * door_boundary_axis.center_.y,
                zoom_ * (door_boundary_axis.center_.x + axis_length_ * door_boundary_axis.y_direction_.x),
                zoom_ * (door_boundary_axis.center_.y + axis_length_ * door_boundary_axis.y_direction_.y));
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawDoorBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(door_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> door_boundary_node_vec_vec;

    world_controller.getDoorBoundaryNodeVecVec(door_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &door_boundary_node_vec :
        door_boundary_node_vec_vec)
    {
        for(EasyNode* door_boundary_node : door_boundary_node_vec)
        {
            const EasyPolygon2D &door_boundary_polygon =
              door_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < door_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point =
                  door_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point =
                  door_boundary_polygon.point_list[
                  (i + 1) % door_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                door_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                door_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

                painter.drawLine(
                    zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                    zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawDoorSpaceBoundary(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(door_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    if(door_brush_color_.red() != 0 ||
        door_brush_color_.green() != 0 ||
        door_brush_color_.blue() != 0)
    {
        QBrush brush;
        brush.setColor(door_brush_color_);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }

    std::vector<EasyNode*> door_space_node_vec;

    world_controller.getDoorSpaceNodeVec(door_space_node_vec);

    for(EasyNode* door_space_node : door_space_node_vec)
    {
        if(door_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &door_space_polygon =
          door_space_node->getBoundaryPolygon();

        QPolygon polygon;
        polygon.resize(door_space_polygon.point_list.size());

        for(size_t i = 0; i < door_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = door_space_polygon.point_list[i];

            EasyPoint2D current_point_in_world;
            door_space_node->getPointInWorld(
                current_point, current_point_in_world);

            polygon.setPoint(i, QPoint(
                  zoom_ * current_point_in_world.x,
                  zoom_ * current_point_in_world.y));
        }
        painter.drawPolygon(polygon);
    }

    return true;
}

bool EasyWorldWidget::drawWindowBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    std::vector<std::vector<EasyNode*>> window_boundary_node_vec_vec;

    world_controller.getWindowBoundaryNodeVecVec(window_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& window_boundary_node_vec: window_boundary_node_vec_vec)
    {
        for(const EasyNode* window_boundary_node : window_boundary_node_vec)
        {
            if(window_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D window_boundary_axis = window_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                zoom_ * window_boundary_axis.center_.x, zoom_ * window_boundary_axis.center_.y,
                zoom_ * (window_boundary_axis.center_.x + axis_length_ * window_boundary_axis.x_direction_.x),
                zoom_ * (window_boundary_axis.center_.y + axis_length_ * window_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * window_boundary_axis.center_.x, zoom_ * window_boundary_axis.center_.y,
                zoom_ * (window_boundary_axis.center_.x + axis_length_ * window_boundary_axis.y_direction_.x),
                zoom_ * (window_boundary_axis.center_.y + axis_length_ * window_boundary_axis.y_direction_.y));
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawWindowBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(window_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> window_boundary_node_vec_vec;

    world_controller.getWindowBoundaryNodeVecVec(window_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &window_boundary_node_vec :
        window_boundary_node_vec_vec)
    {
        for(EasyNode* window_boundary_node : window_boundary_node_vec)
        {
            const EasyPolygon2D &window_boundary_polygon =
              window_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < window_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point =
                  window_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point =
                  window_boundary_polygon.point_list[
                  (i + 1) % window_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                window_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                window_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

                painter.drawLine(
                    zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                    zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawWindowSpaceBoundary(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(window_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song);

    painter.setPen(pen);

    if(window_brush_color_.red() != 0 ||
        window_brush_color_.green() != 0 ||
        window_brush_color_.blue() != 0)
    {
        QBrush brush;
        brush.setColor(window_brush_color_);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }

    std::vector<EasyNode*> window_space_node_vec;

    world_controller.getWindowSpaceNodeVec(window_space_node_vec);

    for(EasyNode* window_space_node : window_space_node_vec)
    {
        if(window_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &window_space_polygon =
          window_space_node->getBoundaryPolygon();

        QPolygon polygon;
        polygon.resize(window_space_polygon.point_list.size());

        for(size_t i = 0; i < window_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = window_space_polygon.point_list[i];

            EasyPoint2D current_point_in_world;
            window_space_node->getPointInWorld(
                current_point, current_point_in_world);

            polygon.setPoint(i, QPoint(
                  zoom_ * current_point_in_world.x,
                  zoom_ * current_point_in_world.y));
        }
        painter.drawPolygon(polygon);
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

    if(team_brush_color_.red() != 0 ||
        team_brush_color_.green() != 0 ||
        team_brush_color_.blue() != 0)
    {
        QBrush brush;
        brush.setColor(team_brush_color_);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }

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

        QPolygon polygon;
        polygon.resize(team_space_polygon.point_list.size());

        for(size_t i = 0; i < team_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = team_space_polygon.point_list[i];

            EasyPoint2D current_point_in_world;
            team_space_node->getPointInWorld(
                current_point, current_point_in_world);

            polygon.setPoint(i, QPoint(
                  zoom_ * current_point_in_world.x,
                  zoom_ * current_point_in_world.y));
        }
        painter.drawPolygon(polygon);
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

    if(furniture_brush_color_.red() != 0 ||
        furniture_brush_color_.green() != 0 ||
        furniture_brush_color_.blue() != 0)
    {
        QBrush brush;
        brush.setColor(furniture_brush_color_);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }

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

        QPolygon polygon;
        polygon.resize(furniture_space_polygon.point_list.size());

        for(size_t i = 0; i < furniture_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = furniture_space_polygon.point_list[i];

            EasyPoint2D current_point_in_world;
            furniture_space_node->getPointInWorld(
                current_point, current_point_in_world);

            polygon.setPoint(i, QPoint(
                  zoom_ * current_point_in_world.x,
                  zoom_ * current_point_in_world.y));
        }
        painter.drawPolygon(polygon);
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
