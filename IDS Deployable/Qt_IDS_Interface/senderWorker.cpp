#include "senderWorker.h"

SenderWorker::SenderWorker(QObject *parent)
    : QObject{parent}
{}

void SenderWorker::connectToServer(){
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &SenderWorker::onConnected);
    connect(m_socket, &QTcpSocket::connected, this, [](){
        qDebug() << "Connected to Python IDS";
    });
    connect(m_socket, &QTcpSocket::errorOccurred, this, [](QAbstractSocket::SocketError e){
        qDebug() << "Socket error:" << e;
    });
    m_socket->connectToHost("127.0.0.1", 9999);
}

void SenderWorker::sendJson(QByteArray jsonBytes){
    if(m_socket && m_socket->state() == QAbstractSocket::ConnectedState){
        m_socket->write(jsonBytes);
    } else{
        m_pendingQueue.enqueue(jsonBytes);
    }
}

void SenderWorker::onConnected(){
    while (!m_pendingQueue.isEmpty()){
        m_socket->write(m_pendingQueue.dequeue());
    }
}
