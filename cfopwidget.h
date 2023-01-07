#ifndef CFOPWIDGET_H
#define CFOPWIDGET_H

#include <QWidget>

namespace Ui {
class CfopWidget;
}

class CfopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CfopWidget(QWidget *parent = nullptr);
    ~CfopWidget();

private:
    Ui::CfopWidget *ui;
};

#endif // CFOPWIDGET_H
