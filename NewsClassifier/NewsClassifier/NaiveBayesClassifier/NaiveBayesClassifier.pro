#-------------------------------------------------
#
# Project created by QtCreator 2014-06-21T19:46:11
#
#-------------------------------------------------

include(../defaults.pri)

QT       -= gui

TARGET = NaiveBayesClassifier
TEMPLATE = lib

DEFINES += NAIVEBAYESCLASSIFIER_LIBRARY

SOURCES += NaiveBayesClassifier.cpp \
    EliminateStopWordsFeature.cpp \
    TFIDF.cpp

HEADERS += NaiveBayesClassifier.h\
        naivebayesclassifier_global.h \
    EliminateStopWordsFeature.h \
    Feature.h \
    TFIDF.h \
    OnLearningFinishedCallback.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -lfl -pthread -lmongoclient -lboost_thread -lboost_system -lboost_filesystem -lboost_program_options\
            -L../Tokenizer -lTokenizer -L../CorpusHandler -lCorpusHandler
