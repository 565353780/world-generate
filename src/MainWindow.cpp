#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    run_example();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run_example()
{
    SpaceController space_controller;

    space_controller.addBoundaryPoint(0, 0);
    space_controller.addBoundaryPoint(400, 0);
    space_controller.addBoundaryPoint(400, 200);
    space_controller.addBoundaryPoint(160, 200);
    space_controller.addBoundaryPoint(160, 400);
    space_controller.addBoundaryPoint(400, 400);
    space_controller.addBoundaryPoint(400, 800);
    space_controller.addBoundaryPoint(0, 800);

    space_controller.showBoundary();
}
