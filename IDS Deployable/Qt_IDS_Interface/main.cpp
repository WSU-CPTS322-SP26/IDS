/*
 * AI was used to help with syntax and threading.
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
