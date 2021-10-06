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

    world_controller_.createWorld();

    world_controller_.createWall(0, NodeType::OuterWall);

    EasyPolygon2D wall_boundary_polygon;
    wall_boundary_polygon.addPoint(0, 0);
    wall_boundary_polygon.addPoint(400, 0);
    wall_boundary_polygon.addPoint(400, 400);
    wall_boundary_polygon.addPoint(0, 400);
    wall_boundary_polygon.setAntiClockWise();

    world_controller_.createWallBoundary(0, NodeType::OuterWall, wall_boundary_polygon);

    world_controller_.outputInfo();

    std::cout << "finish run_example!" << std::endl;
}

void EasyWorldWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // drawWallSpaceBoundary();

    drawWallBoundaryPolygon();

    drawWallBoundaryAxis();
}

void EasyWorldWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    EasyPoint2D random_new_point;

    random_new_point.setPosition(100 + rand() % 400, 100 + rand() % 400);

    world_controller_.setWallBoundaryPolygonPointPosition(
        0, NodeType::OuterWall, 1, random_new_point);

    update();
}

void EasyWorldWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void EasyWorldWidget::mouseReleaseEvent(QMouseEvent *event)
{
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
                const EasyPoint2D &current_point =
                  wall_boundary_polygon.point_list[i];
                const EasyPoint2D &next_point =
                  wall_boundary_polygon.point_list[
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

    for(const EasyNode* wall_space_node : wall_space_node_vec)
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

            painter.drawLine(
                current_point.x, current_point.y,
                next_point.x, next_point.y);
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
