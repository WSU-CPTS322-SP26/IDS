/*
 * Opens a adaptor to capture packets. Extracts the timestamp and the length
 * of every packet and prints them on the screen. Does not use Callback approach
 * requiring a direct call from the programmer each time he wants to retrieve a packet.
 * Tutorial Link: https://npcap.com/guide/npcap-tutorial.html
 *
 * AI was used to help with syntax and threading.
 *
 */

#include "packetInterpreter.h"
#include "misc.h" /* LoadNpcapDlls */
#include <time.h>

/* 4 bytes IP address */
typedef struct ip_address {
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

/* IPv4 header */
typedef struct ip_header {
    u_char  ver_ihl; // Version (4 bits) + IP header length (4 bits)
    u_char  tos;     // Type of service
    u_short tlen;    // Total length
    u_short identification; // Identification
    u_short flags_fo; // Flags (3 bits) + Fragment offset (13 bits)
    u_char  ttl;      // Time to live
    u_char  proto;    // Protocol
    u_short crc;      // Header checksum
    ip_address  saddr; // Source address
    ip_address  daddr; // Destination address
    u_int  op_pad;     // Option + Padding
}ip_header;

/* UDP header*/
typedef struct udp_header {
    u_short sport; // Source port
    u_short dport; // Destination port
    u_short len;   // Datagram length
    u_short crc;   // Checksum
}udp_header;

int interpreter(char* name, PacketCallback cb, void *userData)
{
    pcap_t* adhandle;
    char errbuf[PCAP_ERRBUF_SIZE];
    const struct pcap_pkthdr* header;
    const u_char* pkt_data;
    int res = 0;
    char packet_filter[] = "ip and udp";
    struct bpf_program fcode;
    PacketDetails info;

    /* Load Npcap and its functions. */
    if (!LoadNpcapDlls())
    {
        return -1;
    }

    /* Open the device */
    if ((adhandle = pcap_open(name, // name of the device
        65536, // portion of the packet to capture.
        // 65536 guarantees that the whole packet will
        // be captured on all the link layers
        PCAP_OPENFLAG_PROMISCUOUS, // promiscuous mode
        1000, // read timeout
        NULL, // authentication on the remote machine
        errbuf // error buffer
    )) == NULL)
    {
        return -1;
    }

    /* Check the link layer. We support only Ethernet for simplicity. */
    if (pcap_datalink(adhandle) != DLT_EN10MB)
    {
        return -1;
    }

    bpf_u_int32 netp;
    bpf_u_int32 netmask;

    if (pcap_lookupnet(name, &netp, &netmask, errbuf) == -1){
        netmask = PCAP_NETMASK_UNKNOWN;
    }

    //compile the filter
    if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
    {
        return -1;
    }

    //set the filter
    if (pcap_setfilter(adhandle, &fcode) < 0)
    {
        return -1;
    }

    /* Retrieve the packets */
    while ((res = pcap_next_ex(adhandle, &header, &pkt_data)) >= 0) {

      if (res == 0)
          /* Timeout elapsed */
        continue;

      struct tm ltime;
      char timestr[16];
      ip_header* ih;
      udp_header* uh;
      u_int ip_len;
      u_short sport, dport;
      time_t local_tv_sec;

      /* convert the timestamp to readable format */
      local_tv_sec = header->ts.tv_sec;
      localtime_s(&ltime, &local_tv_sec);
      strftime(timestr, sizeof timestr, "%H:%M:%S", &ltime);

      /* print timestamp and length of the packet */
      snprintf(info.timeStamp, sizeof(info.timeStamp),"%s.%.6d", timestr, header->ts.tv_usec);

      /* retireve the position of the ip header */
      ih = (ip_header*)(pkt_data +
          14); //length of ethernet header

      /* retireve the position of the udp header */
      ip_len = (ih->ver_ihl & 0xf) * 4;
      uh = (udp_header*)((u_char*)ih + ip_len);

      /* convert from network byte order to host byte order */
      sport = ntohs(uh->sport);
      dport = ntohs(uh->dport);

      info.len = header->len;
      snprintf(info.proto, sizeof(info.proto), "%s", "UDP");
      info.sourcePort = sport;
      info.destPort = dport;
      /* print ip addresses and udp ports */
      snprintf(info.sourceIP, sizeof(info.sourceIP), "%d.%d.%d.%d",
          ih->saddr.byte1,
          ih->saddr.byte2,
          ih->saddr.byte3,
          ih->saddr.byte4);

      snprintf(info.destIP, sizeof(info.destIP), "%d.%d.%d.%d",
          ih->daddr.byte1,
          ih->daddr.byte2,
          ih->daddr.byte3,
          ih->daddr.byte4);

        if(cb){
          cb(&info, userData);
        }
    }

    pcap_close(adhandle);
    if (res == -1) {
        return -1;
    }
  return 0;
}
