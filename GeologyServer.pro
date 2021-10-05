TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH +=  $$PWD/../libcppmicrohttpd/include \
                $$PWD/../libhttpserver/src \
                $$PWD/../GeologyDatabase/include

LIBS += -L$$PWD/../PostgreSQL/lib/ \
        -L$$PWD/../GeologyDatabase/lib \
        -L$$PWD/../libhttpserver/lib \
        -L$$PWD/../libcppmicrohttpd/lib

LIBS += -lpq -lGeologyDatabase_lib

LIBS += -lws2_32 -lhttpserver -lmicrohttpd

SOURCES += \
        src/Common/ThreadContainer.cpp \
        src/CommonProcessor.cpp \
        src/GeologyDataBase/DataBaseRequest.cpp \
        src/GeologyDataBase/GeologyDataBase.cpp \
        src/Common/TimeMeter.cpp \
        src/HTTP_staff.cpp \
        src/ManagerProcessor.cpp \
        src/PageContainer.cpp \
        src/RequestProcessor.cpp \
        src/SpecialistProcessor.cpp \
        src/TemplateReader.cpp \
        src/main.cpp

HEADERS += \
    src/Common/ThreadContainer.h \
    src/CommonProcessor.h \
    src/GeologyDataBase/DataBaseRequest.h \
    src/GeologyDataBase/GeologyDataBase.h \
    src/Common/TimeMeter.h \
    src/HTTP_staff.h \
    src/ManagerProcessor.h \
    src/PageContainer.h \
    src/RequestProcessor.h \
    src/SpecialistProcessor.h \
    src/TemplateReader.h
