#ifndef CLASSIFIERTESTER_H
#define CLASSIFIERTESTER_H

#include "TestingCorpusHandler.h"
#include "NaiveBayesClassifier.h"

#include <boost/shared_ptr.hpp>

#include <vector>

#include <QString>

class ClassifierTester
{
public:
    static void test(boost::shared_ptr< NaiveBayesClassifier > classifier, boost::shared_ptr< QWidget > waitWidget);

private:

    void show();

    static QString getHtmlReport(unsigned int** mat, unsigned int n, boost::shared_ptr< CorpusHandler > CorpusHandler);

    // per category measures

    static float getPrecisionForCategory(unsigned int** mat, unsigned int n, unsigned int i);

    static float getRecallForCategory(unsigned int** mat, unsigned int n, unsigned int i);

    static float getF1ForCategory(unsigned int** mat, unsigned int n, unsigned int i);

    static float getAccuracyForCategory(unsigned int** mat, unsigned int n, unsigned int i);


    // global measures

    // Macro
    static float getMacroaveragePrecision(unsigned int** mat, unsigned int n);

    static float getMacroaverageRecall(unsigned int** mat, unsigned int n);

    static float getMacroaverageF1(unsigned int** mat, unsigned int n);

    static float getMacroaverageAccuracy(unsigned int** mat, unsigned int n);

    // Micro

    static float getMicroaveragePrecision(unsigned int** mat, unsigned int n);

    static float getMicroaverageRecall(unsigned int** mat, unsigned int n);

    static float getMicroaverageF1(unsigned int** mat, unsigned int n);

    static float getMicroaverageAccuracy(unsigned int** mat, unsigned int n);

};
#endif // CLASSIFIERTESTER_H
