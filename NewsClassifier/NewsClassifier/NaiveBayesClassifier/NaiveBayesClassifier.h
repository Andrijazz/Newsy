#ifndef NAIVEBAYESCLASSIFIER_H
#define NAIVEBAYESCLASSIFIER_H

#include "naivebayesclassifier_global.h"
#include "OnLearningFinishedCallback.h"
#include "Feature.h"

// mongo
#include "mongo/client/dbclient.h"

#include <vector>

#include <QString>
#include <QList>

class NAIVEBAYESCLASSIFIERSHARED_EXPORT NaiveBayesClassifier
{
public:
    NaiveBayesClassifier();

    QString classifyNaiveBayesText(QString text);

    void learnNaiveBayesText();

    void registerObserver(boost::shared_ptr<OnLearningFinishedCallback> o)
    {
        observers.push_back(o);
    }

    void unregisterObserver(boost::shared_ptr<OnLearningFinishedCallback> o)
    {
        observers.removeOne(o);
    }

    void notifyOnLearningFinished()
    {
        for (int i = 0; i < observers.length(); i++)
        {
            observers[i]->onLearningFinishedCallback();
        }
    }


private:

    // to be changed to public when we don't want learning scenario
    void setup();


    void applyFeatures();

    boost::shared_ptr< Feature > createFeature(QString s);

    mongo::DBClientConnection conn;

    std::vector<QString> m_categories;
    std::vector<int> m_categories_sizes;

    std::vector<long double> pvj;

    int vocabulary;

    std::vector<int> textj;

    // JUST FOR NOW - PROFF OF CONCEPT
    bool tfidf;
    int m_total;
    QList< boost::shared_ptr<OnLearningFinishedCallback> > observers;

};

#endif // NAIVEBAYESCLASSIFIER_H
