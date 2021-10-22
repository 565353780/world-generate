#ifndef EASYWORLDWIDGET_H
#define EASYWORLDWIDGET_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QPoint>
#include <QPolygon>

#include <time.h>

#include "EasyWorld/WorldSplitGenerator.h"
#include "EasyWorld/WorldPlaceGenerator.h"
#include "EasyWorld/WorldEditer.h"

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
    bool chooseRoomContainer(
        QMouseEvent *event);

    bool moveWallRoomContainer(
        const size_t &wall_roomcontainer_id,
        QMouseEvent *event);

    bool drawWallBoundaryAxis(
        WorldController &world_controller);
    bool drawWallBoundaryPolygon(
        WorldController &world_controller);
    bool drawWallSpaceBoundary(
        WorldController &world_controller);
    bool drawWallInside(
        WorldController &world_controller);

    bool drawRoomContainerBoundaryAxis(
        WorldController &world_controller);
    bool drawRoomContainerBoundaryPolygon(
        WorldController &world_controller);
    bool drawRoomContainerSpaceBoundary(
        WorldController &world_controller);

    bool drawRoomBoundaryAxis(
        WorldController &world_controller);
    bool drawRoomBoundaryPolygon(
        WorldController &world_controller);
    bool drawRoomSpaceBoundary(
        WorldController &world_controller);

    bool drawDoorBoundaryAxis(
        WorldController &world_controller);
    bool drawDoorBoundaryPolygon(
        WorldController &world_controller);
    bool drawDoorSpaceBoundary(
        WorldController &world_controller);

    bool drawWindowBoundaryAxis(
        WorldController &world_controller);
    bool drawWindowBoundaryPolygon(
        WorldController &world_controller);
    bool drawWindowSpaceBoundary(
        WorldController &world_controller);

    bool drawTeamBoundaryAxis(
        WorldController &world_controller);
    bool drawTeamBoundaryPolygon(
        WorldController &world_controller);
    bool drawTeamSpaceBoundary(
        WorldController &world_controller);

    bool drawPersonBoundaryAxis(
        WorldController &world_controller);
    bool drawPersonBoundaryPolygon(
        WorldController &world_controller);
    bool drawPersonSpaceBoundary(
        WorldController &world_controller);

    bool drawFurnitureBoundaryAxis(
        WorldController &world_controller);
    bool drawFurnitureBoundaryPolygon(
        WorldController &world_controller);
    bool drawFurnitureSpaceBoundary(
        WorldController &world_controller);

    bool setStartTime();

    bool getFPS(
        const long &cycle_num,
        float &average_fps);

private:
    Ui::EasyWorldWidget *ui;

    WorldController world_controller_;
    WorldSplitGenerator world_split_generator_;
    WorldPlaceGenerator world_place_generator_;
    WorldEditer world_editer_;

    float axis_length_;
    float zoom_;
    QColor wall_color_;
    QColor wall_brush_color_;
    QColor roomcontainer_color_;
    QColor roomcontainer_brush_color_;
    QColor room_color_;
    QColor room_brush_color_;
    QColor door_color_;
    QColor door_brush_color_;
    QColor window_color_;
    QColor window_brush_color_;
    QColor team_color_;
    QColor team_brush_color_;
    QColor person_color_;
    QColor person_brush_color_;
    QColor furniture_color_;
    QColor furniture_brush_color_;

    timespec t_spc_;
    long t_start_;
    long last_second_;

    size_t current_choose_node_id_;
    NodeType current_choose_node_type_;

    float current_press_position_to_start_position;
};

#endif // EASYWORLDWIDGET_H
