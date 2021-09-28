#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "EasyWidget.h"

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

    EasyWidget *easy_widget_;
};
#endif // MAINWINDOW_H
