/*
 * AI was used to help with syntax and threading.
 */

#include "captureWorker.h"
#include "packetInterpreter.h"

static void packetBridge(const PacketDetails* pktStruct,void* userData){
    CaptureWorker *worker = static_cast<CaptureWorker*>(userData);
    emit worker->packetReady(QString::fromLocal8Bit(pktStruct->timeStamp),
                             QString::fromLocal8Bit(pktStruct->sourceIP),
                             QString::fromLocal8Bit(pktStruct->destIP),
                             QString::fromLocal8Bit(pktStruct->proto),
                             pktStruct->len,
                             pktStruct->sourcePort,
                             pktStruct->destPort);
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
