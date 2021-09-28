#ifndef EASYWIDGET_H
#define EASYWIDGET_H

#include <QWidget>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QDebug>

#include <time.h>
#include "EasySpace/SpaceController.h"

namespace Ui {
class EasyWidget;
}

class EasyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EasyWidget(QWidget *parent = nullptr);
    ~EasyWidget();

    void run_example();

    bool createDemo();

protected:
    void paintEvent(QPaintEvent *event);

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
    Ui::EasyWidget *ui;

    SpaceController space_controller_;
    timespec t_spc_;
    long t_start_;
    long last_second_;
};

#endif // EASYWIDGET_H
