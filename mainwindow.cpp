#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->centralWidget()->setFixedSize(0,0);
    connect(ui->widget_2, SIGNAL(insertTime(int)), ui->widget_3, SLOT(insertTime(int)));
    QWidget::setFocusPolicy(Qt::NoFocus);
}

MainWindow::~MainWindow()
{
    delete ui;
}

