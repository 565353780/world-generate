#include "UnitWorldWidget.h"
#include "ui_UnitWorldWidget.h"
#include <string>

UnitWorldWidget::UnitWorldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitWorldWidget)
{
    ui->setupUi(this);

    run_example();

    this->show();
}

UnitWorldWidget::~UnitWorldWidget()
{
    delete ui;
}

void UnitWorldWidget::run_example()
{
    unit_world_controller_.createWorld();

    unit_world_controller_.createWall("Outerwall 0", 0, NodeType::OuterWall);
    EasyPolygon2D polygon;
    polygon.addPoint(0, 0);
    polygon.addPoint(30, 0);
    polygon.addPoint(0, 30);
    unit_world_controller_.setBoundaryPolygon(0, NodeType::OuterWall, polygon);

    unit_world_controller_.createWall("Innerwall 0", 0, NodeType::InnerWall);
    polygon.reset();
    polygon.addPoint(8, 8);
    polygon.addPoint(14, 8);
    polygon.addPoint(8, 14);
    unit_world_controller_.setBoundaryPolygon(0, InnerWall, polygon);

    zoom_ = 20;
    offset_x_ = 100;
    offset_y_ = 100;

    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;
    new_room_idx_ = 0;
}

void UnitWorldWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    drawBackGround();
    drawWall();
    drawRoom();
}

void UnitWorldWidget::mousePressEvent(QMouseEvent *event)
{
    if(!chooseRoomContainer(event->pos()))
    {
        unit_world_controller_.createRoom(
            "Room " + std::to_string(new_room_idx_),
            new_room_idx_, NodeType::WallRoom,
            0, NodeType::OuterWall);
        current_choose_node_id_ = new_room_idx_;
        current_choose_node_type_ = NodeType::WallRoom;
        ++new_room_idx_;

        EasyPoint2D mouse_position_in_world = getPointInWorld(event->pos());

        unit_world_controller_.unit_tree_.setNodePositionOnParentPolygonByPosition(
            current_choose_node_id_,
            current_choose_node_type_,
            mouse_position_in_world,
            0, 5, 5, PI / 2.0, PI / 2.0);

        update();
    }
}

void UnitWorldWidget::mouseMoveEvent(QMouseEvent *event)
{
    EasyPoint2D mouse_position_in_world = getPointInWorld(event->pos());

    unit_world_controller_.unit_tree_.setNodePositionOnParentPolygonByPosition(
        current_choose_node_id_,
        current_choose_node_type_,
        mouse_position_in_world,
        0, 5, 5, PI / 2.0, PI / 2.0);

    update();
}

void UnitWorldWidget::mouseReleaseEvent(QMouseEvent *event)
{
    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;
}

QPoint UnitWorldWidget::getPointInImage(
    const EasyPoint2D& point_in_world)
{
    QPoint point_in_image = QPoint(
        offset_x_ + zoom_ * point_in_world.x,
        offset_y_ + zoom_ * point_in_world.y);

    return point_in_image;
}

EasyPoint2D UnitWorldWidget::getPointInWorld(
    const QPoint& point_in_image)
{
    EasyPoint2D point_in_world;
    point_in_world.setPosition(
        (point_in_image.x() - offset_x_) / zoom_,
        (point_in_image.y() - offset_y_) / zoom_);

    return point_in_world;
}

bool UnitWorldWidget::chooseRoomContainer(
    const QPoint& mouse_position_in_image)
{
    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;

    for(UnitNode* wall_node : unit_world_controller_.unit_tree_.root->child_vec)
    {
        for(UnitNode* room_node : wall_node->child_vec)
        {
            const EasyPoint2D mouse_position_in_world =
              getPointInWorld(mouse_position_in_image);

            if(EasyComputation::isPointInPolygon(
                  mouse_position_in_world,
                  room_node->boundary_polygon))
            {
                current_choose_node_id_ = room_node->id;
                current_choose_node_type_ = room_node->type;

                return true;
            }
        }
    }

    return false;
}

bool UnitWorldWidget::drawBackGround()
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0));

    QRect rect = QRect(0, 0, this->width(), this->height());
    painter.drawRect(rect);

    return true;
}

bool UnitWorldWidget::drawWall()
{
    QPainter painter(this);

    QPen pen(QColor(255, 255, 255), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    painter.setPen(pen);

    for(UnitNode* wall_node : unit_world_controller_.unit_tree_.root->child_vec)
    {
        const EasyPolygon2D& polygon = wall_node->boundary_polygon;

        QPolygon q_polygon;
        q_polygon.resize(polygon.point_list.size());

        for(size_t i = 0; i < polygon.point_list.size(); ++i)
        {
            const EasyPoint2D& polygon_point = polygon.point_list[i];
            q_polygon.setPoint(i, getPointInImage(polygon_point));
        }

        painter.drawPolygon(q_polygon);
    }

    return true;
}

bool UnitWorldWidget::drawRoom()
{
    QPainter painter(this);

    QPen pen(QColor(0, 255, 0), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_red(QColor(255, 0, 0), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_blue(QColor(0, 0, 255), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    painter.setPen(pen);

    for(UnitNode* wall_node : unit_world_controller_.unit_tree_.root->child_vec)
    {
        for(UnitNode* room_node : wall_node->child_vec)
        {
            const EasyPolygon2D& polygon = room_node->boundary_polygon;
            QPolygon q_polygon;
            q_polygon.resize(polygon.point_list.size());

            for(size_t i = 0; i < polygon.point_list.size(); ++i)
            {
                const EasyPoint2D& polygon_point = polygon.point_list[i];
                q_polygon.setPoint(i, getPointInImage(polygon_point));
            }

            painter.setPen(pen);
            painter.drawPolygon(q_polygon);

            painter.setPen(pen_red);
            for(const EasyIntersection2D& inter : room_node->intersection_vec_)
            {
                painter.drawPoint(getPointInImage(inter.point));
            }

            painter.setPen(pen_blue);
            painter.drawLine(
                getPointInImage(room_node->test_left_.point_1),
                getPointInImage(room_node->test_left_.point_2));
            painter.setPen(pen_red);
            painter.drawLine(
                getPointInImage(room_node->test_right_.point_1),
                getPointInImage(room_node->test_right_.point_2));
        }
    }

    return true;
}

