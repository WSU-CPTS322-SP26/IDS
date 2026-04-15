QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
#CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FindAllDevs.c \
    captureWorker.cpp \
    choosedevs.cpp \
    main.cpp \
    mainwindow.cpp \
    packetInterpreter.c

HEADERS += \
    FindAllDevs.h \
    captureWorker.h \
    choosedevs.h \
    mainwindow.h \
    misc.h \
    packetInterpreter.h

FORMS += \
    choosedevs.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#Paths depend on the individual user's directory
NPCAP_SDK = "C:\Users\mitch\Desktop\322_Software Engineering\npcap-sdk-1.16"
INCLUDEPATH += $$NPCAP_SDK/Include
LIBS += -L$$NPCAP_SDK/Lib/x64 -lwpcap -lpacket
LIBS+= -lws2_32

