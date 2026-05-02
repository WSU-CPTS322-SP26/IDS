/*
 * Worker thread to capture packets.
 */

#include "captureWorker.h"
#include "packetInterpreter.h"
#include <QJsonObject>
#include <QJsonDocument>


static void packetBridge(const PacketDetails* pktStruct,void* userData){
    CaptureWorker *worker = static_cast<CaptureWorker*>(userData);
    emit worker->packetReady(QString::fromLocal8Bit(pktStruct->timeStamp),
                             QString::fromLocal8Bit(pktStruct->sourceIP),
                             QString::fromLocal8Bit(pktStruct->destIP),
                             QString::fromLocal8Bit(pktStruct->proto),
                             pktStruct->len,
                             pktStruct->sourcePort,
                             pktStruct->destPort);
    // build JSON for the socket
    QJsonObject obj;
    obj["timestamp"] = QString::fromLocal8Bit(pktStruct->isoTimeStamp);
    obj["source_ip"] = QString::fromLocal8Bit(pktStruct->sourceIP);
    obj["destination_ip"] = QString::fromLocal8Bit(pktStruct->destIP);
    obj["protocol"] = QString::fromLocal8Bit(pktStruct->proto);
    obj["length"] = pktStruct->len;
    obj["source_port"] = pktStruct->sourcePort;
    obj["destination_port"] = pktStruct->destPort;
    obj["tcp_flags"] = pktStruct->tcp_flags;

    QByteArray jsonBytes = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    jsonBytes.append('\n');

    emit worker->packetSerialized(jsonBytes);
}

CaptureWorker::CaptureWorker(const QString &deviceName)
    : m_deviceName(deviceName){
}

void CaptureWorker::process(){
    QByteArray arr = m_deviceName.toLocal8Bit();
    int rc = interpreter(arr.data(),packetBridge, this);
    if (rc != 0){
        emit error ("Capture unsuccessful.");
    }
    emit  finished();
}
