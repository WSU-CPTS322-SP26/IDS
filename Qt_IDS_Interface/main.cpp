#include "mainwindow.h"
#include "choosedevs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChooseDevs w;
    w.show();
    return a.exec();
}
