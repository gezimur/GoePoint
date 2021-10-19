TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH +=  $$PWD/../libcppmicrohttpd/include \
                $$PWD/../libhttpserver/src \
                $$PWD/../GoePointDataBase/include \
                $$PWD/../DocFiller/include \
                $$PWD/../boost_1_76_0

LIBS += -L$$PWD/../PostgreSQL/14/lib/ \
        -L$$PWD/../GoePointDataBase/lib \
        -L$$PWD/../DocFiller/lib \
        -L$$PWD/../DuckX/lib \
        -L$$PWD/../libhttpserver/lib \
        -L$$PWD/../libcppmicrohttpd/lib \
        -L$$PWD/../boost_1_76_0/lib

LIBS += -lpq -lGeologyDatabase_lib -lDocFiller_lib -lDuckX_lib

LIBS += -lhttpserver -lmicrohttpd

LIBS += -lboost-filesystem

SOURCES += \
        $$PWD/src/Common/ThreadContainer.cpp \
        $$PWD/src/CommonProcessor.cpp \
        $$PWD/src/GeologyDataBase/DataBaseRequest.cpp \
        $$PWD/src/GeologyDataBase/GeologyDataBase.cpp \
        $$PWD/src/Common/TimeMeter.cpp \
        $$PWD/src/HTTP_staff.cpp \
        $$PWD/src/UserProcessor.cpp \
        $$PWD/src/PageContainer.cpp \
        $$PWD/src/RequestProcessor.cpp \
        $$PWD/src/TemplateReader.cpp \
        $$PWD/src/main.cpp

HEADERS += \
    $$PWD/src/Common/ThreadContainer.h \
    $$PWD/src/CommonProcessor.h \
    $$PWD/src/GeologyDataBase/DataBaseRequest.h \
    $$PWD/src/GeologyDataBase/GeologyDataBase.h \
    $$PWD/src/Common/TimeMeter.h \
    $$PWD/src/HTTP_staff.h \
    $$PWD/src/UserProcessor.h \
    $$PWD/src/PageContainer.h \
    $$PWD/src/RequestProcessor.h \
    $$PWD/src/TemplateReader.h

DESTDIR = $$PWD/bin
TARGET = GeologyServer
