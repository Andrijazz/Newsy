#-------------------------------------------------
#
# Project created by QtCreator 2014-06-26T17:11:23
#
#-------------------------------------------------

include(../defaults.pri)

LIBS += -L../Tokenizer -lTokenizer -L../ConfigService -lConfigService  -L../CorpusHandler -lCorpusHandler\
 -L../NaiveBayesClassifier -lNaiveBayesClassifier -lboost_system -lboost_thread

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    PdfGenerator.cpp \
    ClassifierTester.cpp \
    SelectCorpusDialog.cpp \
    Runtime.cpp \
    selectfeaturedialog.cpp \
    QtWaitingSpinner.cpp \
    spinnerwidget.cpp

HEADERS  += mainwindow.h \
    PdfGenerator.h \
    ClassifierTester.h \
    SelectCorpusDialog.h \
    Subject.h \
    Observer.h \
    Runtime.h \
    Feature.h \
    selectfeaturedialog.h \
    QtWaitingSpinner.h \
    spinnerwidget.h

FORMS    += mainwindow.ui \
    SelectCorpusDialog.ui \
    selectfeaturedialog.ui \
    spinnerwidget.ui
