#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    m_classifier.reset(new NaiveBayesClassifier());
    m_classifier->registerObserver(shared_from_this());
    m_classifier->learnNaiveBayesText();
}

void MainWindow::on_actionClassifier_preformances_triggered()
{
    ClassifierTester::test(m_classifier);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    QString category = m_classifier->classifyNaiveBayesText(text);

    ui->textEdit->clear();
    ui->textEdit->insertPlainText(category);
}

void MainWindow::registerObserver(boost::shared_ptr< OnResetObserver > o)
{
    observers.push_back(o);
}
void MainWindow::removeObserver(boost::shared_ptr< OnResetObserver > o)
{
    observers.removeOne(o);
}
void MainWindow::notifyObservers()
{
    for (QList< boost::shared_ptr< OnResetObserver > >::iterator it = observers.begin(); it != observers.end(); it++)
    {
        (*it)->onReset();
    }
}

void MainWindow::on_actionSettings_triggered()
{
    notifyObservers();
}

void MainWindow::onLearningFinishedCallback()
{
    show();
}
