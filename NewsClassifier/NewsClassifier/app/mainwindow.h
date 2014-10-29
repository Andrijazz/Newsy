#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "Subject.h"

#include "OnLearningFinishedCallback.h"
#include "NaiveBayesClassifier.h"
#include "ClassifierTester.h"

#include "waitwidget.h"
#include <boost/thread.hpp>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow, public OnResetSubject,
                    public  OnLearningFinishedCallback, public boost::enable_shared_from_this< MainWindow >
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    virtual void registerObserver(boost::shared_ptr< OnResetObserver > o);
    virtual void removeObserver(boost::shared_ptr< OnResetObserver > o);
    virtual void notifyObservers();


    virtual void onLearningFinishedCallback();


    void initialize();

    void learn();
    void test();

private slots:

    void on_actionClassifier_preformances_triggered();

    void on_actionExit_triggered();

    void on_pushButton_clicked();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;


    boost::shared_ptr< NaiveBayesClassifier > m_classifier;
    boost::shared_ptr< ClassifierTester > m_classifierTester;
    QList< boost::shared_ptr< OnResetObserver > > observers;
    boost::shared_ptr< waitwidget > waitWidget;
};

#endif // MAINWINDOW_H
