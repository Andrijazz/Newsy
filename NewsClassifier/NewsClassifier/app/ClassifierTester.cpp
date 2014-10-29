#include "ClassifierTester.h"
#include "Tokenizer.h"
#include "PdfGenerator.h"

#include <stdlib.h>
#include <QWidget>


// TODO: Create matrix class

void ClassifierTester::test(boost::shared_ptr< NaiveBayesClassifier > classifier, boost::shared_ptr< QWidget > waitWidget)
{
    boost::shared_ptr< CorpusHandler > corpusHandler(new TestingCorpusHandler());

    unsigned int n = corpusHandler->getNumberOfCategories();

    // intialize confusion matrix
    unsigned int** confusion_matrix = new unsigned int*[n];
    for (unsigned int i = 0; i < n; i++)
    {
        confusion_matrix[i] = new unsigned int[n];
    }

    // set to 0 matrix
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            confusion_matrix[i][j] = 0;
        }
    }

    // test
    while (!corpusHandler->end())
    {
        QString article = corpusHandler->getArticle();

        QString expected_category = Tokenizer::getCategory(article);

        QString result = classifier->classifyNaiveBayesText(article);

        int i = corpusHandler->getCategoryIndex(expected_category);
        int j = corpusHandler->getCategoryIndex(result);

        if (i != -1 && j != -1)
        {
            confusion_matrix[i][j]++;
        }
    }

    QString report = getHtmlReport(confusion_matrix, n, corpusHandler);

    if (PdfGenerator::generatePdf(report))
    {
        waitWidget->close();
        system ("okular test_report.pdf");
    }
    else
    {
        // PROMT MSG BOX ERROR
    }
}


float ClassifierTester::getMacroaveragePrecision(unsigned int** mat, unsigned int n)
{
    float sum = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        sum += getPrecisionForCategory(mat, n, i);
    }
    return sum/n;
}

float ClassifierTester::getMacroaverageRecall(unsigned int** mat, unsigned int n)
{
    float sum = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        sum += getRecallForCategory(mat, n, i);
    }
    return sum/n;
}

float ClassifierTester::getMacroaverageF1(unsigned int** mat, unsigned int n)
{
    float sum = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        sum += getF1ForCategory(mat, n, i);
    }
    return sum/n;
}


float ClassifierTester::getPrecisionForCategory(unsigned int** mat, unsigned int n, unsigned int i)
{
    unsigned int sum = 0;
    for (unsigned int j = 0; j < n; j++)
    {
        sum += mat[j][i];
    }

    return (float) mat[i][i]/sum;
}

float ClassifierTester::getRecallForCategory(unsigned int** mat, unsigned int n, unsigned int i)
{
    int sum = 0;
    for (unsigned int j = 0; j < n; j++)
    {
        sum += mat[i][j];
    }

    return (float) mat[i][i]/sum;
}

float ClassifierTester::getF1ForCategory(unsigned int** mat, unsigned int n, unsigned int i)
{
    float precision = getPrecisionForCategory(mat, n, i), recall = getRecallForCategory(mat, n, i);
    return 2*precision*recall / (precision + recall);
}

//float ClassifierTester::getAccuracy(unsigned int** mat, unsigned int n)
//{
//    unsigned int passed = 0, runned = 0;
//    for (unsigned int i = 0; i < n; i++)
//    {
//        for (unsigned int j = 0; j < n; j++)
//        {
//            if (i == j)
//            {
//                passed += mat[i][j];
//            }

//            runned += mat[i][j];
//        }
//    }

//    return (float)passed/runned;
//}

float ClassifierTester::getMicroaveragePrecision(unsigned int** mat, unsigned int n)
{
    // sum of all diag elems
    unsigned int tp = 0;

    // sum of all elems except diags
    // the sum of fp's is equal to sum of fn's
    unsigned int fp = 0;

    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            if (i == j)
            {
                tp += mat[i][j];
            }
            else
            {
                fp += mat[i][j];
            }
        }
    }
    return (float) tp / (tp + fp);
}

float ClassifierTester::getMicroaverageRecall(unsigned int** mat, unsigned int n)
{
    // sum of all diag elems
    unsigned int tp = 0;

    // sum of all elems except diags
    // the sum of fp's is equal to sum of fn's
    unsigned int fp = 0;

    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            if (i == j)
            {
                tp += mat[i][j];
            }
            else
            {
                fp += mat[i][j];
            }
        }
    }
    return (float) tp / (tp + fp);
}

float ClassifierTester::getMicroaverageF1(unsigned int** mat, unsigned int n)
{
    float precision = getMicroaveragePrecision(mat, n), recall = getMicroaverageRecall(mat, n);
    return 2*precision*recall / (precision + recall);
}

float ClassifierTester::getAccuracyForCategory(unsigned int** mat, unsigned int n, unsigned int i)
{
    unsigned int tp = mat[i][i];
    unsigned int tn = 0;
    for (unsigned int k = 0; k < n; k++)
    {
        if (k != i)
        {
            for (unsigned int j = 0; j < n; j ++)
            {
                if (j != i)
                {
                    tn += mat[k][j];
                }
            }
        }
    }
    unsigned int fp = 0;
    for (unsigned int k = 0; k < n; k++)
    {
        if (k != i)
        {
            fp += mat[k][i];
        }
    }

    unsigned int fn = 0;
    for (unsigned int k = 0; k < n; k++)
    {
        if (k != i)
        {
            fp += mat[i][k];
        }
    }

    return (float)(tp + tn)/(tp + tn + fp + fn);
}

float ClassifierTester::getMacroaverageAccuracy(unsigned int** mat, unsigned int n)
{
    float sum = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        sum += getAccuracyForCategory(mat, n, i);
    }
    return sum/n;
}

float ClassifierTester::getMicroaverageAccuracy(unsigned int ** mat, unsigned int n)
{
    unsigned int tps = 0;
    for (unsigned int k = 0; k < n; k++)
    {
       for (unsigned int j = 0; j < n; j++)
        {
            if (j == k)
            {
                tps += mat[k][j];
            }
        }
    }

    unsigned int tns = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int k = 0; k < n; k++)
        {
            if (k != i)
            {
                for (unsigned int j = 0; j < n; j ++)
                {
                    if (j != i)
                    {
                        tns += mat[k][j];
                    }
                }
            }
        }
    }

    unsigned int sum = 0;
    for (unsigned int k = 0; k < n; k++)
    {
       for (unsigned int j = 0; j < n; j++)
        {
            sum += mat[k][j];
        }
    }

    return (float)(tps + tns)/(n*sum);
}


QString ClassifierTester::getHtmlReport(unsigned int** mat, unsigned int n, boost::shared_ptr< CorpusHandler > corpusHandler)
{
    std::vector<QString> categories = corpusHandler->getCategories();
    QString html;
    html.append(
                "<html>"
                "<head>"
                "</head>"

                "<body>");
    html.append("<div>"
                "<h1 align=center>Naive Bayes Classifier report</h1>"
                "</div>");

    html.append("<p>Corpus name: " + corpusHandler->getCorpusName() + "</p>");
//    html.append("<p>Accuracy: " + QString::number(getAccuracy(mat, n)));

    html.append("<div>");
    html.append("<h2>Confusion matrix</h2>");
    html.append("<p>");

    html.append("<font size=1>");
    html.append("<table>");

    html.append("<tr>");
    html.append("<th>truth/selected</th>");
    for (unsigned int i = 0; i < n; i++)
    {
        html.append("<th>" + categories[i] + "</th>");
    }
    html.append("</tr>");

    for (unsigned int i = 0; i < n; i++)
    {
        html.append("<tr>");
        html.append("<th>" + categories[i] + "</th>");
        for (unsigned int j = 0; j < n; j++)
        {
            html.append("<td align=center>" + QString::number(mat[i][j]) + "</td>");
        }
        html.append("</tr>");
    }


    // stats
    html.append("</table>");
    html.append("</p>");

    html.append("</font>");
    html.append("</div>");

    html.append("<h2>Performance</h2>");
    html.append("<p>");

    html.append("<font size=1>");
    html.append("<table>");

    html.append("<tr>");
    html.append("<th>class/measure</th>");

    html.append("<th>precision</th>");
    html.append("<th>recall</th>");
    html.append("<th>f1</th>");
    html.append("<th>accuracy</th>");

    html.append("</tr>");

    for (unsigned int i = 0; i < n; i++)
    {
        html.append("<tr align=\"left\">");
        html.append("<th>" + categories[i] + "</th>");

        html.append("<td align=center>" + QString::number(getPrecisionForCategory(mat, n, i)) + "</td>");
        html.append("<td align=center>" + QString::number(getRecallForCategory(mat, n, i)) + "</td>");
        html.append("<td align=center>" + QString::number(getF1ForCategory(mat, n, i)) + "</td>");
        html.append("<td align=center>" + QString::number(getAccuracyForCategory(mat, n, i)) + "</td>");

        html.append("</tr>");
    }

    html.append("</table>");

    // MM
    html.append("<br>");

    html.append("<table>");

    html.append("<tr>");
    html.append("<th>mm/measure</th>");

    html.append("<th>precision</th>");
    html.append("<th>recall</th>");
    html.append("<th>f1</th>");
    html.append("<th>accuracy</th>");

    html.append("</tr>");

    html.append("<tr align=\"left\">");
    html.append("<th>macroaverage</th>");

    html.append("<td align=center>" + QString::number(getMacroaveragePrecision(mat, n)) + "</td>");
    html.append("<td align=center>" + QString::number(getMacroaverageRecall(mat, n)) + "</td>");
    html.append("<td align=center>" + QString::number(getMacroaverageF1(mat, n)) + "</td>");
    html.append("<td align=center>" + QString::number(getMacroaverageAccuracy(mat, n)) + "</td>");

    html.append("</tr>");

    html.append("<tr align=\"left\">");

    html.append("<th>microaverage</th>");

    html.append("<td align=center>" + QString::number(getMicroaveragePrecision(mat, n)) + "</td>");
    html.append("<td align=center>" + QString::number(getMicroaverageRecall(mat, n)) + "</td>");
    html.append("<td align=center>" + QString::number(getMicroaverageF1(mat, n)) + "</td>");
    html.append("<td align=center>" + QString::number(getMicroaverageAccuracy(mat, n)) + "</td>");


    html.append("</tr>");

    html.append("</table>");


    html.append("</font>");

    html.append("</p>");
    html.append(
                "</body>"
                "</html>");


    return html;
}
