/*
 * AI was leveraged for this project.
 */

#include "mainwindow.h"
#include "choosedevs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChooseDevs w;
    w.showMaximized();
    return a.exec();
}
