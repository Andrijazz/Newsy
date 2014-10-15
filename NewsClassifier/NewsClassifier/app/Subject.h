#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <boost/shared_ptr.hpp>

class OnCorpusSetSubject
{
public:
    virtual void registerObserver(boost::shared_ptr< OnCorpusSetObserver > o) = 0;
    virtual void removeObserver(boost::shared_ptr< OnCorpusSetObserver > o) = 0;
    virtual void notifyObservers() = 0;
};

class OnFeaturesSetSubject
{
public:
    virtual void registerObserver(boost::shared_ptr< OnFeaturesSetObserver > o) = 0;
    virtual void removeObserver(boost::shared_ptr< OnFeaturesSetObserver > o) = 0;
    virtual void notifyObservers() = 0;
};

class OnResetSubject
{
public:
    virtual void registerObserver(boost::shared_ptr< OnResetObserver > o) = 0;
    virtual void removeObserver(boost::shared_ptr< OnResetObserver > o) = 0;
    virtual void notifyObservers() = 0;
};

#endif // SUBJECT_H
