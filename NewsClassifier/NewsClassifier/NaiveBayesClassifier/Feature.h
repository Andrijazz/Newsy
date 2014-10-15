#ifndef FEATURE_H
#define FEATURE_H

#include "naivebayesclassifier_global.h"

class NAIVEBAYESCLASSIFIERSHARED_EXPORT Feature
{
public:
    virtual void apply() = 0;
};
#endif // FEATURE_H
