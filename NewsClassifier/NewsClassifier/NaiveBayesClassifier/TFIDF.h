#ifndef TFIDF_H
#define TFIDF_H

#include "Feature.h"

// TODO: CURRENTLY IT DOES NOTHING - FIX THIS SHIT
class TFIDF : public Feature
{
public:

    TFIDF();
    void apply();

private:
    bool active;
};
#endif // TFIDF_H
