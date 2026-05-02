/*
 * Worker thread to send JSON messages over socket.
 */
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
    connect(m_socket, &QTcpSocket::readyRead, this, &SenderWorker::onReadyRead); // Be ready for bytes coming in
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

void SenderWorker::onReadyRead(){
    m_readBuffer.append(m_socket->readAll());

    int newLineIndex;
    while((newLineIndex = m_readBuffer.indexOf('\n')) != -1){
        QByteArray line = m_readBuffer.left(newLineIndex);
        m_readBuffer.remove(0, newLineIndex+1);

        QJsonDocument doc = QJsonDocument::fromJson(line);
        if(!doc.isNull() && doc.isObject()){
            QJsonObject obj = doc.object();
            QString timestamp = obj["timestamp"].toString();
            QString threatType = obj["threat_type"].toString();
            QString sourceIP = obj["source_ip"].toString();
            QString destinationIP = obj["destination_ip"].toString();
            double confidence = obj["confidence"].toDouble();
            QString rule = obj["details"].toObject()["rule"].toString();

            emit alertReceived(timestamp, threatType, sourceIP, destinationIP, confidence, rule);
        }
    }
}
