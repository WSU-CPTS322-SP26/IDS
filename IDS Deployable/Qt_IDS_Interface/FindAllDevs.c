/*
 * The following code retrieves the adapter list and prints the complete contents
 * of each pcap_if structure, printing an error if no adapters are found.
 * Tutorial Link: https://npcap.com/guide/npcap-tutorial.html
 */

#include "FindAllDevs.h"

pcap_if_t* FindAllDevs()
{
    pcap_if_t* alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];

    /* Retrieve the device list from the local machine */
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING,
        NULL /* auth is not needed */,
        &alldevs, errbuf) == -1)
    {
      return NULL;
    }
    return alldevs;
}
