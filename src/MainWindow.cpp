#include "MainWindow.h"
#include "qwidget.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    world_widget_ = new EasyWorldWidget(this);

    this->ui->VLayout->addWidget(world_widget_);

    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

