#ifndef EASYWORLDWIDGET_H
#define EASYWORLDWIDGET_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QPoint>

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

private:
    bool moveWallInWorld(
        const size_t &wall_id,
        const NodeType &wall_type,
        QMouseEvent *event);

    bool moveRoomContainerInWorld(
        const size_t &roomcontainer_id,
        const NodeType &roomcontainer_type,
        QMouseEvent *event);

    bool moveRoomInWorld(
        const size_t &room_id,
        const NodeType &room_type,
        QMouseEvent *event);

    bool moveTeamInWorld(
        const size_t &team_id,
        const NodeType &team_type,
        QMouseEvent *event);

    bool movePersonInWorld(
        const size_t &person_id,
        const NodeType &person_type,
        QMouseEvent *event);

    bool moveFurnitureInWorld(
        const size_t &furniture_id,
        const NodeType &furniture_type,
        QMouseEvent *event);

    bool drawWallBoundaryAxis();
    bool drawWallBoundaryPolygon();
    bool drawWallSpaceBoundary();

    bool drawRoomContainerBoundaryAxis();
    bool drawRoomContainerBoundaryPolygon();
    bool drawRoomContainerSpaceBoundary();

    bool drawRoomBoundaryAxis();
    bool drawRoomBoundaryPolygon();
    bool drawRoomSpaceBoundary();

    bool drawTeamBoundaryAxis();
    bool drawTeamBoundaryPolygon();
    bool drawTeamSpaceBoundary();

    bool drawPersonBoundaryAxis();
    bool drawPersonBoundaryPolygon();
    bool drawPersonSpaceBoundary();

    bool drawFurnitureBoundaryAxis();
    bool drawFurnitureBoundaryPolygon();
    bool drawFurnitureSpaceBoundary();

    bool setStartTime();

    bool getFPS(
        const long &cycle_num,
        float &average_fps);

private:
    Ui::EasyWorldWidget *ui;

    WorldController world_controller_;

    float axis_length_;
    float zoom_;
    QColor wall_color_;
    QColor roomcontainer_color_;
    QColor room_color_;
    QColor team_color_;
    QColor person_color_;
    QColor furniture_color_;

    timespec t_spc_;
    long t_start_;
    long last_second_;
};

#endif // EASYWORLDWIDGET_H
