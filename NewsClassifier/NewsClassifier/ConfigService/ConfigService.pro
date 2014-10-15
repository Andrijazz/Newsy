#-------------------------------------------------
#
# Project created by QtCreator 2014-07-29T00:38:29
#
#-------------------------------------------------

QT       -= gui

TARGET = ConfigService
TEMPLATE = lib

DEFINES += CONFIGSERVICE_LIBRARY

SOURCES += configservice.cpp

HEADERS += configservice.h\
        configservice_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
