#include "UnitWorldWidget.h"
#include "ui_UnitWorldWidget.h"

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
    polygon_vec_.resize(2);

    polygon_vec_[0].addPoint(0, 0);
    polygon_vec_[0].addPoint(30, 0);
    polygon_vec_[0].addPoint(30, 30);
    polygon_vec_[0].addPoint(0, 30);

    polygon_vec_[1].addPoint(10, 10);
    polygon_vec_[1].addPoint(20, 10);
    polygon_vec_[1].addPoint(20, 20);
    polygon_vec_[1].addPoint(10, 20);

    zoom_ = 20;
    offset_x_ = 100;
    offset_y_ = 100;

    mouse_pressed_ = false;
}

void UnitWorldWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    drawBackGround();

    drawPolygon();

    if(mouse_pressed_)
    {
        drawPolygonPoint();
    }
}

void UnitWorldWidget::mousePressEvent(QMouseEvent *event)
{
    mouse_pressed_ = true;
    setMousePosition(event->pos());
}

void UnitWorldWidget::mouseMoveEvent(QMouseEvent *event)
{
    setMousePosition(event->pos());
}

void UnitWorldWidget::mouseReleaseEvent(QMouseEvent *event)
{
    setMousePosition(event->pos());
    mouse_pressed_ = false;
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

bool UnitWorldWidget::setMousePosition(
    const QPoint& mouse_position_in_image)
{
    EasyPoint2D mouse_position_in_world = getPointInWorld(mouse_position_in_image);
    polygon_point_.updateByPosition(polygon_vec_[0], mouse_position_in_world);

    update();

    return true;
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

bool UnitWorldWidget::drawPolygon()
{
    QPainter painter(this);

    QPen pen(QColor(255, 255, 255), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    painter.setPen(pen);

    for(const EasyPolygon2D& polygon : polygon_vec_)
    {
        QPolygon q_polygon;
        q_polygon.resize(polygon.point_list.size());

        for(size_t i = 0; i < polygon.point_list.size(); ++i)
        {
            const EasyPoint2D& polygon_point = polygon.point_list[i];
            q_polygon.setPoint(i, QPoint(
                  offset_x_ + zoom_ * polygon_point.x,
                  offset_y_ + zoom_ * polygon_point.y));
        }

        painter.drawPolygon(q_polygon);
    }

    return true;
}

bool UnitWorldWidget::drawPolygonPoint()
{
    QPainter painter(this);

    QPen pen(QColor(0, 255, 0), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    painter.setPen(pen);

    QPoint q_point = getPointInImage(polygon_point_.position);

    painter.drawPoint(q_point);

    return true;
}
