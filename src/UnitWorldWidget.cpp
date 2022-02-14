#include "UnitWorldWidget.h"
#include "qnamespace.h"
#include "ui_UnitWorldWidget.h"

UnitWorldWidget::UnitWorldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitWorldWidget)
{
    ui->setupUi(this);

    this->grabKeyboard();

    this->setFixedSize(1400, 700);

    run_example();

    this->show();
}

UnitWorldWidget::~UnitWorldWidget()
{
    delete ui;
}

void UnitWorldWidget::run_example()
{
    unit_world_environment_.setImageSize(this->width(), this->height(), 20);

    unit_world_environment_.createNewWorld();

    unit_world_environment_.createOuterWall();
    unit_world_environment_.createInnerWall();

    float a = 18;
    float b = 10;
    size_t point_num = 100;

    for(size_t i = 0; i < point_num; ++i)
    {
        unit_world_environment_.addPointForOuterWall(
            0,
            a * std::cos(2.0 * PI * i / point_num),
            b * std::sin(2.0 * PI * i / point_num));
    }

    a = 11;
    b = 4;
    point_num = 50;
    for(size_t i = 0; i < point_num; ++i)
    {
        unit_world_environment_.addPointForInnerWall(
            0,
            a * std::cos(2.0 * PI * i / point_num),
            b * std::sin(2.0 * PI * i / point_num));
    }

    unit_world_environment_.generateWall();

    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;
    new_room_idx_ = 0;

    update();
}

void UnitWorldWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    drawBackGround();

    drawNode(unit_world_environment_.getOuterWallBoundaryDataVec(), QColor(255, 255, 255));
    drawNode(unit_world_environment_.getInnerWallBoundaryDataVec(), QColor(255, 255, 255));
    drawNode(unit_world_environment_.getWallRoomBoundaryDataVec(), QColor(0, 255, 0));
}

void UnitWorldWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(!chooseRoom(event->pos()))
        {
            unit_world_environment_.placeWallRoomByPosition(
                event->pos().x(),
                event->pos().y(),
                2, 2);

            current_choose_node_id_ = new_room_idx_;
            current_choose_node_type_ = NodeType::WallRoom;

            ++new_room_idx_;

            update();
        }
    }
    else if(event->button() == Qt::RightButton)
    {
      unit_world_environment_.resetButRemainWall();
      new_room_idx_ = 0;

      update();
    }
}

void UnitWorldWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(current_choose_node_type_ == NodeType::WallRoom)
    {
        unit_world_environment_.setWallRoomPositionByPosition(
            current_choose_node_id_,
            event->pos().x(),
            event->pos().y(),
            2, 2);

        unit_world_environment_.outputParamLine();
    }

    update();
}

void UnitWorldWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;
}

bool UnitWorldWidget::chooseRoom(
    const QPoint& mouse_position_in_image)
{
    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;

    for(UnitNode* wall_node : unit_world_environment_.unit_world_controller_.unit_tree.root->child_vec)
    {
        for(UnitNode* room_node : wall_node->child_vec)
        {
            float mouse_position_x_in_world, mouse_position_y_in_world;
            unit_world_environment_.unit_world_transformer_.transPointToWorld(
                mouse_position_in_image.x(), mouse_position_in_image.y(),
                mouse_position_x_in_world, mouse_position_y_in_world);

            EasyPoint2D mouse_position_in_world;
            mouse_position_in_world.setPosition(mouse_position_x_in_world, mouse_position_y_in_world);

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

bool UnitWorldWidget::drawNode(
    const std::vector<std::vector<std::vector<size_t>>>& node_boundary_data_vec,
    const QColor color)
{
    QPainter painter(this);
    QPen pen(color, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    for(const std::vector<std::vector<size_t>>& node_boundary_data :
        node_boundary_data_vec)
    {
        QPolygon q_polygon;
        q_polygon.resize(node_boundary_data.size());

        for(size_t i = 0; i < node_boundary_data.size(); ++i)
        {
            const std::vector<size_t>& node_boundary_point_data =
              node_boundary_data[i];

            q_polygon.setPoint(
                i, node_boundary_point_data[0], node_boundary_point_data[1]);
        }

        painter.drawPolygon(q_polygon);
    }

    return true;
}

