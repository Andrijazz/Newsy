TEMPLATE = subdirs

SUBDIRS = \
    Tokenizer \
    NaiveBayesClassifier \
    app \
    CorpusHandler \
    ConfigService


app.depends = CorpusHandler
app.depends = Tokenizer
app.depends = NaiveBayesClassifier
app.depends = ConfigService

NaiveBayesClassifier.depends = Tokenizer
NaiveBayesClassifier.depends = CorpusHandler

CorpusHandler.depends = ConfigService

OTHER_FILES += \
    defaults.pri

unix:!macx: LIBS += -L$$OUT_PWD/ConfigService/ -lConfigService

INCLUDEPATH += $$PWD/ConfigService
DEPENDPATH += $$PWD/ConfigService

unix:!macx: LIBS += -L$$OUT_PWD/CorpusHandler/ -lCorpusHandler

INCLUDEPATH += $$PWD/CorpusHandler
DEPENDPATH += $$PWD/CorpusHandler

unix:!macx: LIBS += -L$$OUT_PWD/NaiveBayesClassifier/ -lNaiveBayesClassifier

INCLUDEPATH += $$PWD/NaiveBayesClassifier
DEPENDPATH += $$PWD/NaiveBayesClassifier

unix:!macx: LIBS += -L$$OUT_PWD/Tokenizer/ -lTokenizer

INCLUDEPATH += $$PWD/Tokenizer
DEPENDPATH += $$PWD/Tokenizer
