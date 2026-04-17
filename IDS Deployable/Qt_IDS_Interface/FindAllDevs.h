#ifndef FINDALLDEVS_H
#define FINDALLDEVS_H
#include "pcap.h"

#ifdef __cplusplus
    extern "C"{
#endif
        pcap_if_t* FindAllDevs();
#ifdef __cplusplus
    }
#endif
#endif // FINDALLDEVS_H
