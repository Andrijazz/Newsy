#ifndef RUNTIME_H
#define RUNTIME_H

#include "SelectCorpusDialog.h"
#include "selectfeaturedialog.h"
#include "mainwindow.h"

#include "Observer.h"
#include <boost/shared_ptr.hpp>

#include <QRect>

class Runtime : public OnCorpusSetObserver, public OnFeaturesSetObserver, public OnResetObserver,
        public boost::enable_shared_from_this< Runtime >
{
public:
    Runtime(QRect geo);
    ~Runtime();

    void start();

    virtual void onCorpusSet();
    virtual void onFeaturesSet();
    virtual void onReset();

private:
    boost::shared_ptr< SelectCorpusDialog > corpusSetDialog;
    boost::shared_ptr< SelectFeatureDialog > featureSetDialog;
    boost::shared_ptr< MainWindow > main_window;


    QRect geometry;

};
#endif // RUNTIME_H
