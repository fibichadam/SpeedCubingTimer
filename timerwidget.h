#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

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

private slots:
    void showTime();

private:
    Ui::TimerWidget *ui;
    QTime startTime;
    QTimer *timer;
    std::chrono::time_point<std::chrono::steady_clock> prepareTime;
    bool prepared;
    bool ready;
    bool started;
};

#endif // TIMERWIDGET_H
