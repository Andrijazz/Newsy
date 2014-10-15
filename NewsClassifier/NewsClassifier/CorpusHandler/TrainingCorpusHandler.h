#include "corpushandler_global.h"
#include "CorpusHandler.h"

class CORPUSHANDLERSHARED_EXPORT TrainingCorpusHandler : public CorpusHandler
{
public:
    TrainingCorpusHandler() : CorpusHandler("training"){}
};
