#include "cfopwidget.h"
#include "ui_cfopwidget.h"

CfopWidget::CfopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CfopWidget)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->setDocumentMode(true);
    ui->tabWidget->tabBar()->setExpanding(true);
}

CfopWidget::~CfopWidget()
{
    delete ui;
}
