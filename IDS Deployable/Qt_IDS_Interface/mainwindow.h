/*
 * AI was used to help with syntax and threading.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class CaptureWorker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QString inter, QWidget *parent = nullptr);
        ~MainWindow();
        void  startInterpreter(QString inter);

    private slots:
        void addPacketRow(QString timeStamp,
                          QString sourceIP,
                          QString destIP,
                          QString proto,
                          int len,
                          int sourcePort,
                          int destPort);
        void onCaptureError(QString message);
        void addAlertRow(QString timestamp,
                         QString threadType,
                         QString sourceIP,
                         QString destinationIP,
                         double confidence,
                         QString rule);
        void onSynFloodClicked();
        void onPortScanClicked();

    signals:
        void fakePacket(QByteArray jsonBytes);

    private:
        Ui::MainWindow *ui;
        QThread *captureThread = nullptr;
        QThread *senderThread = nullptr;
};
#endif // MAINWINDOW_H
