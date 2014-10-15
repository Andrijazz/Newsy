#ifndef SELECTFEATUREDIALOG_H
#define SELECTFEATUREDIALOG_H

#include <QDialog>
#include <QList>
#include <boost/shared_ptr.hpp>

#include "Subject.h"

namespace Ui {
class SelectFeatureDialog;
}

class SelectFeatureDialog : public QDialog, public OnFeaturesSetSubject
{
    Q_OBJECT

public:
    explicit SelectFeatureDialog(QWidget *parent = 0);
    ~SelectFeatureDialog();

    virtual void registerObserver(boost::shared_ptr< OnFeaturesSetObserver > o);
    virtual void removeObserver(boost::shared_ptr< OnFeaturesSetObserver > o);
    virtual void notifyObservers();

private slots:

    void on_pushButton_clicked();

private:
    Ui::SelectFeatureDialog *ui;
    QList< boost::shared_ptr< OnFeaturesSetObserver > > observers;
};

#endif // SELECTFEATUREDIALOG_H
