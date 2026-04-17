# Qt Npcap Integration Setup

## Install and Download Npcap SDK
* <https://npcap.com/>

## Link SDK to Qt project
In .pro file of Qt project add/update the fields below. 
(If the SDK installed correctly, just add the path and that is all that should be needed.)
* NPCAP_SDK = C:\Users\mitch\Desktop\IDS\IDS\npcap-sdk-1.16
* INCLUDEPATH += $$NPCAP_SDK/Include
* LIBS += -L$$NPCAP_SDK/Lib/x64 -lwpcap -lpacket

After updating the .pro file run qmake and rebuild project.

Now the program can be run.
