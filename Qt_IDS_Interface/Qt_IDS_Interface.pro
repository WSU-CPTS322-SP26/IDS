QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
#CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#INCLUDEPATH += "C:/Users/mitch/Desktop/IDS/IDS/npcap-sdk-1.16/Include"
#LIBS += "C:/Users/mitch/Desktop/IDS/IDS/npcap-sdk-1.16/Lib/x64/wpcap.lib"
#LIBS += "C:/Users/mitch/Desktop/IDS/IDS/npcap-sdk-1.16/Lib/x64/Packet.lib"
#LIBS += -lws2_32
