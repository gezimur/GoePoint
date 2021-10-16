TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH +=  $$PWD/../libcppmicrohttpd/include \
                $$PWD/../libhttpserver/src \
                $$PWD/../GeologyDatabase/include \
                $$PWD/../DocFiller/include \

LIBS += -L$$PWD/../PostgreSQL/lib/ \
        -L$$PWD/../GeologyDatabase/lib \
        -L$$PWD/../DocFiller/lib \
        -L$$PWD/../libhttpserver/lib \
        -L$$PWD/../libcppmicrohttpd/lib

LIBS += -lpq -lGeologyDatabase_lib -lDocFiller_lib

LIBS += -lws2_32 -lhttpserver -lmicrohttpd

SOURCES += \
        $$PWD/src/Common/ThreadContainer.cpp \
        $$PWD/src/CommonProcessor.cpp \
        $$PWD/src/GeologyDataBase/DataBaseRequest.cpp \
        $$PWD/src/GeologyDataBase/GeologyDataBase.cpp \
        $$PWD/src/Common/TimeMeter.cpp \
        $$PWD/src/HTTP_staff.cpp \
        $$PWD/src/ManagerProcessor.cpp \
        $$PWD/src/PageContainer.cpp \
        $$PWD/src/RequestProcessor.cpp \
        $$PWD/src/SpecialistProcessor.cpp \
        $$PWD/src/TemplateReader.cpp \
        $$PWD/src/main.cpp

HEADERS += \
    $$PWD/src/Common/ThreadContainer.h \
    $$PWD/src/CommonProcessor.h \
    $$PWD/src/GeologyDataBase/DataBaseRequest.h \
    $$PWD/src/GeologyDataBase/GeologyDataBase.h \
    $$PWD/src/Common/TimeMeter.h \
    $$PWD/src/HTTP_staff.h \
    $$PWD/src/ManagerProcessor.h \
    $$PWD/src/PageContainer.h \
    $$PWD/src/RequestProcessor.h \
    $$PWD/src/SpecialistProcessor.h \
    $$PWD/src/TemplateReader.h

DESTDIR = $$PWD/bin
TARGET = GeologyServer
