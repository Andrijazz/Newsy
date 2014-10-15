#include "PdfGenerator.h"

#include <QString>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QRect>

#include <QMargins>
bool PdfGenerator::generatePdf(QString html)
{
    QString fileName = "test_report.pdf";

    if (fileName.length() == 0)
        return false;

    if (!fileName.contains(".pdf", Qt::CaseSensitive))
        return false;

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    printer.setPageMargins(15, 20, 15, 20, QPrinter::Unit());

    QPainter painter(&printer);

//    painter.setWindow(50, 50, printer.width() - 50, printer.height() - 50);
//    painter.window().setRect(100, printer.);
//    int printerWidth = printer.pageRect().width();
//    int printerHeight = printer.pageRect().height();
//    float xscale = (float)printerWidth/100;
//    float yscale = (float)printerHeight/100;
//    float scale = qMin(xscale, yscale);
//    painter.scale((qreal)scale, (qreal)scale);
    //here we start painting to the printer
//    if (!painter.begin(&printer))
//        return false;

    QTextDocument doc;
 //   doc.setDocumentMargin((qreal)50);

    QFont font("courier", 10);

    doc.setDefaultFont(font);
    doc.setHtml(html);

    doc.drawContents(&painter);

//    painter.end();
    return true;
}
