TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lws2_32

SOURCES += \
        ClientSocket.cpp \
        DataBaseRequest.cpp \
        GeologyDataBase.cpp \
        GeologyServer.cpp \
        ServerListenSocket.cpp \
        TimeMeter.cpp \
        main.cpp

HEADERS += \
    ClientSocket.h \
    DataBaseRequest.h \
    GeologyDataBase.h \
    GeologyServer.h \
    ServerListenSocket.h \
    TimeMeter.h
