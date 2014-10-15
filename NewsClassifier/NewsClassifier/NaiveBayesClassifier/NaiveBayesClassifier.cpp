#include "NaiveBayesClassifier.h"

// boost
#include <boost/shared_ptr.hpp>

#include "TrainingCorpusHandler.h"
#include "Tokenizer.h"

#include <iostream>
#include <math.h>

#include "configservice.h"
#include "EliminateStopWordsFeature.h"

NaiveBayesClassifier::NaiveBayesClassifier()
{
    // initialize mongo client and connect to mongo server

    const char *port = "27017";
//    mongo::Status status = mongo::client::initialize();
//    if (!status.isOK())
//    {
//        std::cout << "Failed to initialize the client driver: " << status.toString() << std::endl;
//        return;
//    }

    std::string errmsg;
    if (!conn.connect( std::string("127.0.0.1:") + port, errmsg))
    {
        std::cout << "couldn't connect : " << errmsg << std::endl;
        // TODO: promt msg box
        return;
    }

    tfidf = false;
}

void NaiveBayesClassifier::learnNaiveBayesText()
{
    // clear collection
    mongo::BSONObjBuilder query;
    conn.remove("NewsVocabulary.Vocabulary" , query.obj());

    // intialize FileHandler for training purposes
    boost::shared_ptr< CorpusHandler > fh(new TrainingCorpusHandler());

    m_categories = fh->getCategories();
    m_categories_sizes = fh->numberOfArticlesPerCategory();
    m_total = 0;
    for (std::vector<int>::const_iterator it = m_categories_sizes.begin(); it != m_categories_sizes.end(); it++)
    {
        m_total += *it;
    }

    while (!fh->end())
    {
        QString text = fh->getArticle();
        std::map<QString, int> article = Tokenizer::parse(text);
        QString category = Tokenizer::getCategory(text);

        // TODO: TRY TO MAKE JUST ONE CALL TO DB WITH VECTOR OF WORDS
        for (std::map<QString, int>::const_iterator it = article.begin(); it != article.end(); it++)
        {
            mongo::Query query(BSON("_id" << (it->first).toStdString().c_str()));
            conn.update("NewsVocabulary.Vocabulary", query, BSON( "$inc" << BSON(category.toStdString().c_str() << it->second
                                                                                 << QString("df").toStdString().c_str() << 1)), true, false);
        }
    }

    setup();
    applyFeatures();
    notifyOnLearningFinished();
}

void NaiveBayesClassifier::setup()
{
    // calculate pvj
    for (unsigned int j = 0; j < m_categories.size(); j++)
    {
        pvj.push_back((long double)1 / m_categories_sizes[j]);
    }

    vocabulary = conn.count("NewsVocabulary.Vocabulary");

    // textj
    for (std::vector<QString>::const_iterator it = m_categories.begin(); it != m_categories.end(); it++)
    {
        int n = conn.count("NewsVocabulary.Vocabulary", BSON((*it).toStdString().c_str() << BSON("$exists" << "true")));
        textj.push_back(n);
    }
}

void NaiveBayesClassifier::applyFeatures()
{
    QString featuresString = ConfigService::getConfig("FEATURES");
    QStringList features = featuresString.split(";");
    for (QStringList::iterator it = features.begin(); it != features.end(); it++)
    {
        boost::shared_ptr< Feature > f = createFeature(*it);
        if (f != NULL)
        {
            f->apply();
        }
    }
}

boost::shared_ptr< Feature > NaiveBayesClassifier::createFeature(QString s)
{
    boost::shared_ptr< Feature > f;

    if (s == "EliminateStopWordsFeature")
    {
        f.reset(new EliminateStopWordsFeature);
    }
    if (s == "TFIDFFeature")
    {
        //f.reset(new TFIDF);
        tfidf = true;
    }
    return f;
}


QString NaiveBayesClassifier::classifyNaiveBayesText(QString text)
{
    std::map<QString, int> bag_of_words = Tokenizer::parse(text);

    // FIX: Create BSON with all queries and than make just one query to the db
    std::vector<mongo::BSONObj> nks;
    for (std::map<QString, int>::const_iterator it = bag_of_words.begin(); it != bag_of_words.end(); it++)
    {
        mongo::BSONObj word = conn.findOne("NewsVocabulary.Vocabulary", BSON("_id" << (it->first).toStdString().c_str()));
        if (word.isEmpty())
            continue;
        nks.push_back(word);
    }

    std::vector<long double> pj;
    for (unsigned int j = 0; j < m_categories.size(); j++)
    {
        long double temp = 0;
        for (unsigned int i = 0; i < nks.size(); i++)
        {
            // how many times the word apears in the category
            int nk = 0;
            if (nks[i].hasField(m_categories[j].toStdString()))
            {
                mongo::BSONElement e = nks[i].getField(m_categories[j].toStdString());
                nk = e.numberInt();
            }

            long double value;

            // TODO: FIX - this is just proof of concept.
            if (tfidf)
            {
                // in how many documents word appears
                int df = 0;
                if (nks[i].hasField("df"))
                {
                    mongo::BSONElement e = nks[i].getField("df");
                    df = e.numberInt();
                }

                int tf;
                float idf;
                tf = nk;
                idf = (float)m_total/df;
                value = (long double)(tf*idf + 1) / (textj[j] + vocabulary);
                temp += std::log(value);

            }
            else
            {
                value = (long double)(nk + 1) / (textj[j] + vocabulary);
                temp += std::log(value);
            }
        }
        long double res = std::log(pvj[j]) + temp;
        pj.push_back(res);
    }

    int max_category_index = 0;
    for (unsigned int j = 0; j < pj.size(); j++)
    {
        if (pj[j] > pj[max_category_index])
        {
            max_category_index = j;
        }
    }

    return m_categories[max_category_index];
}

void NaiveBayesClassifier::registerObserver(boost::shared_ptr<OnLearningFinishedCallback> o)
{
    observers.push_back(o);
}

void NaiveBayesClassifier::unregisterObserver(boost::shared_ptr<OnLearningFinishedCallback> o)
{
    observers.removeOne(o);
}

void NaiveBayesClassifier::notifyOnLearningFinished()
{
    for (int i = 0; i < observers.length(); i++)
    {
        observers[i]->onLearningFinishedCallback();
    }
}
