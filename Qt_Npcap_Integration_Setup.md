# Qt Npcap Integration Setup

## Install and Download Npcap SDK
* <https://npcap.com/>

## Link SDK to Qt project
In .pro file of Qt project add/update these fields:
* NPCAP_SDK = C:\Users\mitch\Desktop\IDS\IDS\npcap-sdk-1.16
* INCLUDEPATH += $$NPCAP_SDK/Include
* LIBS += -L$$NPCAP_SDK/Lib/x64 -lwpcap -lpacket

