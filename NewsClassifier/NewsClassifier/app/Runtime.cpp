#include "Runtime.h"
#include <QStyle>

#include "configservice.h"
#include <boost/thread.hpp>

Runtime::Runtime(QRect geo): geometry(geo)
{}

Runtime::~Runtime()
{}


void Runtime::start()
{
    ConfigService::init();

    corpusSetDialog.reset(new SelectCorpusDialog);
    corpusSetDialog->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, corpusSetDialog->size(), geometry));
    corpusSetDialog->show();

    corpusSetDialog->registerObserver(shared_from_this());
}

void Runtime::onCorpusSet()
{
    corpusSetDialog->close();

    featureSetDialog.reset(new SelectFeatureDialog);
    featureSetDialog->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, featureSetDialog->size(), geometry));
    featureSetDialog->show();

    featureSetDialog->registerObserver(shared_from_this());
}

void Runtime::onFeaturesSet()
{
    featureSetDialog->close();

    main_window.reset(new MainWindow);
    main_window->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, main_window->size(), geometry));
    main_window->initialize();
    main_window->show();

    main_window->registerObserver(shared_from_this());
}

void Runtime::onReset()
{
    main_window->close();
    start();
}
