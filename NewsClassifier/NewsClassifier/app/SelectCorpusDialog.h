#ifndef SELECTCORPUSDIALOG_H
#define SELECTCORPUSDIALOG_H

#include <QDialog>
#include <QFileInfoList>
#include <QDir>

#include "Subject.h"
#include "Observer.h"

#include <boost/shared_ptr.hpp>
#include <QList>

namespace Ui {
class SelectCorpusDialog;
}

class SelectCorpusDialog : public QDialog, public OnCorpusSetSubject
{
    Q_OBJECT

public:
    explicit SelectCorpusDialog(QWidget *parent = 0);
    ~SelectCorpusDialog();

    virtual void registerObserver(boost::shared_ptr< OnCorpusSetObserver > o);
    virtual void removeObserver(boost::shared_ptr< OnCorpusSetObserver > o);
    virtual void notifyObservers();

private slots:

    void on_pushButton_clicked();

private:
    QFileInfoList getCorpusFileInfoList();

    Ui::SelectCorpusDialog *ui;

    QList< boost::shared_ptr< OnCorpusSetObserver > > observers;
};

#endif // SELECTCORPUSDIALOG_H
