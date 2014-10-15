#include "selectfeaturedialog.h"
#include "ui_selectfeaturedialog.h"

#include "configservice.h"

SelectFeatureDialog::SelectFeatureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectFeatureDialog)
{
    ui->setupUi(this);
}

SelectFeatureDialog::~SelectFeatureDialog()
{
    delete ui;
}

void SelectFeatureDialog::on_pushButton_clicked()
{
    QString features;
    if (ui->checkBox->isChecked())
    {
        features.append("EliminateStopWordsFeature");
    }
    if (ui->checkBox_2->isChecked())
    {
        features.append(";TFIDFFeature");
    }
    if (ui->checkBox_3->isChecked())
    {
        features.append(";StemmingFeature");
    }
    ConfigService::setConfig("FEATURES", features);
    notifyObservers();
}

void SelectFeatureDialog::registerObserver(boost::shared_ptr< OnFeaturesSetObserver > o)
{
    observers.push_back(o);
}
void SelectFeatureDialog::removeObserver(boost::shared_ptr< OnFeaturesSetObserver > o)
{
    observers.removeOne(o);
}

void SelectFeatureDialog::notifyObservers()
{
    for (QList< boost::shared_ptr< OnFeaturesSetObserver > >::iterator it = observers.begin(); it != observers.end(); it++)
    {
        (*it)->onFeaturesSet();
    }
}
