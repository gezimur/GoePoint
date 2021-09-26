TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../libhttpserver/src \
                $$PWD/../libcppmicrohttpd/include \
                $$PWD/../GeologyDatabase/src \
                $$PWD/../PostgreSQL/include

LIBS += -L$$PWD/../PostgreSQL/lib/ \
        -L$$PWD/../GeologyDatabase/lib \
        -L$$PWD/../libhttpserver/lib \
        -L$$PWD/../libcppmicrohttpd/lib

LIBS += -lpq -lGeologyDatabase_lib

LIBS += -lws2_32 -lhttpserver -lmicrohttpd

SOURCES += \
        src/AuthorizationPage.cpp \
        src/Common/ThreadContainer.cpp \
        src/GeologyDataBase/DataBaseConnection.cpp \
        src/GeologyDataBase/GeologyDataBase.cpp \
        src/Common/TimeMeter.cpp \
        src/TemplateReader.cpp \
        src/main.cpp

HEADERS += \
    src/AuthorizationPage.h \
    src/Common/ThreadContainer.h \
    src/GeologyDataBase/DataBaseConnection.h \
    src/GeologyDataBase/GeologyDataBase.h \
    src/Common/TimeMeter.h \
    src/TemplateReader.h
