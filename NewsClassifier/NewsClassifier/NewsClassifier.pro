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
