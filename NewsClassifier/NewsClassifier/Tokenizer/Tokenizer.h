#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "tokenizer_global.h"

#include <map>
#include <QString>

/*
 * Tokenizer is a helper class that tokinizes given articles and extracts
 * all the neccessary informations.
 */

class TOKENIZERSHARED_EXPORT Tokenizer
{

public:
    /*
     * Method creates the map of pairs (word, number_of_occurances)
     * for a given article.
     */
    static std::map<QString, int> parse(QString text);

    /*
     * Extracts the category from a given article if spcified
     * and if not, returns "Unknown"
     */
    static QString getCategory(QString text);
};

#endif // TOKENIZER_H
