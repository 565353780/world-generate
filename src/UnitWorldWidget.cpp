#include "UnitWorldWidget.h"
#include "qnamespace.h"
#include "ui_UnitWorldWidget.h"

UnitWorldWidget::UnitWorldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitWorldWidget)
{
    ui->setupUi(this);

    this->grabKeyboard();

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
    unit_world_controller_.createWall("Innerwall 0", 0, NodeType::InnerWall);

    float a = 18;
    float b = 10;
    size_t point_num = 100;

    EasyPolygon2D polygon;
    for(size_t i = 0; i < point_num; ++i)
    {
        polygon.addPoint(
            a * std::cos(2.0 * PI * i / point_num),
            b * std::sin(2.0 * PI * i / point_num));
    }
    unit_world_controller_.setWallBoundaryPolygon(0, NodeType::OuterWall, polygon);

    a = 11;
    b = 4;
    point_num = 50;
    polygon.reset();
    for(size_t i = 0; i < point_num; ++i)
    {
        polygon.addPoint(
            a * std::cos(2.0 * PI * i / point_num),
            b * std::sin(2.0 * PI * i / point_num));
    }
    unit_world_controller_.setWallBoundaryPolygon(0, InnerWall, polygon);

    zoom_ = 40;
    offset_x_ = 800;
    offset_y_ = 600;

    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;
    new_room_idx_ = 0;

    for(int i = -10; i < 10; i+=2)
    {
        unit_world_controller_.createRoom(
            "Room " + std::to_string(new_room_idx_),
            new_room_idx_, NodeType::WallRoom,
            0, NodeType::OuterWall);
        current_choose_node_id_ = new_room_idx_;
        current_choose_node_type_ = NodeType::WallRoom;
        ++new_room_idx_;

        EasyPoint2D mouse_position_in_world;

        mouse_position_in_world.setPosition(i, i);
        unit_world_controller_.setRoomPositionOnTreeByPosition(
            current_choose_node_id_,
            current_choose_node_type_,
            mouse_position_in_world);

        unit_world_controller_.unit_tree.updateNodePolygon(
            current_choose_node_id_,
            current_choose_node_type_);

        for(const EasyPoint2D& point :
            unit_world_controller_.unit_tree.findNode(current_choose_node_id_, current_choose_node_type_)->test_intersection_vec_)
        {
            test_intersection_vec_.emplace_back(point);
        }
    }

    // unit_world_controller_.unit_tree.setNodePositionOnParentPolygonByPosition(
        // current_choose_node_id_,
        // current_choose_node_type_,
        // mouse_position_in_world,
        // 0, 2, 2, PI / 2.0, PI / 2.0);

    // unit_world_controller_.unit_tree.updateNodePolygon(
        // current_choose_node_id_,
        // current_choose_node_type_);

    update();
}

void UnitWorldWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    drawBackGround();
    drawWall();
    drawRoom();

    QPainter painter(this);
    QPen pen(QColor(255, 0, 0), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    EasyPoint2D point;

    // for(int i = -10; i < 10; i+=2)
    // {
        // point.setPosition(i, i);
        // painter.drawPoint(getPointInImage(point));
    // }

    for(const EasyPoint2D& point : test_intersection_vec_)
    {
        painter.drawPoint(getPointInImage(point));
    }
}

void UnitWorldWidget::mousePressEvent(QMouseEvent *event)
{
    if(create_mode_ == CreateMode::CreateWall)
    {
        if(!chooseWall(event->pos()))
        {
        }
    }

    if(!chooseRoom(event->pos()))
    {
        unit_world_controller_.createRoom(
            "Room " + std::to_string(new_room_idx_),
            new_room_idx_, NodeType::WallRoom,
            0, NodeType::OuterWall);
        current_choose_node_id_ = new_room_idx_;
        current_choose_node_type_ = NodeType::WallRoom;
        ++new_room_idx_;

        EasyPoint2D mouse_position_in_world = getPointInWorld(event->pos());

        unit_world_controller_.setRoomPositionOnTreeByPosition(
            current_choose_node_id_,
            current_choose_node_type_,
            mouse_position_in_world);

        // unit_world_controller_.unit_tree.setNodePositionOnParentPolygonByPosition(
            // current_choose_node_id_,
            // current_choose_node_type_,
            // mouse_position_in_world,
            // 0, 2, 2, PI / 2.0, PI / 2.0);

        unit_world_controller_.unit_tree.updateNodePolygon(
            current_choose_node_id_,
            current_choose_node_type_);

        update();
    }
}

void UnitWorldWidget::mouseMoveEvent(QMouseEvent *event)
{
    return;
    EasyPoint2D mouse_position_in_world = getPointInWorld(event->pos());

    unit_world_controller_.setRoomPositionOnTreeByPosition(
        current_choose_node_id_,
        current_choose_node_type_,
        mouse_position_in_world);

    unit_world_controller_.unit_tree.updateNodePolygon(
        current_choose_node_id_,
        current_choose_node_type_);

    update();
}

void UnitWorldWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;
}

void UnitWorldWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F)
    {
        create_mode_ = CreateMode::CreateFree;
        std::cout << "Change to CreateFree Mode!\n";
        return;
    }

    if(event->key() == Qt::Key_W)
    {
        create_mode_ = CreateMode::CreateWall;
        std::cout << "Change to CreateWall Mode!\n";
        return;
    }

    if(event->key() == Qt::Key_R)
    {
        create_mode_ = CreateMode::CreateRoom;
        std::cout << "Change to CreateRoom Mode!\n";
        return;
    }
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

bool UnitWorldWidget::chooseWall(
    const QPoint& mouse_position_in_image)
{
    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;

    for(UnitNode* wall_node : unit_world_controller_.unit_tree.root->child_vec)
    {
        const EasyPoint2D mouse_position_in_world =
          getPointInWorld(mouse_position_in_image);
    }

    return true;
}

bool UnitWorldWidget::chooseRoom(
    const QPoint& mouse_position_in_image)
{
    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;

    for(UnitNode* wall_node : unit_world_controller_.unit_tree.root->child_vec)
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

    for(UnitNode* wall_node : unit_world_controller_.unit_tree.root->child_vec)
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

    painter.setPen(pen);

    for(UnitNode* wall_node : unit_world_controller_.unit_tree.root->child_vec)
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

            painter.drawPolygon(q_polygon);
        }
    }

    return true;
}

