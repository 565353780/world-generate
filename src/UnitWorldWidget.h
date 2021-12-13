#ifndef UNITWORLDWIDGET_H
#define UNITWORLDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPen>
#include <QPainter>
#include <QPolygon>

#include "UnitWorld/UnitWorldEnvironment.h"

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
    bool chooseRoom(
        const QPoint& mouse_position_in_image);

    bool setMousePosition(
        const QPoint& mouse_position_in_image);

    bool drawBackGround();

    bool drawNode(
        const std::vector<std::vector<std::vector<size_t>>>& node_boundary_data_vec,
        QColor color);

private:
    Ui::UnitWorldWidget *ui;

    UnitWorldEnvironment unit_world_environment_;

    size_t current_choose_node_id_;
    NodeType current_choose_node_type_;
    size_t new_room_idx_;
};

#endif // UNITWORLDWIDGET_H
