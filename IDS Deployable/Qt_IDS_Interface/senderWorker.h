#ifndef SENDERWORKER_H
#define SENDERWORKER_H

#include <QObject>
#include <QTcpSocket>

class SenderWorker : public QObject
{
    Q_OBJECT
public:
    explicit SenderWorker(QObject *parent = nullptr);

public slots:
    void connectToServer(); // opens the socket
    // sendJson(QByteArray) slot will come in #57

private:
    QTcpSocket *m_socket = nullptr;
};

#endif // SENDERWORKER_H
