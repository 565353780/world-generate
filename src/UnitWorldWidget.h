#ifndef UNITWORLDWIDGET_H
#define UNITWORLDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPen>
#include <QPainter>
#include <QPolygon>

#include "UnitWorld/UnitWorldController.h"

namespace Ui {
class UnitWorldWidget;
}

class UnitWorldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnitWorldWidget(QWidget *parent = nullptr);
    ~UnitWorldWidget();

    void run_example();

protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint getPointInImage(
        const EasyPoint2D& point_in_world);

    EasyPoint2D getPointInWorld(
        const QPoint& point_in_image);

    bool chooseRoomContainer(
        const QPoint& mouse_position_in_image);

    bool setMousePosition(
        const QPoint& mouse_position_in_image);

    bool drawBackGround();
    bool drawWall();
    bool drawRoom();

private:
    Ui::UnitWorldWidget *ui;

    UnitWorldController unit_world_controller_;
    EasyPolygonPoint2D polygon_point_;

    float zoom_;
    float offset_x_;
    float offset_y_;

    size_t current_choose_node_id_;
    NodeType current_choose_node_type_;
    size_t new_room_idx_;
};

#endif // UNITWORLDWIDGET_H
