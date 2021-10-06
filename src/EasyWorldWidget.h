#ifndef EASYWORLDWIDGET_H
#define EASYWORLDWIDGET_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>

#include <time.h>
#include "EasyWorld/WorldController.h"

namespace Ui {
class EasyWorldWidget;
}

class EasyWorldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EasyWorldWidget(QWidget *parent = nullptr);
    ~EasyWorldWidget();

    void run_example();

protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    bool drawWallBoundaryAxis();
    bool drawWallBoundaryPolygon();
    bool drawWallSpaceBoundary();

    bool drawRoomBoundaryAxis();
    bool drawRoomBoundaryPolygon();
    bool drawRoomSpaceBoundary();

private:
    bool setStartTime();

    bool getFPS(
        const long &cycle_num,
        float &average_fps);

private:
    Ui::EasyWorldWidget *ui;

    WorldController world_controller_;

    float axis_length_;

    timespec t_spc_;
    long t_start_;
    long last_second_;
};

#endif // EASYWORLDWIDGET_H
