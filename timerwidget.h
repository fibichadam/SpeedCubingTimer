#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include "timelistwidget.h"
#include <QWidget>
#include <QTime>
#include <chrono>

namespace Ui {
class TimerWidget;
}

class TimerWidget : public QWidget
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public:
    explicit TimerWidget(QWidget *parent = nullptr);
    ~TimerWidget();
    void prepareTimer();
    void updateTimer();
    void showScramble();

    std::vector<std::string> scrambleList = {};

private slots:
    void showTime();

signals:
    void insertTime(int time);

private:
    void generateScramble();

    Ui::TimerWidget *ui;
    QTime startTime;
    QTimer *timer;
    TimeListWidget *timelist;
    std::chrono::time_point<std::chrono::steady_clock> prepareTime;

    int solveTime;

    bool prepared = false;
    bool ready = false;
    bool started = false;
};

#endif // TIMERWIDGET_H
