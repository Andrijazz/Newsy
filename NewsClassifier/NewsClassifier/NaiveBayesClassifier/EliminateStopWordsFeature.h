#ifndef ELIMINATESTOPWORDSFEATURE_H
#define ELIMINATESTOPWORDSFEATURE_H

#include "Feature.h"

// mongo
#include "mongo/client/dbclient.h"

#include <vector>

#include <QString>

class EliminateStopWordsFeature : public Feature
{
public:

    EliminateStopWordsFeature();
    void apply();

private:

    /*
    * stop words
    */
    std::vector<QString> readStopWords();

    mongo::DBClientConnection conn;
};
#endif // ELIMINATESTOPWORDSFEATURE_H
