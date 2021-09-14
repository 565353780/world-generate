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

    std::vector<EasyPoint2D> boundary_point_vec;

    EasyPoint2D boundary_point;
    boundary_point.setPosition(0, 0);
    boundary_point_vec.emplace_back(boundary_point);
    boundary_point.setPosition(1000, 0);
    boundary_point_vec.emplace_back(boundary_point);
    boundary_point.setPosition(1000, 1000);
    boundary_point_vec.emplace_back(boundary_point);
    boundary_point.setPosition(600, 1000);
    boundary_point_vec.emplace_back(boundary_point);
    boundary_point.setPosition(600, 1500);
    boundary_point_vec.emplace_back(boundary_point);
    boundary_point.setPosition(1000, 1500);
    boundary_point_vec.emplace_back(boundary_point);
    boundary_point.setPosition(1000, 2000);
    boundary_point_vec.emplace_back(boundary_point);
    boundary_point.setPosition(0, 2000);
    boundary_point_vec.emplace_back(boundary_point);

    space_controller.createBoundary(boundary_point_vec);

    space_controller.showBoundary();
}
