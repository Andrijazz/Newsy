#-------------------------------------------------
#
# Project created by QtCreator 2014-07-27T16:55:57
#
#-------------------------------------------------

include(../defaults.pri)

QT       -= gui

LIBS += -L../ConfigService -lConfigService

TARGET = CorpusHandler
TEMPLATE = lib

DEFINES += CORPUSHANDLER_LIBRARY

SOURCES += CorpusHandler.cpp \
    TrainingCorpusHandler.cpp \
    TestingCorpusHandler.cpp

HEADERS +=\
        corpushandler_global.h \
    CorpusHandler.h \
    TrainingCorpusHandler.h \
    TestingCorpusHandler.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
