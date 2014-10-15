#include "corpushandler_global.h"
#include "CorpusHandler.h"

class CORPUSHANDLERSHARED_EXPORT TestingCorpusHandler : public CorpusHandler
{
public:
    TestingCorpusHandler() : CorpusHandler("testing")
    {}
};
