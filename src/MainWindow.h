#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "EasyWorldWidget.h"
#include "UnitWorldWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void run_example();

private:
    Ui::MainWindow *ui;

    // EasyWorldWidget *widget_;
    UnitWorldWidget *widget_;
};
#endif // MAINWINDOW_H
