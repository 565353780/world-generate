#include "MainWindow.h"
#include "qwidget.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(1600, 900);

    widget_ = new UnitWorldWidget(this);

    this->ui->VLayout->addWidget(widget_);

    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

