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

    boost::thread spinnerThread(&Runtime::spin, this);
    spinnerThread.join();

    main_window.reset(new MainWindow);
    main_window->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, main_window->size(), geometry));
    main_window->initialize();
    main_window->registerObserver(shared_from_this());
}

void Runtime::spin()
{

    spinnerWidget.reset(new SpinnerWidget);
    spinnerWidget->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, spinnerWidget->size(), geometry));
    spinnerWidget->setWindowFlags(Qt::CustomizeWindowHint);

    spinnerWidget->start();
    spinnerWidget->show();

}

void Runtime::onReset()
{
    main_window->close();
    start();
}
