#include "MainWindow.h"
#include "qwidget.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    easy_widget_ = new EasyWidget(this);

    this->ui->VLayout->addWidget(easy_widget_);

    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

