#ifndef SENDERWORKER_H
#define SENDERWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QQueue>
#include <QJsonObject>
#include <QJsonDocument>

class SenderWorker : public QObject
{
    Q_OBJECT
public:
    explicit SenderWorker(QObject *parent = nullptr);

public slots:
    void connectToServer(); // opens the socket
    void sendJson(QByteArray jsonBytes);
    void onConnected();
    void onReadyRead();

signals:
    void alertReceived(QString timestamp,
                       QString threatType,
                       QString sourceIP,
                       QString destinationIP,
                       double confidence,
                       QString rule);
private:
    QTcpSocket *m_socket = nullptr;
    QQueue<QByteArray> m_pendingQueue;
    QByteArray m_readBuffer;
};


#endif // SENDERWORKER_H
