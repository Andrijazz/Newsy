#ifndef OBSERVER_H
#define OBSERVER_H


class OnCorpusSetObserver
{
public:
    virtual void onCorpusSet() = 0;
};

class OnFeaturesSetObserver
{
public:
    virtual void onFeaturesSet() = 0;
};

class OnResetObserver
{
public:
    virtual void onReset() = 0;
};
#endif // OBSERVER_H
