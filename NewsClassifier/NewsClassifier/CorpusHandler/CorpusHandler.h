#ifndef CORPUSHANDLER_H
#define CORPUSHANDLER_H

// QT libs
#include <QDir>
#include <QString>
#include <QFileInfo>
#include <QFileInfoList>

// stl
#include <map>
#include <vector>

// boost
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

#define CORPUS_PATH "../../../../corpus"


// #include "corpushandler_global.h"

class CorpusHandler
{
public:

    /*
     * Returns the text of the next article in corpus if everything
     * went well. Otherwise, returns empty string.
     */
    QString getArticle();

    /*
     * Returns true if we have reach the end of corpus
     */
     bool end();

     /*
      * Gets the vector of categories names - readed from config
      */
     std::vector<QString> getCategories();

     /*
      * Gets the number of categories - readed from config
      */
     unsigned int getNumberOfCategories();

     /*
      * Gets the index of a category
      */
     int getCategoryIndex(QString category);

     /*
      * Gets corpus name
      */
      QString getCorpusName();

     /*
      * Returns numbers of training articles available per category
      */
     std::vector<int> numberOfArticlesPerCategory();


protected:

     CorpusHandler(QString purpose);
     ~CorpusHandler();

private:

     /*
      * intialize corpus handler for training or testing
      */
    void initializeFor(QString purpose);

    QFileInfoList getCategoryFileInfoList(QString category, QString purpose);
    QString readFile(QFileInfo fileInfo);

    // TODO: Make it a share pointer
    boost::shared_ptr< std::vector< boost::tuple<QString, QFileInfoList, int> > > m_corpus;
    unsigned int m_iter;

    std::vector<QString> m_categories;

    QString m_corpusName;

};

#endif // CORPUSHANDLER_H
