#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QKeyEvent>
#include <QFile>

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

void MainWindow::saveToFile()
{
    QFile file("lastSession.csv");
    QTableWidget *timeList = ui->widget_3->table;
    std::vector<std::string> scrambles = ui->widget_2->scrambleList;

    if(file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data( &file );
        QStringList strList;
        for( int c = 0; c < timeList->columnCount(); ++c )
        {
            strList <<
                       "\" " +
                       timeList->horizontalHeaderItem(c)->data(Qt::DisplayRole).toString() +
                       "\" ";
        }
        strList << "\"scrambles\" ";

        data << strList.join(";") << "\n";
        for( int r = 0; r < timeList->rowCount(); ++r )
        {
            strList.clear();
            for( int c = 0; c < timeList->columnCount(); ++c )
            {
                QTableWidgetItem* item = timeList->item(r,c);           //Load items
                if (!item || item->text().isEmpty())                    //Test if there is something at item(r,c)
                {
                    timeList->setItem(r,c,new QTableWidgetItem("0"));   //IF there is nothing write 0
                }
                strList << "\" "+timeList->item( r, c )->text()+"\" ";
            }
            strList << "\" "+QString::fromStdString(scrambles[scrambles.size()- (r+2)])+"\" ";
            data << strList.join( ";" )+"\n";
        }
        file.close();
    }
}
