#ifndef EASYSPACEWIDGET_H
#define EASYSPACEWIDGET_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>

#include <time.h>
#include "EasySpace/SpaceController.h"
#include "EasyWorld/WorldController.h"

namespace Ui {
class EasySpaceWidget;
}

class EasySpaceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EasySpaceWidget(QWidget *parent = nullptr);
    ~EasySpaceWidget();

    void run_example();

    bool createDemo();

protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool drawBoundary();

    bool drawRoomLinePosition();

    bool drawRoomPosition();

    bool drawRoomBoundary();

    bool setStartTime();

    bool getFPS(
        const long &cycle_num,
        float &average_fps);

private:
    Ui::EasySpaceWidget *ui;

    SpaceController space_controller_;

    timespec t_spc_;
    long t_start_;
    long last_second_;
};

#endif // EASYSPACEWIDGET_H
