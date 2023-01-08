#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    QObject::connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(saveToFile()));
    return a.exec();
}
