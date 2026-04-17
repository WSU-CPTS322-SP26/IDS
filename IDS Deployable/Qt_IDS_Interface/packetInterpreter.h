/*
 * AI was used to help with syntax and threading.
 */
#ifndef PACKETINTERPRETER_H
#define PACKETINTERPRETER_H
#include "pcap.h"
#include <Winsock2.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct PacketDetails {
    int len;
    int sourcePort;
    int destPort;
    char  proto[8];
    char timeStamp[16];
    char sourceIP[16];
    char destIP[16];
} PacketDetails;

typedef void (*PacketCallback)(const PacketDetails* pktStruct,void *userData); //fp

int interpreter(char* name, PacketCallback cb, void *userData);
int packetProcess(PacketDetails *info, const struct pcap_pkthdr* header, const u_char* pkt_data);

#ifdef __cplusplus
}
#endif

#endif // PACKETINTERPRETER_H
