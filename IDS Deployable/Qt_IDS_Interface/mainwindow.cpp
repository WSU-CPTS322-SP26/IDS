/*
 * AI was used to help with syntax and threading.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "captureWorker.h"
#include "senderWorker.h"

#include <QHeaderView>
#include <QMessageBox>
#include <QScrollBar>

/*
 * inter is the name of the device to listen on
 */
MainWindow::MainWindow(QString inter, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->home->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->home->verticalHeader()->setVisible(false);
    startInterpreter(inter);

}

MainWindow::~MainWindow()
{
    if(captureThread){
        captureThread->quit();
        captureThread->wait();
    }
    delete(ui);
}

void MainWindow::startInterpreter(QString inter){
    captureThread = new QThread(this);
    CaptureWorker* worker = new CaptureWorker(inter);

    worker->moveToThread(captureThread);
    connect(captureThread, &QThread::started, worker, &CaptureWorker::process);
    connect(worker, &CaptureWorker::packetReady, this, &MainWindow::addPacketRow);
    connect(worker, &CaptureWorker::error, this, &MainWindow::onCaptureError);
    connect(worker, &CaptureWorker::finished, captureThread, &QThread::quit);
    connect(worker, &CaptureWorker::finished, worker, &QObject::deleteLater);
    connect(captureThread, &QThread::finished, captureThread, &QObject::deleteLater);

    SenderWorker* sender = new SenderWorker(this);
    sender->connectToServer();

    captureThread->start();
}
void MainWindow::addPacketRow(QString timeStamp,
                         QString sourceIP,
                         QString destIP,
                         QString proto,
                         int len,
                         int sourcePort,
                         int destPort){

    QScrollBar* bar = ui->home->verticalScrollBar();
    bool wasAtBottom = (bar->value() == bar->maximum());
    int row = ui->home->rowCount();
    ui->home->insertRow(row);

    ui->home->setItem(row, 0, new QTableWidgetItem(QString::number(row+1)));
    ui->home->item(row,0)->setTextAlignment(Qt::AlignCenter);

    ui->home->setItem(row, 1, new QTableWidgetItem(timeStamp));
    ui->home->setItem(row, 2, new QTableWidgetItem(sourceIP));
    ui->home->setItem(row, 3, new QTableWidgetItem(destIP));
    ui->home->setItem(row, 4, new QTableWidgetItem(proto));
    ui->home->setItem(row, 5, new QTableWidgetItem(QString::number(len)));

    QString build = "";
    build = QString::number(sourcePort) + " -> " + QString::number(destPort);

    ui->home->setItem(row, 6, new QTableWidgetItem(build));


    if(wasAtBottom){
        ui->home->scrollToBottom();
    }
}
void MainWindow::onCaptureError(QString message){
    QMessageBox::critical(this, "Capture Error", message);
}
