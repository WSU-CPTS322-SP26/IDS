/*
 * AI was used to help with syntax and threading.
 */

#ifndef CAPTUREWORKER_H
#define CAPTUREWORKER_H

#include <QObject>
#include <QString>

class CaptureWorker : public  QObject{
    Q_OBJECT
    public:
        explicit CaptureWorker(const QString &deviceName);

    public slots:
        void process();

    signals:
        void packetReady(QString timeStamp,
                         QString sourceIP,
                         QString destIP,
                         QString proto,
                         int len,
                         int sourcePort,
                         int destPort);
        void packetSerialized(QByteArray jsonBytes);
        void error(QString message);
        void finished();

    private:
        QString m_deviceName;
};

#endif // CAPTUREWORKER_H
