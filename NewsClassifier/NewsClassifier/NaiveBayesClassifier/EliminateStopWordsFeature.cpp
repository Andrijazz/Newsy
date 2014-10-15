#include "EliminateStopWordsFeature.h"

#include <QDir>
#include <QFile>
#include <QTextStream>

#define CONFIG_PATH "../../../../config"

EliminateStopWordsFeature::EliminateStopWordsFeature()
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

}

void EliminateStopWordsFeature::apply()
{
    std::vector<QString> stopwords = readStopWords();

    // Build an array
    mongo::BSONArrayBuilder words_arr;

    for (std::vector<QString>::const_iterator it = stopwords.begin(); it != stopwords.end(); it++)
    {
        words_arr.append((*it).toStdString().c_str());
    }

    conn.remove("NewsVocabulary.Vocabulary", BSON("_id" << BSON("$in" << words_arr.arr())));
}

std::vector<QString> EliminateStopWordsFeature::readStopWords()
{
    std::vector<QString> stop_words;
    QString path = CONFIG_PATH;
    path.append( "/stopwords.txt");
    QFile file(path);
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd())
            {
                stop_words.push_back(in.readLine());
            }
        }
    }

    return stop_words;
}
