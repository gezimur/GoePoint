TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lws2_32

SOURCES += \
        src/ClientProcessor.cpp \
        src/Common/ThreadContainer.cpp \
        src/GeologyDataBase/DataBaseConnection.cpp \
        src/GeologyDataBase/GeologyDataBase.cpp \
        src/GeologyServer.cpp \
        src/ServerListenSocket.cpp \
        src/Common/TimeMeter.cpp \
        src/main.cpp

HEADERS += \
    src/ClientProcessor.h \
    src/Common/ThreadContainer.h \
    src/GeologyDataBase/DataBaseConnection.h \
    src/GeologyDataBase/GeologyDataBase.h \
    src/GeologyServer.h \
    src/ServerListenSocket.h \
    src/Common/TimeMeter.h
