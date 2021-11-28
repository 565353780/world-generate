#ifndef UNITWORLDWIDGET_H
#define UNITWORLDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPen>
#include <QPainter>
#include <QPolygon>

#include "EasyShape/EasyShape.h"

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

    bool setMousePosition(
        const QPoint& mouse_position_in_image);

    bool drawBackGround();
    bool drawPolygon();
    bool drawPolygonPoint();

private:
    Ui::UnitWorldWidget *ui;

    std::vector<EasyPolygon2D> polygon_vec_;
    EasyPolygonPoint2D polygon_point_;

    float zoom_;
    float offset_x_;
    float offset_y_;

    bool mouse_pressed_;
};

#endif // UNITWORLDWIDGET_H
