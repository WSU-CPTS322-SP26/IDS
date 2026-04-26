#include "senderWorker.h"

SenderWorker::SenderWorker(QObject *parent)
    : QObject{parent}
{}

void SenderWorker::connectToServer(){
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, [](){
        qDebug() << "Connected to Python IDS";
    });
    connect(m_socket, &QTcpSocket::errorOccurred, this, [](QAbstractSocket::SocketError e){
        qDebug() << "Socket error:" << e;
    });
    m_socket->connectToHost("127.0.0.1", 9999);

    // Hello-world test
    if (m_socket -> waitForConnected(2000)){
        m_socket->write("hello from Qt\n");
    }
}
