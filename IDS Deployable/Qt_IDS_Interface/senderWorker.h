#ifndef SENDERWORKER_H
#define SENDERWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QQueue>

class SenderWorker : public QObject
{
    Q_OBJECT
public:
    explicit SenderWorker(QObject *parent = nullptr);

public slots:
    void connectToServer(); // opens the socket
    void sendJson(QByteArray jsonBytes);
    void onConnected();

private:
    QTcpSocket *m_socket = nullptr;
    QQueue<QByteArray> m_pendingQueue;
};

#endif // SENDERWORKER_H
