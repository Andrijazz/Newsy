#include "SelectCorpusDialog.h"
#include "ui_SelectCorpusDialog.h"

#include "mainwindow.h"

#define CORPUS_PATH "../../../../corpus"

#include "configservice.h"


SelectCorpusDialog::SelectCorpusDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectCorpusDialog)
{
    ui->setupUi(this);

    // load list of available corpuses
    QFileInfoList list = getCorpusFileInfoList();
    foreach (QFileInfo f, list)
    {
        if (f.baseName() != "")
        {
            ui->comboBox->addItem(f.baseName());
        }
    }
}

QFileInfoList SelectCorpusDialog::getCorpusFileInfoList()
{
    QString path = CORPUS_PATH;
    QDir dir(path);
    if (dir.exists())
    {
        return dir.entryInfoList(QDir::Dirs);
    }
    return QFileInfoList();
}

SelectCorpusDialog::~SelectCorpusDialog()
{
    delete ui;
}

void SelectCorpusDialog::registerObserver(boost::shared_ptr< OnCorpusSetObserver > o)
{
    observers.push_back(o);
}
void SelectCorpusDialog::removeObserver(boost::shared_ptr< OnCorpusSetObserver > o)
{
    observers.removeOne(o);
}
void SelectCorpusDialog::notifyObservers()
{
    for (QList< boost::shared_ptr< OnCorpusSetObserver > >::iterator it = observers.begin(); it != observers.end(); it++)
    {
        (*it)->onCorpusSet();
    }
}

void SelectCorpusDialog::on_pushButton_clicked()
{
    QString corpus = ui->comboBox->currentText();
    ConfigService::setConfig("CORPUS", corpus);
    notifyObservers();
}
