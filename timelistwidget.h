#ifndef TIMELISTWIDGET_H
#define TIMELISTWIDGET_H

#include "qtablewidget.h"
#include <QWidget>

namespace Ui {
class TimeListWidget;
}

class TimeListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeListWidget(QWidget *parent = nullptr);
    ~TimeListWidget();

private slots:
    void insertTime(int time);

private:
    Ui::TimeListWidget *ui;
    QTableWidget *table;
    std::string intToTimeString(int time);

    std::vector<int> calcTime = {};
};

#endif // TIMELISTWIDGET_H
