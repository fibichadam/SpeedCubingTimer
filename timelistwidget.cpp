#include "timelistwidget.h"
#include "ui_timelistwidget.h"

TimeListWidget::TimeListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeListWidget)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table = ui->tableWidget;
}

TimeListWidget::~TimeListWidget()
{
    delete ui;
}

std::string TimeListWidget::intToTimeString(int time)
{
    if(time < 100)
    {
        return "0.0"+std::to_string(time).substr(0,1);
    }

    int ms = time % 1000;
    time /= 1000;
    int sec = time % 60;
    time /= 60;
    int min = time;

    std::string str;
    if(min == 0)    //Short time when minutes = 0
    {
        str = std::to_string(sec).substr(0,2) + "." + std::to_string(ms).substr(0,2);
    }
    else            //Long time
    {
        str = std::to_string(min) + ":" + std::to_string(sec) + "." + std::to_string(ms).substr(0,2);
    }

    return str;
}

void TimeListWidget::insertTime(int time)
{
     calcTime.push_back(time);

    //insert time
    QString s = QString::fromStdString(intToTimeString(time));
    table->insertRow(0);
    table->setItem(0, 0, new QTableWidgetItem(s));

    // calculate and insert ao3
    if(calcTime.size() >= 3)
    {
        int sum = 0;
        for(int i = 1; i < 4; i++)
        {
            sum += calcTime[calcTime.size()-i];
        }
        sum /= 3;

        QString s = QString::fromStdString(intToTimeString(sum));
        table->setItem(0, 1, new QTableWidgetItem(s));
    }

    // calculate and insert ao5
    if(calcTime.size() >= 5)
    {
        int sum = 0;
        for(int i = 1; i < 6; i++)
        {
            sum += calcTime[calcTime.size()-i];
        }
        sum /= 5;

        QString s = QString::fromStdString(intToTimeString(sum));
        table->setItem(0, 2, new QTableWidgetItem(s));
    }

    // calculate and insert ao12
    if(calcTime.size() >= 12)
    {
        int sum = 0;
        for(int i = 1; i < 13; i++)
        {
            sum += calcTime[calcTime.size()-i];
        }
        sum /= 12;

        QString s = QString::fromStdString(intToTimeString(sum));
        table->setItem(0, 3, new QTableWidgetItem(s));
    }
}
