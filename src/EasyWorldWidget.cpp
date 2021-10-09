#include "EasyWorldWidget.h"
#include "qglobal.h"
#include "ui_EasyWorldWidget.h"

EasyWorldWidget::EasyWorldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EasyWorldWidget)
{
    ui->setupUi(this);

    axis_length_ = 20;

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
    world_controller_.reset();

    world_controller_.createWorld(400, 400);

    world_controller_.createWall(0, NodeType::OuterWall);

    EasyPolygon2D wall_boundary_polygon;
    wall_boundary_polygon.addPoint(0, 0);
    wall_boundary_polygon.addPoint(400, 0);
    wall_boundary_polygon.addPoint(400, 400);
    wall_boundary_polygon.addPoint(0, 400);
    wall_boundary_polygon.setAntiClockWise();

    world_controller_.setWallBoundaryPolygon(0, NodeType::OuterWall, wall_boundary_polygon);

    world_controller_.createRoom(0, NodeType::Room, 0, NodeType::OuterWall, 0);
    world_controller_.createRoom(1, NodeType::Room, 0, NodeType::OuterWall, 0);
    world_controller_.createRoom(2, NodeType::Room, 0, NodeType::OuterWall, 2);

    EasyPolygon2D room_boundary_polygon;
    room_boundary_polygon.addPoint(0, 0);
    room_boundary_polygon.addPoint(100, 0);
    room_boundary_polygon.addPoint(100, 100);
    room_boundary_polygon.addPoint(0, 100);
    room_boundary_polygon.setAntiClockWise();

    world_controller_.setRoomBoundaryPolygon(0, NodeType::Room, room_boundary_polygon);
    world_controller_.setRoomBoundaryPolygon(1, NodeType::Room, room_boundary_polygon);
    world_controller_.setRoomBoundaryPolygon(2, NodeType::Room, room_boundary_polygon);

    EasyPoint2D room_axis_center_position_in_parent;
    room_axis_center_position_in_parent.setPosition(101, 0);

    world_controller_.setRoomAxisCenterPositionInParent(1, NodeType::Room, room_axis_center_position_in_parent);

    world_controller_.createFurniture(0, NodeType::Furniture, 0, NodeType::Room);
    world_controller_.createFurniture(1, NodeType::Furniture, 1, NodeType::Room);
    world_controller_.createFurniture(2, NodeType::Furniture, 2, NodeType::Room);

    EasyPolygon2D furniture_boundary_polygon;
    furniture_boundary_polygon.addPoint(0, 0);
    furniture_boundary_polygon.addPoint(20, 0);
    furniture_boundary_polygon.addPoint(20, 10);
    furniture_boundary_polygon.addPoint(0, 10);
    furniture_boundary_polygon.setAntiClockWise();

    world_controller_.setFurnitureBoundaryPolygon(0, NodeType::Furniture, furniture_boundary_polygon);
    world_controller_.setFurnitureBoundaryPolygon(1, NodeType::Furniture, furniture_boundary_polygon);
    world_controller_.setFurnitureBoundaryPolygon(2, NodeType::Furniture, furniture_boundary_polygon);

    EasyPoint2D furniture_axis_center_position_in_parent;
    furniture_axis_center_position_in_parent.setPosition(40, 45);

    world_controller_.setFurnitureAxisCenterPositionInParent(0, NodeType::Furniture, furniture_axis_center_position_in_parent);
    world_controller_.setFurnitureAxisCenterPositionInParent(1, NodeType::Furniture, furniture_axis_center_position_in_parent);
    world_controller_.setFurnitureAxisCenterPositionInParent(2, NodeType::Furniture, furniture_axis_center_position_in_parent);

    // world_controller_.outputInfo();

    std::cout << "finish run_example!" << std::endl;
}

void EasyWorldWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    drawWallSpaceBoundary();
    // drawWallBoundaryPolygon();

    drawRoomSpaceBoundary();
    // drawRoomBoundaryPolygon();

    drawFurnitureSpaceBoundary();
    // drawFurnitureBoundaryPolygon();

    drawWallBoundaryAxis();
    drawRoomBoundaryAxis();
    drawFurnitureBoundaryAxis();
}

void EasyWorldWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void EasyWorldWidget::mouseMoveEvent(QMouseEvent *event)
{
    // moveRoomInWorld(0, NodeType::Room, event);

    moveFurnitureInWorld(0, NodeType::Furniture, event);
}

void EasyWorldWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
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
