#include "MainWindow.h"
#include "qwidget.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMaximumSize(800, 800);

    // widget_ = new EasyWorldWidget(this);
    widget_ = new UnitWorldWidget(this);

    this->ui->VLayout->addWidget(widget_);

    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

