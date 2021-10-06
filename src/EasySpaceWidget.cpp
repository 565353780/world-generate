#include "EasySpaceWidget.h"
#include "qglobal.h"
#include "ui_EasySpaceWidget.h"

EasySpaceWidget::EasySpaceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EasySpaceWidget)
{
    ui->setupUi(this);

    // run_example();
    
    this->show();
}

EasySpaceWidget::~EasySpaceWidget()
{
    delete ui;
}

void EasySpaceWidget::run_example()
{
    // 0 : AnHui Applicated Center
    // 1 : Rebuild Demo
    // 2 : Rebuild Demo reset room position speed test // offline 130w fps render 700 fps
    // 3 : Rebuild Demo all process speed test // offline 56w fps render 700 fps
    size_t demo_mode = 3;

    long cycle_num = 0;
    float average_fps = 0;

    SpaceController space_controller;

    switch(demo_mode)
    {
    case 0:
        space_controller.createBoundary("Outer Wall");
        space_controller.setOuterBoundary(0);

        space_controller.addBoundaryPoint(0, 0, 0);
        space_controller.addBoundaryPoint(0, 400, 0);
        space_controller.addBoundaryPoint(0, 400, 200);
        space_controller.addBoundaryPoint(0, 160, 200);
        space_controller.addBoundaryPoint(0, 160, 400);
        space_controller.addBoundaryPoint(0, 400, 400);
        space_controller.addBoundaryPoint(0, 400, 800);
        space_controller.addBoundaryPoint(0, 0, 800);

        space_controller.updateBoundary();

        space_controller.createRoom("Meeting Room");
        space_controller.setRoomSize(0, 100, 100);
        space_controller.createRoom("Gaming Room");
        space_controller.setRoomSize(1, 100, 100);
        space_controller.createRoom("Manager Department");
        space_controller.setRoomSize(2, 100, 100);
        space_controller.createRoom("Manager Department");
        space_controller.setRoomSize(3, 100, 100);
        space_controller.createRoom("Gaming Room");
        space_controller.setRoomSize(4, 100, 100);
        space_controller.createRoom("Meeting Room");
        space_controller.setRoomSize(5, 100, 100);

        space_controller.setRoomNeighboor(0, 1);
        space_controller.setRoomNeighboor(1, 2);
        space_controller.setRoomNeighboor(0, 2);

        space_controller.setRoomNeighboor(3, 4);
        space_controller.setRoomNeighboor(4, 5);

        space_controller.updateRoomConnection();

        space_controller.setRoomBoundaryPointParam(0, 0, 0, 0);
        space_controller.setRoomBoundaryPointParam(4, 0, 6, 0);

        space_controller.updateRoom();

        space_controller.showSpace(0);

        break;
    case 1:
        space_controller.createBoundary("Outer Wall");
        space_controller.setOuterBoundary(0);

        space_controller.addBoundaryPoint(0, 0, 0);
        space_controller.addBoundaryPoint(0, 400, 0);
        space_controller.addBoundaryPoint(0, 400, 400);
        space_controller.addBoundaryPoint(0, 0, 400);

        space_controller.updateBoundary();

        space_controller.createRoom("MR 1");
        space_controller.setRoomSize(0, 100, 70);
        space_controller.createRoom("MR 2");
        space_controller.setRoomSize(1, 100, 70);
        space_controller.createRoom("MR 3");
        space_controller.setRoomSize(2, 100, 80);

        space_controller.setRoomNeighboor(0, 1);
        space_controller.setRoomNeighboor(1, 2);

        space_controller.createRoom("MR 4");
        space_controller.setRoomSize(3, 100, 100);
        space_controller.createRoom("MR 5");
        space_controller.setRoomSize(4, 100, 100);

        space_controller.updateRoomConnection();

        space_controller.setRoomBoundaryPointParam(2, 0, 0, 1);
        space_controller.setRoomBoundaryPointParam(3, 0, 2, 0);
        space_controller.setRoomBoundaryPointParam(4, 0, 2, 1);

        space_controller.updateRoom();

        space_controller.showSpace(0);

        break;
    case 2:
        space_controller.createBoundary("Outer Wall");
        space_controller.setOuterBoundary(0);

        space_controller.addBoundaryPoint(0, 0, 0);
        space_controller.addBoundaryPoint(0, 400, 0);
        space_controller.addBoundaryPoint(0, 400, 400);
        space_controller.addBoundaryPoint(0, 0, 400);

        space_controller.updateBoundary();

        space_controller.createRoom("MR 1");
        space_controller.setRoomSize(0, 100, 70);
        space_controller.createRoom("MR 2");
        space_controller.setRoomSize(1, 100, 70);
        space_controller.createRoom("MR 3");
        space_controller.setRoomSize(2, 100, 80);

        space_controller.setRoomNeighboor(0, 1);
        space_controller.setRoomNeighboor(1, 2);

        space_controller.createRoom("MR 4");
        space_controller.setRoomSize(3, 100, 100);
        space_controller.createRoom("MR 5");
        space_controller.setRoomSize(4, 100, 100);

        space_controller.updateRoomConnection();

        setStartTime();

        while(true)
        {
            size_t random_room_2_boundary_line_idx = std::rand() % 4;
            size_t random_room_34_boundary_line_idx = (random_room_2_boundary_line_idx + 2) % 4;
            float random_room_2_boundary_line_param = 1.0 * (std::rand() % 1000) / 1000.0;
            float random_room_3_boundary_line_param = 1.0 * (std::rand() % 300) / 1000.0;
            float random_room_4_boundary_line_param = 0.7 + 1.0 * (std::rand() % 300) / 1000.0;
            space_controller.setRoomBoundaryPointParam(2, 0, random_room_2_boundary_line_idx, random_room_2_boundary_line_param);
            space_controller.setRoomBoundaryPointParam(3, 0, random_room_34_boundary_line_idx, random_room_3_boundary_line_param);
            space_controller.setRoomBoundaryPointParam(4, 0, random_room_34_boundary_line_idx, random_room_4_boundary_line_param);

            space_controller.updateRoom();

            space_controller.showSpace(1);

            ++cycle_num;

            getFPS(cycle_num, average_fps);

            std::cout << "fps : " << size_t(average_fps) << std::endl;
        }

        break;
    case 3:
        setStartTime();

        while(true)
        {
            space_controller.reset();

            space_controller.createBoundary("Outer Wall");
            space_controller.setOuterBoundary(0);

            space_controller.addBoundaryPoint(0, 0, 0);
            space_controller.addBoundaryPoint(0, 400, 0);
            space_controller.addBoundaryPoint(0, 400, 400);
            space_controller.addBoundaryPoint(0, 0, 400);

            space_controller.updateBoundary();

            space_controller.createRoom("MR 1");
            space_controller.setRoomSize(0, 100, 70);
            space_controller.createRoom("MR 2");
            space_controller.setRoomSize(1, 100, 70);
            space_controller.createRoom("MR 3");
            space_controller.setRoomSize(2, 100, 80);

            space_controller.setRoomNeighboor(0, 1);
            space_controller.setRoomNeighboor(1, 2);

            space_controller.createRoom("MR 4");
            space_controller.setRoomSize(3, 100, 100);
            space_controller.createRoom("MR 5");
            space_controller.setRoomSize(4, 100, 100);

            space_controller.updateRoomConnection();

            size_t random_room_2_boundary_line_idx = std::rand() % 4;
            size_t random_room_34_boundary_line_idx = (random_room_2_boundary_line_idx + 2) % 4;
            float random_room_2_boundary_line_param = 1.0 * (std::rand() % 1000) / 1000.0;
            float random_room_3_boundary_line_param = 1.0 * (std::rand() % 300) / 1000.0;
            float random_room_4_boundary_line_param = 0.7 + 1.0 * (std::rand() % 300) / 1000.0;
            space_controller.setRoomBoundaryPointParam(2, 0, random_room_2_boundary_line_idx, random_room_2_boundary_line_param);
            space_controller.setRoomBoundaryPointParam(3, 0, random_room_34_boundary_line_idx, random_room_3_boundary_line_param);
            space_controller.setRoomBoundaryPointParam(4, 0, random_room_34_boundary_line_idx, random_room_4_boundary_line_param);

            space_controller.updateRoom();

            space_controller.showSpace(1);

            ++cycle_num;

            getFPS(cycle_num, average_fps);

            std::cout << "fps : " << size_t(average_fps) << std::endl;
        }

        break;
    }
}

bool EasySpaceWidget::createDemo()
{
    // 0 : AnHui Applicated Center
    // 1 : Rebuild Demo
    size_t demo_mode = 1;

    switch(demo_mode)
    {
    case 0:
        space_controller_.reset();

        space_controller_.createBoundary("Outer Wall");
        space_controller_.setOuterBoundary(0);

        space_controller_.addBoundaryPoint(0, 0, 0);
        space_controller_.addBoundaryPoint(0, 400, 0);
        space_controller_.addBoundaryPoint(0, 400, 200);
        space_controller_.addBoundaryPoint(0, 160, 200);
        space_controller_.addBoundaryPoint(0, 160, 400);
        space_controller_.addBoundaryPoint(0, 400, 400);
        space_controller_.addBoundaryPoint(0, 400, 800);
        space_controller_.addBoundaryPoint(0, 0, 800);

        space_controller_.updateBoundary();

        space_controller_.createRoom("Meeting Room");
        space_controller_.setRoomSize(0, 100, 100);
        space_controller_.createRoom("Gaming Room");
        space_controller_.setRoomSize(1, 100, 100);
        space_controller_.createRoom("Manager Department");
        space_controller_.setRoomSize(2, 100, 100);
        space_controller_.createRoom("Manager Department");
        space_controller_.setRoomSize(3, 100, 100);
        space_controller_.createRoom("Gaming Room");
        space_controller_.setRoomSize(4, 100, 100);
        space_controller_.createRoom("Meeting Room");
        space_controller_.setRoomSize(5, 100, 100);

        space_controller_.setRoomNeighboor(0, 1);
        space_controller_.setRoomNeighboor(1, 2);
        space_controller_.setRoomNeighboor(0, 2);

        space_controller_.setRoomNeighboor(3, 4);
        space_controller_.setRoomNeighboor(4, 5);

        space_controller_.updateRoomConnection();

        space_controller_.setRoomBoundaryPointParam(0, 0, 0, 0);
        space_controller_.setRoomBoundaryPointParam(4, 0, 6, 0);

        space_controller_.updateRoom();

        space_controller_.showSpace(0);

        this->update();
        break;
    case 1:
        space_controller_.reset();

        space_controller_.createBoundary("Outer Wall");
        space_controller_.setOuterBoundary(0);

        space_controller_.addBoundaryPoint(0, 0, 0);
        space_controller_.addBoundaryPoint(0, 400, 0);
        space_controller_.addBoundaryPoint(0, 400, 400);
        space_controller_.addBoundaryPoint(0, 0, 400);

        space_controller_.updateBoundary();

        space_controller_.createRoom("MR 1");
        space_controller_.setRoomSize(0, 100, 70);
        space_controller_.createRoom("MR 2");
        space_controller_.setRoomSize(1, 100, 70);
        space_controller_.createRoom("MR 3");
        space_controller_.setRoomSize(2, 100, 80);

        space_controller_.setRoomNeighboor(0, 1);
        space_controller_.setRoomNeighboor(1, 2);

        space_controller_.createRoom("MR 4");
        space_controller_.setRoomSize(3, 100, 100);
        space_controller_.createRoom("MR 5");
        space_controller_.setRoomSize(4, 100, 100);

        space_controller_.updateRoomConnection();

        size_t random_room_2_boundary_line_idx = std::rand() % 4;
        size_t random_room_34_boundary_line_idx = (random_room_2_boundary_line_idx + 2) % 4;
        float random_room_2_boundary_line_param = 1.0 * (std::rand() % 1000) / 1000.0;
        float random_room_3_boundary_line_param = 1.0 * (std::rand() % 300) / 1000.0;
        float random_room_4_boundary_line_param = 0.7 + 1.0 * (std::rand() % 300) / 1000.0;
        space_controller_.setRoomBoundaryPointParam(2, 0, random_room_2_boundary_line_idx, random_room_2_boundary_line_param);
        space_controller_.setRoomBoundaryPointParam(3, 0, random_room_34_boundary_line_idx, random_room_3_boundary_line_param);
        space_controller_.setRoomBoundaryPointParam(4, 0, random_room_34_boundary_line_idx, random_room_4_boundary_line_param);

        space_controller_.updateRoom();

        space_controller_.showSpace(0);

        this->update();

        break;
    }

    return true;
}

void EasySpaceWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    drawBoundary();

    drawRoomBoundary();
}

void EasySpaceWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    createDemo();
}

void EasySpaceWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void EasySpaceWidget::mouseReleaseEvent(QMouseEvent *event)
{
}

bool EasySpaceWidget::drawBoundary()
{
    QPainter painter(this);

    QPen pen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    QFont font("宋体", 15, QFont::Bold, true);
    painter.setFont(font);

    float x_max = std::numeric_limits<float>::min();
    float y_max = std::numeric_limits<float>::min();

    for(const EasyBoundary &boundary : space_controller_.boundary_vec_)
    {
        x_max = std::fmax(x_max, boundary.boundary.rect.x_max);
        y_max = std::fmax(y_max, boundary.boundary.rect.y_max);
    }

    for(const EasyBoundary &boundary : space_controller_.boundary_vec_)
    {
        if(boundary.boundary.point_list.size() == 0)
        {
            continue;
        }

        for(size_t i = 0; i < boundary.boundary.point_list.size(); ++i)
        {
            const EasyPolygon2D &boundary_polygon = boundary.boundary;
            const EasyPoint2D &current_point = boundary_polygon.point_list[i];
            const EasyPoint2D &next_point =
              boundary_polygon.point_list[(i + 1) % boundary_polygon.point_list.size()];

            const size_t current_point_x =
              size_t(current_point.x - space_controller_.x_min_) + space_controller_.x_free_;
            const size_t current_point_y =
              size_t(current_point.y - space_controller_.y_min_) + space_controller_.y_free_;

            const size_t next_point_x = 
              size_t(next_point.x - space_controller_.x_min_) + space_controller_.x_free_;
            const size_t next_point_y =
              size_t(next_point.y - space_controller_.y_min_) + space_controller_.y_free_;


            painter.drawLine(current_point_x, current_point_y, next_point_x, next_point_y);

            QString text = "b" + QString::number(i);

            painter.drawText(current_point_x, current_point_y, text);
        }
    }

    return true;
}

bool EasySpaceWidget::drawRoomLinePosition()
{
    if(space_controller_.room_line_boundary_point_vec_.size() == 0)
    {
        std::cout << "EasySpaceWidget::drawRoomLinePosition : " <<
          "room line boundary point not found!" << std::endl;

        return false;
    }

    QPainter painter(this);

    QPen pen(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    QFont font("宋体", 15, QFont::Bold, true);
    painter.setFont(font);

    for(size_t i = 0; i < space_controller_.room_line_boundary_point_vec_.size(); ++i)
    {
        const EasyBoundaryPoint &room_line_boundary_point = space_controller_.room_line_boundary_point_vec_[i];

        if(!room_line_boundary_point.is_valid)
        {
            continue;
        }

        const EasyPoint2D &room_line_boundary_point_position =
          room_line_boundary_point.position;

        const size_t point_x =
          size_t(room_line_boundary_point_position.x - space_controller_.x_min_) + space_controller_.x_free_;
        const size_t point_y =
          size_t(room_line_boundary_point_position.y - space_controller_.y_min_) + space_controller_.y_free_;

        painter.drawPoint(point_x, point_y);

        QString text = "rl" + QString::number(i);

        painter.drawText(point_x, point_y, text);
    }

    return true;
}

bool EasySpaceWidget::drawRoomPosition()
{
    if(space_controller_.room_boundary_point_vec_.size() == 0)
    {
        std::cout << "EasySpaceWidget::drawRoomPosition : " <<
          "room boundary point not found!" << std::endl;

        return false;
    }

    QPainter painter(this);

    QPen pen(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    QFont font("宋体", 15, QFont::Bold, true);
    painter.setFont(font);

    for(size_t i = 0; i < space_controller_.room_boundary_point_vec_.size(); ++i)
    {
        const EasyBoundaryPoint &room_boundary_point = space_controller_.room_boundary_point_vec_[i];

        if(!room_boundary_point.is_valid)
        {
            continue;
        }

        const EasyPoint2D &room_boundary_point_position =
          room_boundary_point.position;

        const size_t point_x =
          size_t(room_boundary_point_position.x - space_controller_.x_min_) + space_controller_.x_free_;
        const size_t point_y =
          size_t(room_boundary_point_position.y - space_controller_.y_min_) + space_controller_.y_free_;

        painter.drawPoint(point_x, point_y);

        QString text = "r" + QString::number(i);

        painter.drawText(point_x, point_y, text);
    }

    return true;
}

bool EasySpaceWidget::drawRoomBoundary()
{
    if(space_controller_.room_vec_.size() == 0)
    {
        std::cout << "EasySpaceWidget::drawRoomBoundary : " <<
          "room vec is empty!" << std::endl;

        return false;
    }

    QPainter painter(this);

    QPen pen(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    QFont font("宋体", 15, QFont::Bold, true);
    painter.setFont(font);

    for(size_t i = 0; i < space_controller_.room_vec_.size(); ++i)
    {
        const EasyRoom &room = space_controller_.room_vec_[i];

        if(room.boundary.point_list.size() == 0)
        {
            continue;
        }

        float average_x = 0;
        float average_y = 0;

        for(size_t j = 0; j < room.boundary.point_list.size(); ++j)
        {
            const EasyPoint2D &boundary_line_start_point = room.boundary.point_list[j];
            const EasyPoint2D &boundary_line_end_point =
              room.boundary.point_list[(j + 1) % room.boundary.point_list.size()];

            average_x += boundary_line_start_point.x;
            average_y += boundary_line_start_point.y;

            const size_t current_point_x =
              size_t(boundary_line_start_point.x - space_controller_.x_min_) + space_controller_.x_free_;
            const size_t current_point_y =
              size_t(boundary_line_start_point.y - space_controller_.y_min_) + space_controller_.y_free_;

            const size_t next_point_x =
              size_t(boundary_line_end_point.x - space_controller_.x_min_) + space_controller_.x_free_;
            const size_t next_point_y =
              size_t(boundary_line_end_point.y - space_controller_.y_min_) + space_controller_.y_free_;

            painter.drawLine(current_point_x, current_point_y, next_point_x, next_point_y);
        }

        average_x =
          size_t(average_x / room.boundary.point_list.size() - space_controller_.x_min_) + space_controller_.x_free_;
        average_y =
          size_t(average_y / room.boundary.point_list.size() - space_controller_.y_min_) + space_controller_.y_free_;


        QString text = QString::number(i);

        painter.drawText(average_x, average_y, text);
    }

    return true;
}



bool EasySpaceWidget::setStartTime()
{
    clock_gettime(CLOCK_REALTIME_COARSE, &t_spc_);
    t_start_ = t_spc_.tv_sec;
    last_second_ = t_start_;

    return true;
}

bool EasySpaceWidget::getFPS(
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
