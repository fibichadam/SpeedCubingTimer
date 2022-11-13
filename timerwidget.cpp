#include "timerwidget.h"
#include "ui_timerwidget.h"
#include <QKeyEvent>
#include <QTimer>
#include <QTime>

TimerWidget::TimerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerWidget)
{
    ui->setupUi(this);
    QWidget::setFocusPolicy(Qt::StrongFocus);
    timer = new QTimer(this);
}

TimerWidget::~TimerWidget()
{
    delete ui;
}

void TimerWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)   //Handle preparing timer
    {
        prepareTimer();
    }

    if(event->key() && started)         //Stop timer
    {
        started = false;
        timer->stop();
    }
}

void TimerWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space && !event->isAutoRepeat() && !ready)                   //Timer not ready
    {
        prepared = false;
        ui->Timer->setStyleSheet(ui->Timer->styleSheet()+("color: rgb(208, 208, 208);"));
    }
    else if(event->key() == Qt::Key_Space && ready && !event->isAutoRepeat())               //Start timer
    {
        ui->Timer->setStyleSheet(ui->Timer->styleSheet()+("color: rgb(208, 208, 208);"));
        startTime = QTime::currentTime();
        started = true;
        prepared = false;
        ready = false;

        connect(timer, &QTimer::timeout, this, &TimerWidget::showTime);
        timer->start(10);
    }
}

void TimerWidget::prepareTimer()
{
    if(!prepared)                                                                           //Prepare timer
    {
        prepared = true;
        prepareTime = std::chrono::steady_clock::now();
        ui->Timer->setStyleSheet(ui->Timer->styleSheet()+("color: red;"));
    }
    else                                                                                    //Check if timer ready
    {
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedPrepareTime = end - prepareTime;
        if(elapsedPrepareTime.count() > 0.5)
        {
            ready = true;
            ui->Timer->setText("0.000");
            ui->Timer->setStyleSheet(ui->Timer->styleSheet()+("color: rgb(0, 170, 0);"));
        }
    }
}

void TimerWidget::showTime()
{
    QTime time = QTime::currentTime();

    //calculate time difference from start and swap to minutes, seconds and milliseconds
    int diff = startTime.msecsTo(time);
    int ms = diff % 1000;
    diff /= 1000;
    int sec = diff % 60;
    diff /= 60;
    int min = diff;

    QString text;
    std::string str;
    if(min == 0)    //Short timer when minutes = 0
    {
        str = std::to_string(sec) + "." + std::to_string(ms);
    }
    else            //Long timer
    {
        str = std::to_string(min) + ":" + std::to_string(sec) + "." + std::to_string(ms);
    }

    text = QString::fromStdString(str);

    ui->Timer->setText(text);
}
