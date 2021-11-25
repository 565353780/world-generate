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

    background_color_ = QColor(0, 0, 0);
    outerwall_color_ = QColor(128,128,128);
    outerwall_brush_color_ = QColor(0,0,0);
    innerwall_color_ = QColor(128,128,128);
    innerwall_brush_color_ = QColor(0,0,0);
    roomcontainer_color_ = QColor(0, 0, 0);
    roomcontainer_brush_color_ = QColor(0, 0, 0);
    wallroom_color_ = QColor(128,128,128);
    wallroom_brush_color_ = QColor(0, 0, 0);
    freeroom_color_ = QColor(128,128,128);
    freeroom_brush_color_ = QColor(0, 0, 0);
    door_color_ = QColor(188,249,6);
    door_brush_color_ = QColor(188,249,6);
    window_color_ = QColor(8,205,206);
    window_brush_color_ = QColor(8,205,206);
    team_color_ = QColor(0, 0, 0);
    team_brush_color_ = QColor(0, 0, 0);
    person_color_ = QColor(0, 0, 0);
    person_brush_color_ = QColor(0, 0, 0);
    furniture_color_ = QColor(8,200,200);
    furniture_brush_color_ = QColor(0,0,0);
    length_color_ = QColor(153,114,0);
    text_color_ = QColor(255,255,0);

    current_choose_node_id_ = 0;
    current_choose_node_type_ = NodeType::NodeFree;

    run_example();
    
    this->show();
}

EasyWorldWidget::~EasyWorldWidget()
{
    delete ui;

    world_environment_.reset();
}

void EasyWorldWidget::run_example()
{
    zoom_ = 22;

    world_environment_.createNewWorld(2, 2);

    world_environment_.createOuterWall();
    world_environment_.createInnerWall();

    world_environment_.addPointForOuterWall(0, 0, 0);
    world_environment_.addPointForOuterWall(0, 41.173, 0);
    world_environment_.addPointForOuterWall(0, 41.173, 40.978);
    world_environment_.addPointForOuterWall(0, 0, 40.978);

    world_environment_.addPointForInnerWall(0, 10, 10);
    world_environment_.addPointForInnerWall(0, 30, 10);
    world_environment_.addPointForInnerWall(0, 30, 30);
    world_environment_.addPointForInnerWall(0, 10, 30);

    world_environment_.generateWall();

    world_environment_.placeOuterWallRoomContainer(0, 0, 0, 6.935, 16.169, 1);
    world_environment_.placeOuterWallRoomContainer(0, 0, 6.935, 6.139, 7.965, 1);
    world_environment_.placeOuterWallRoomContainer(0, 0, 13.074, 2.833, 7.965, 1);
    world_environment_.placeOuterWallRoomContainer(0, 0, 15.907, 3.028, 7.965, 1);
    world_environment_.placeOuterWallRoomContainer(0, 0, 18.935, 4.396, 7.965, 1);
    world_environment_.placeOuterWallRoomContainer(0, 0, 23.331, 3.726, 5.608, 1);
    world_environment_.placeOuterWallRoomContainer(0, 1, 0, 6.740, 6.935, 1);
    world_environment_.placeOuterWallRoomContainer(0, 1, 6.740, 11.969, 11.720, 1);
    world_environment_.placeOuterWallRoomContainer(0, 1, 18.709, 3.321, 7.769, 1);
    world_environment_.placeOuterWallRoomContainer(0, 1, 22.03, 4.197, 5.522, 1);
    world_environment_.placeOuterWallRoomContainer(0, 1, 26.227, 3.528, 5.522, 1);
    world_environment_.placeOuterWallRoomContainer(0, 2, 0, 5.665, 7.965, 1);
    world_environment_.placeOuterWallRoomContainer(0, 2, 5.665, 7.867, 7.965, 1);
    world_environment_.placeOuterWallRoomContainer(0, 2, 13.532, 4.057, 7.965, 1);
    world_environment_.placeOuterWallRoomContainer(0, 2, 17.589, 2.833, 9.385, 1);
    world_environment_.placeOuterWallRoomContainer(0, 2, 20.422, 3.862, 5.621, 1);
    world_environment_.placeOuterWallRoomContainer(0, 2, 24.284, 4.058, 5.621, 1);
    world_environment_.placeOuterWallRoomContainer(0, 3, 20.023, 4.546, 11.774, 1);

    world_environment_.generateFreeRoomContainer(4, 4, 0.5, 2);

    update();

    // long cycle_num = 0;
    // float avg_fps = 0;
    // setStartTime();
    // while(true)
    // {
        // world_environment_.resetButRemainWall();
        // world_environment_.placeOuterWallRoomContainer(0, std::rand() % 4, std::rand() % 22, 4, 4, 1);
        // world_environment_.placeOuterWallRoomContainer(0, std::rand() % 4, std::rand() % 12, 12, 4, 3);
        // world_environment_.placeInnerWallRoomContainer(0, std::rand() % 4, std::rand() % 22, 4, 4, 1);
        // world_environment_.placeInnerWallRoomContainer(0, std::rand() % 4, std::rand() % 22, 4, 4, 1);
        // world_environment_.generateFreeRoomContainer(4, 4, 0.5, 2);
        // ++cycle_num;
        // getFPS(cycle_num, avg_fps);
        // std::cout << "fps = " << size_t(avg_fps) << std::endl;
    // }

    // world_controller_.outputInfo();

    std::cout << "finish run_example!" << std::endl;
}

void EasyWorldWidget::paintEvent(QPaintEvent *event)
{
    paintWorld(world_environment_.world_controller_, event);
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
        // world_environment_.generateWorld(world_controller_);

        world_environment_.resetButRemainWall();

        world_environment_.placeOuterWallRoomContainer(0, std::rand() % 4, std::rand() % 22, 4, 4, 1);
        world_environment_.placeOuterWallRoomContainer(0, std::rand() % 4, std::rand() % 12, 12, 4, 3);
        world_environment_.placeInnerWallRoomContainer(0, std::rand() % 4, std::rand() % 22, 4, 4, 1);
        world_environment_.placeInnerWallRoomContainer(0, std::rand() % 4, std::rand() % 22, 4, 4, 1);
        world_environment_.generateFreeRoomContainer(4, 4, 0.5, 2);
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

    world_environment_.world_controller_.getRoomContainerSpaceNodeVec(
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

        world_environment_.setWallRoomContainerPosition(
            wall_roomcontainer_id,
            new_position_x,
            new_position_y,
            current_press_position_to_start_position);

        update();
    }

    return true;
}

bool EasyWorldWidget::drawBackGround()
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(background_color_);

    QRect rect = QRect(0, 0, this->width(), this->height());
    painter.drawRect(rect);

    return true;
}

bool EasyWorldWidget::drawOuterWallBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

    std::vector<std::vector<EasyNode*>> outerwall_boundary_node_vec_vec;

    world_controller.getOuterWallBoundaryNodeVecVec(outerwall_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& outerwall_boundary_node_vec: outerwall_boundary_node_vec_vec)
    {
        for(const EasyNode* outerwall_boundary_node : outerwall_boundary_node_vec)
        {
            if(outerwall_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D outerwall_boundary_axis = outerwall_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                zoom_ * outerwall_boundary_axis.center_.x, zoom_ * outerwall_boundary_axis.center_.y,
                zoom_ * (outerwall_boundary_axis.center_.x + axis_length_ * outerwall_boundary_axis.x_direction_.x),
                zoom_ * (outerwall_boundary_axis.center_.y + axis_length_ * outerwall_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * outerwall_boundary_axis.center_.x, zoom_ * outerwall_boundary_axis.center_.y,
                zoom_ * (outerwall_boundary_axis.center_.x + axis_length_ * outerwall_boundary_axis.y_direction_.x),
                zoom_ * (outerwall_boundary_axis.center_.y + axis_length_ * outerwall_boundary_axis.y_direction_.y));
        }
        
    }
    
    return true;
}

bool EasyWorldWidget::drawOuterWallBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(outerwall_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> outerwall_boundary_node_vec_vec;

    world_controller.getOuterWallBoundaryNodeVecVec(outerwall_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &outerwall_boundary_node_vec :
        outerwall_boundary_node_vec_vec)
    {
        for(EasyNode* outerwall_boundary_node : outerwall_boundary_node_vec)
        {
            const EasyPolygon2D &outerwall_boundary_polygon =
              outerwall_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < outerwall_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point = outerwall_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point = outerwall_boundary_polygon.point_list[
                  (i + 1) % outerwall_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                outerwall_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                outerwall_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

            painter.drawLine(
                zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawOuterWallSpaceBoundary()
{
    QPainter painter(this);

    QPen pen(outerwall_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_line(length_color_, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_text(text_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);
    QFont font_song_10("宋体", 10, QFont::Bold, true);

    painter.setPen(pen);

    if(outerwall_brush_color_.red() != 0 ||
        outerwall_brush_color_.green() != 0 ||
        outerwall_brush_color_.blue() != 0)
    {
        QBrush brush;
        brush.setColor(outerwall_brush_color_);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }

    const std::vector<std::vector<std::vector<float>>> outerwall_boundary_data_vec =
      world_environment_.getOuterWallBoundaryDataVec();

    for(const std::vector<std::vector<float>>& outerwall_boundary_data : outerwall_boundary_data_vec)
    {
        if(outerwall_boundary_data.size() == 0)
        {
            continue;
        }

        QPolygon polygon;
        polygon.resize(outerwall_boundary_data.size());

        const float line_info_dist = 20;

        for(size_t i = 0; i < outerwall_boundary_data.size(); ++i)
        {
            const size_t next_point_idx = (i + 1) % outerwall_boundary_data.size();

            const float current_point_x = outerwall_boundary_data[i][0];
            const float current_point_y = outerwall_boundary_data[i][1];
            const float next_point_x = outerwall_boundary_data[next_point_idx][0];
            const float next_point_y = outerwall_boundary_data[next_point_idx][1];

            polygon.setPoint(i, QPoint(
                  zoom_ * current_point_x,
                  zoom_ * current_point_y));

            const float line_x_diff = next_point_x - current_point_x;
            const float line_y_diff = next_point_y - current_point_y;

            const float line_length = std::sqrt(
                line_x_diff * line_x_diff +
                line_y_diff * line_y_diff);

            EasyPoint2D move_direction;
            move_direction.setPosition(
                line_y_diff / line_length,
                -line_x_diff / line_length);

            EasyPoint2D current_point_move;
            EasyPoint2D next_point_move;
            current_point_move.setPosition(
                zoom_ * current_point_x + line_info_dist * move_direction.x,
                zoom_ * current_point_y + line_info_dist * move_direction.y);
            next_point_move.setPosition(
                zoom_ * next_point_x + line_info_dist * move_direction.x,
                zoom_ * next_point_y + line_info_dist * move_direction.y);

            painter.setPen(pen_line);
            painter.drawLine(
                current_point_move.x,
                current_point_move.y,
                next_point_move.x,
                next_point_move.y);

            painter.setPen(pen_text);
            painter.setFont(font_song_10);
            painter.drawText(
                (current_point_move.x + next_point_move.x) / 2.0,
                (current_point_move.y + next_point_move.y) / 2.0,
                QString::number(line_length));
        }

        painter.setPen(pen);
        painter.drawPolygon(polygon);
    }

    return true;
}

bool EasyWorldWidget::drawInnerWallBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

    std::vector<std::vector<EasyNode*>> innerwall_boundary_node_vec_vec;

    world_controller.getInnerWallBoundaryNodeVecVec(innerwall_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& innerwall_boundary_node_vec: innerwall_boundary_node_vec_vec)
    {
        for(const EasyNode* innerwall_boundary_node : innerwall_boundary_node_vec)
        {
            if(innerwall_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D innerwall_boundary_axis = innerwall_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                zoom_ * innerwall_boundary_axis.center_.x, zoom_ * innerwall_boundary_axis.center_.y,
                zoom_ * (innerwall_boundary_axis.center_.x + axis_length_ * innerwall_boundary_axis.x_direction_.x),
                zoom_ * (innerwall_boundary_axis.center_.y + axis_length_ * innerwall_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * innerwall_boundary_axis.center_.x, zoom_ * innerwall_boundary_axis.center_.y,
                zoom_ * (innerwall_boundary_axis.center_.x + axis_length_ * innerwall_boundary_axis.y_direction_.x),
                zoom_ * (innerwall_boundary_axis.center_.y + axis_length_ * innerwall_boundary_axis.y_direction_.y));
        }
        
    }
    
    return true;
}

bool EasyWorldWidget::drawInnerWallBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(innerwall_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> innerwall_boundary_node_vec_vec;

    world_controller.getInnerWallBoundaryNodeVecVec(innerwall_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &innerwall_boundary_node_vec :
        innerwall_boundary_node_vec_vec)
    {
        for(EasyNode* innerwall_boundary_node : innerwall_boundary_node_vec)
        {
            const EasyPolygon2D &innerwall_boundary_polygon =
              innerwall_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < innerwall_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point = innerwall_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point = innerwall_boundary_polygon.point_list[
                  (i + 1) % innerwall_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                innerwall_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                innerwall_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

            painter.drawLine(
                zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawInnerWallSpaceBoundary()
{
    QPainter painter(this);

    QPen pen(innerwall_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_line(length_color_, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_text(text_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);
    QFont font_song_10("宋体", 10, QFont::Bold, true);

    painter.setPen(pen);

    if(innerwall_brush_color_.red() != 0 ||
        innerwall_brush_color_.green() != 0 ||
        innerwall_brush_color_.blue() != 0)
    {
        QBrush brush;
        brush.setColor(innerwall_brush_color_);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }

    const std::vector<std::vector<std::vector<float>>> innerwall_boundary_data_vec =
      world_environment_.getInnerWallBoundaryDataVec();

    for(const std::vector<std::vector<float>>& innerwall_boundary_data : innerwall_boundary_data_vec)
    {
        if(innerwall_boundary_data.size() == 0)
        {
            continue;
        }

        QPolygon polygon;
        polygon.resize(innerwall_boundary_data.size());

        const float line_info_dist = 20;

        for(size_t i = 0; i < innerwall_boundary_data.size(); ++i)
        {
            const size_t next_point_idx = (i + 1) % innerwall_boundary_data.size();

            const float current_point_x = innerwall_boundary_data[i][0];
            const float current_point_y = innerwall_boundary_data[i][1];
            const float next_point_x = innerwall_boundary_data[next_point_idx][0];
            const float next_point_y = innerwall_boundary_data[next_point_idx][1];

            polygon.setPoint(i, QPoint(
                  zoom_ * current_point_x,
                  zoom_ * current_point_y));

            const float line_x_diff = next_point_x - current_point_x;
            const float line_y_diff = next_point_y - current_point_y;

            const float line_length = std::sqrt(
                line_x_diff * line_x_diff +
                line_y_diff * line_y_diff);

            EasyPoint2D move_direction;
            move_direction.setPosition(
                line_y_diff / line_length,
                -line_x_diff / line_length);

            EasyPoint2D current_point_move;
            EasyPoint2D next_point_move;
            current_point_move.setPosition(
                zoom_ * current_point_x + line_info_dist * move_direction.x,
                zoom_ * current_point_y + line_info_dist * move_direction.y);
            next_point_move.setPosition(
                zoom_ * next_point_x + line_info_dist * move_direction.x,
                zoom_ * next_point_y + line_info_dist * move_direction.y);

            painter.setPen(pen_line);
            painter.drawLine(
                current_point_move.x,
                current_point_move.y,
                next_point_move.x,
                next_point_move.y);

            painter.setPen(pen_text);
            painter.setFont(font_song_10);
            painter.drawText(
                (current_point_move.x + next_point_move.x) / 2.0,
                (current_point_move.y + next_point_move.y) / 2.0,
                QString::number(line_length));
        }

        painter.setPen(pen);
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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

bool EasyWorldWidget::drawWallRoomBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

    std::vector<std::vector<EasyNode*>> wallroom_boundary_node_vec_vec;

    world_controller.getWallRoomBoundaryNodeVecVec(wallroom_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& wallroom_boundary_node_vec: wallroom_boundary_node_vec_vec)
    {
        for(const EasyNode* wallroom_boundary_node : wallroom_boundary_node_vec)
        {
            if(wallroom_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D wallroom_boundary_axis = wallroom_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                zoom_ * wallroom_boundary_axis.center_.x, zoom_ * wallroom_boundary_axis.center_.y,
                zoom_ * (wallroom_boundary_axis.center_.x + axis_length_ * wallroom_boundary_axis.x_direction_.x),
                zoom_ * (wallroom_boundary_axis.center_.y + axis_length_ * wallroom_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * wallroom_boundary_axis.center_.x, zoom_ * wallroom_boundary_axis.center_.y,
                zoom_ * (wallroom_boundary_axis.center_.x + axis_length_ * wallroom_boundary_axis.y_direction_.x),
                zoom_ * (wallroom_boundary_axis.center_.y + axis_length_ * wallroom_boundary_axis.y_direction_.y));
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawWallRoomBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(wallroom_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> wallroom_boundary_node_vec_vec;

    world_controller.getWallRoomBoundaryNodeVecVec(wallroom_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &wallroom_boundary_node_vec :
        wallroom_boundary_node_vec_vec)
    {
        for(EasyNode* wallroom_boundary_node : wallroom_boundary_node_vec)
        {
            const EasyPolygon2D &wallroom_boundary_polygon =
              wallroom_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < wallroom_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point =
                  wallroom_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point =
                  wallroom_boundary_polygon.point_list[
                  (i + 1) % wallroom_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                wallroom_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                wallroom_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

                painter.drawLine(
                    zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                    zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawWallRoomSpaceBoundary(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(wallroom_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_line(length_color_, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_text(text_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QFont font_song_15("宋体", 15, QFont::Bold, true);
    painter.setFont(font_song_15);
    QFont font_song_10("宋体", 10, QFont::Bold, true);

    painter.setPen(pen);

    if(wallroom_brush_color_.red() != 0 ||
        wallroom_brush_color_.green() != 0 ||
        wallroom_brush_color_.blue() != 0)
    {
        QBrush brush;
        brush.setColor(wallroom_brush_color_);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }

    std::vector<EasyNode*> wallroom_space_node_vec;

    world_controller.getWallRoomSpaceNodeVec(wallroom_space_node_vec);

    for(EasyNode* wallroom_space_node : wallroom_space_node_vec)
    {
        if(wallroom_space_node == nullptr)
        {
            continue;
        }

        const QString wallroom_name = QString(wallroom_space_node->getParent()->getName().c_str());

        const EasyPolygon2D &wallroom_space_polygon =
          wallroom_space_node->getBoundaryPolygon();

        const QString wallroom_area = QString::number(
            wallroom_space_polygon.point_list[2].x *
            wallroom_space_polygon.point_list[2].y) + " m^2";

        float point_x_sum = 0;
        float point_y_sum = 0;

        QPolygon polygon;
        polygon.resize(wallroom_space_polygon.point_list.size());

        const float line_info_dist = 5;

        for(size_t i = 0; i < wallroom_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = wallroom_space_polygon.point_list[i];

            EasyPoint2D current_point_in_world;
            wallroom_space_node->getPointInWorld(
                current_point, current_point_in_world);

            point_x_sum += current_point_in_world.x;
            point_y_sum += current_point_in_world.y;

            polygon.setPoint(i, QPoint(
                  zoom_ * current_point_in_world.x,
                  zoom_ * current_point_in_world.y));

            const EasyPoint2D &next_point = wallroom_space_polygon.point_list[
              (i+1) % wallroom_space_polygon.point_list.size()];

            EasyPoint2D next_point_in_world;
            wallroom_space_node->getPointInWorld(
                next_point, next_point_in_world);

            const float line_x_diff =
              next_point_in_world.x - current_point_in_world.x;
            const float line_y_diff =
              next_point_in_world.y - current_point_in_world.y;

            const float line_length = std::sqrt(
                line_x_diff * line_x_diff +
                line_y_diff * line_y_diff);

            EasyPoint2D move_direction;
            move_direction.setPosition(
                -line_y_diff / line_length,
                line_x_diff / line_length);

            EasyPoint2D current_point_move;
            EasyPoint2D next_point_move;
            current_point_move.setPosition(
                zoom_ * current_point_in_world.x + line_info_dist * move_direction.x,
                zoom_ * current_point_in_world.y + line_info_dist * move_direction.y);
            next_point_move.setPosition(
                zoom_ * next_point_in_world.x + line_info_dist * move_direction.x,
                zoom_ * next_point_in_world.y + line_info_dist * move_direction.y);

            painter.setPen(pen_line);
            painter.drawLine(
                current_point_move.x,
                current_point_move.y,
                next_point_move.x,
                next_point_move.y);

            painter.setPen(pen_text);
            painter.setFont(font_song_10);
            painter.drawText(
                (current_point_move.x + next_point_move.x) / 2.0 + 10 * move_direction.x,
                (current_point_move.y + next_point_move.y) / 2.0 + 10 * move_direction.y,
                QString::number(line_length));
        }
        painter.setPen(pen);
        painter.drawPolygon(polygon);

        QPoint center_point = QPoint(
            zoom_ * point_x_sum / wallroom_space_polygon.point_list.size(),
            zoom_ * point_y_sum / wallroom_space_polygon.point_list.size());

        painter.setPen(pen_text);
        painter.setFont(font_song_15);
        painter.drawText(center_point, wallroom_name);
        painter.setFont(font_song_10);
        painter.drawText(center_point + QPoint(-5, 15), wallroom_area);
    }

    return true;
}

bool EasyWorldWidget::drawFreeRoomBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

    std::vector<std::vector<EasyNode*>> freeroom_boundary_node_vec_vec;

    world_controller.getFreeRoomBoundaryNodeVecVec(freeroom_boundary_node_vec_vec);

    for(const std::vector<EasyNode*>& freeroom_boundary_node_vec: freeroom_boundary_node_vec_vec)
    {
        for(const EasyNode* freeroom_boundary_node : freeroom_boundary_node_vec)
        {
            if(freeroom_boundary_node == nullptr)
            {
                continue;
            }

            EasyAxis2D freeroom_boundary_axis = freeroom_boundary_node->getAxisInWorld();

            painter.setPen(pen_red);

            painter.drawLine(
                zoom_ * freeroom_boundary_axis.center_.x, zoom_ * freeroom_boundary_axis.center_.y,
                zoom_ * (freeroom_boundary_axis.center_.x + axis_length_ * freeroom_boundary_axis.x_direction_.x),
                zoom_ * (freeroom_boundary_axis.center_.y + axis_length_ * freeroom_boundary_axis.x_direction_.y));

            painter.setPen(pen_green);

            painter.drawLine(
                zoom_ * freeroom_boundary_axis.center_.x, zoom_ * freeroom_boundary_axis.center_.y,
                zoom_ * (freeroom_boundary_axis.center_.x + axis_length_ * freeroom_boundary_axis.y_direction_.x),
                zoom_ * (freeroom_boundary_axis.center_.y + axis_length_ * freeroom_boundary_axis.y_direction_.y));
        }
        
    }
    return true;
}

bool EasyWorldWidget::drawFreeRoomBoundaryPolygon(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(freeroom_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

    painter.setPen(pen);

    std::vector<std::vector<EasyNode*>> freeroom_boundary_node_vec_vec;

    world_controller.getFreeRoomBoundaryNodeVecVec(freeroom_boundary_node_vec_vec);

    for(const std::vector<EasyNode*> &freeroom_boundary_node_vec :
        freeroom_boundary_node_vec_vec)
    {
        for(EasyNode* freeroom_boundary_node : freeroom_boundary_node_vec)
        {
            const EasyPolygon2D &freeroom_boundary_polygon =
              freeroom_boundary_node->getBoundaryPolygon();

            for(size_t i = 0; i < freeroom_boundary_polygon.point_list.size(); ++i)
            {
                const EasyPoint2D &current_point =
                  freeroom_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point =
                  freeroom_boundary_polygon.point_list[
                  (i + 1) % freeroom_boundary_polygon.point_list.size()];

                EasyPoint2D current_point_in_world;
                EasyPoint2D next_point_in_world;
                freeroom_boundary_node->getPointInWorld(
                    current_point, current_point_in_world);
                freeroom_boundary_node->getPointInWorld(
                    next_point, next_point_in_world);

                painter.drawLine(
                    zoom_ * current_point_in_world.x, zoom_ * current_point_in_world.y,
                    zoom_ * next_point_in_world.x, zoom_ * next_point_in_world.y);
            }
        }
    }

    return true;
}

bool EasyWorldWidget::drawFreeRoomSpaceBoundary(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen(freeroom_color_, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_line(length_color_, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_text(text_color_, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QFont font_song_15("宋体", 15, QFont::Bold, true);
    painter.setFont(font_song_15);
    QFont font_song_10("宋体", 10, QFont::Bold, true);

    painter.setPen(pen);

    if(freeroom_brush_color_.red() != 0 ||
        freeroom_brush_color_.green() != 0 ||
        freeroom_brush_color_.blue() != 0)
    {
        QBrush brush;
        brush.setColor(freeroom_brush_color_);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }

    std::vector<EasyNode*> freeroom_space_node_vec;

    world_controller.getFreeRoomSpaceNodeVec(freeroom_space_node_vec);

    for(EasyNode* freeroom_space_node : freeroom_space_node_vec)
    {
        if(freeroom_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &freeroom_space_polygon =
          freeroom_space_node->getBoundaryPolygon();

        const QString freeroom_area = QString::number(
            freeroom_space_polygon.point_list[2].x *
            freeroom_space_polygon.point_list[2].y) + " m^2";

        float point_x_sum = 0;
        float point_y_sum = 0;

        QPolygon polygon;
        polygon.resize(freeroom_space_polygon.point_list.size());

        const float line_info_dist = 5;

        for(size_t i = 0; i < freeroom_space_polygon.point_list.size(); ++i)
        {
            const EasyPoint2D &current_point = freeroom_space_polygon.point_list[i];

            EasyPoint2D current_point_in_world;
            freeroom_space_node->getPointInWorld(
                current_point, current_point_in_world);

            point_x_sum += current_point_in_world.x;
            point_y_sum += current_point_in_world.y;

            polygon.setPoint(i, QPoint(
                  zoom_ * current_point_in_world.x,
                  zoom_ * current_point_in_world.y));

            const EasyPoint2D &next_point = freeroom_space_polygon.point_list[
              (i+1) % freeroom_space_polygon.point_list.size()];

            EasyPoint2D next_point_in_world;
            freeroom_space_node->getPointInWorld(
                next_point, next_point_in_world);

            const float line_x_diff =
              next_point_in_world.x - current_point_in_world.x;
            const float line_y_diff =
              next_point_in_world.y - current_point_in_world.y;

            const float line_length = std::sqrt(
                line_x_diff * line_x_diff +
                line_y_diff * line_y_diff);

            EasyPoint2D move_direction;
            move_direction.setPosition(
                -line_y_diff / line_length,
                line_x_diff / line_length);

            EasyPoint2D current_point_move;
            EasyPoint2D next_point_move;
            current_point_move.setPosition(
                zoom_ * current_point_in_world.x + line_info_dist * move_direction.x,
                zoom_ * current_point_in_world.y + line_info_dist * move_direction.y);
            next_point_move.setPosition(
                zoom_ * next_point_in_world.x + line_info_dist * move_direction.x,
                zoom_ * next_point_in_world.y + line_info_dist * move_direction.y);

            painter.setPen(pen_line);
            painter.drawLine(
                current_point_move.x,
                current_point_move.y,
                next_point_move.x,
                next_point_move.y);

            painter.setPen(pen_text);
            painter.setFont(font_song_10);
            painter.drawText(
                (current_point_move.x + next_point_move.x) / 2.0 + 10 * move_direction.x,
                (current_point_move.y + next_point_move.y) / 2.0 + 10 * move_direction.y,
                QString::number(line_length));
        }
        painter.setPen(pen);
        painter.drawPolygon(polygon);

        QPoint center_point = QPoint(
            zoom_ * point_x_sum / freeroom_space_polygon.point_list.size(),
            zoom_ * point_y_sum / freeroom_space_polygon.point_list.size());

        painter.setPen(pen_text);
        painter.setFont(font_song_10);
        painter.drawText(center_point + QPoint(-5, 15), freeroom_area);
    }

    return true;
}

bool EasyWorldWidget::drawDoorBoundaryAxis(
    WorldController &world_controller)
{
    QPainter painter(this);

    QPen pen_red(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_green(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

    QPen pen(furniture_color_, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // QFont font_song_15("宋体", 15, QFont::Bold, true);
    // painter.setFont(font_song_15);

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

bool EasyWorldWidget::paintWorld(
    WorldController &world_controller,
    QPaintEvent *event)
{
    Q_UNUSED(event);

    drawBackGround();

    drawOuterWallSpaceBoundary();
    drawInnerWallSpaceBoundary();
    // drawRoomContainerSpaceBoundary(world_controller);
    drawWallRoomSpaceBoundary(world_controller);
    drawFreeRoomSpaceBoundary(world_controller);
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
