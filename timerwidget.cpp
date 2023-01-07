#include "timerwidget.h"
#include "qnamespace.h"
#include "ui_timerwidget.h"
#include "timerwidget.h"
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <cstdlib>

TimerWidget::TimerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerWidget)
{
    ui->setupUi(this);
    timer = new QTimer(this);

    QWidget::setFocusPolicy(Qt::StrongFocus);

    generateScramble();
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

    if(event->key() && started)         //Stop timer, generate new scramble and insert time into list
    {
        timer->stop();
        started = false;
        emit insertTime(solveTime);
        generateScramble();
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
            ui->Timer->setText("0.00");
            ui->Timer->setStyleSheet(ui->Timer->styleSheet()+("color: rgb(0, 170, 0);"));
        }
    }
}

void TimerWidget::showTime()
{
    QString text;
    std::string str;

    QTime time = QTime::currentTime();

    //calculate time difference from start and swap to minutes, seconds and milliseconds
    int diff = startTime.msecsTo(time);

    if(diff < 100)
    {
        str = "0.0"+std::to_string(diff).substr(0,1);
    }
    else
    {
        solveTime = diff;
        int ms = diff % 1000;
        diff /= 1000;
        int sec = diff % 60;
        diff /= 60;
        int min = diff;

        if(min == 0)    //Short timer when minutes = 0
        {
            str = std::to_string(sec).substr(0,2) + "." + std::to_string(ms).substr(0,2);
        }
        else            //Long timer
        {
            str = std::to_string(min) + ":" + std::to_string(sec) + "." + std::to_string(ms).substr(0,2);
        }

        if(std::to_string(ms).length() == 1)
        {
            str += "0";
        }
    }

    text = QString::fromStdString(str);
    ui->Timer->setText(text);
}

void TimerWidget::generateScramble()
{
    std::string scramble = "";
    std::vector<std::vector<std::string>> moves = {{"R ", "R' ", "R2 "}, {"L ", "L' ", "L2 "}, {"U ", "U' ", "U2 "}, {"D ", "D' ", "D2 "}, {"F ", "F' ", "F2 "}, {"B ", "B' ", "B2 "}};
    int lastFace = std::rand()%6;
    int face = std::rand()%6;
    for(int i = 0; i < 20; i++)
    {
        while(face == lastFace)
        {
            face = std::rand()%6;
        }
        lastFace = face;

        int move = std::rand()%3;
        scramble += moves[face][move];
    }

    QString text = QString::fromStdString(scramble);
    ui->scrambleLabel->setText(text);
}


