/********************************************************************************
** Form generated from reading UI file 'selectfeaturedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTFEATUREDIALOG_H
#define UI_SELECTFEATUREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectFeatureDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QPushButton *pushButton;

    void setupUi(QDialog *SelectFeatureDialog)
    {
        if (SelectFeatureDialog->objectName().isEmpty())
            SelectFeatureDialog->setObjectName(QStringLiteral("SelectFeatureDialog"));
        SelectFeatureDialog->resize(361, 232);
        label = new QLabel(SelectFeatureDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 191, 17));
        label_2 = new QLabel(SelectFeatureDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 110, 201, 17));
        checkBox = new QCheckBox(SelectFeatureDialog);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(20, 40, 191, 22));
        checkBox_2 = new QCheckBox(SelectFeatureDialog);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(20, 70, 98, 22));
        checkBox_3 = new QCheckBox(SelectFeatureDialog);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(20, 140, 191, 22));
        pushButton = new QPushButton(SelectFeatureDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(130, 190, 99, 27));
        pushButton->setAutoDefault(false);

        retranslateUi(SelectFeatureDialog);

        QMetaObject::connectSlotsByName(SelectFeatureDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectFeatureDialog)
    {
        SelectFeatureDialog->setWindowTitle(QApplication::translate("SelectFeatureDialog", "Newsy", 0));
        label->setText(QApplication::translate("SelectFeatureDialog", "Feature selection methods:", 0));
        label_2->setText(QApplication::translate("SelectFeatureDialog", "Feature extraction methods:", 0));
        checkBox->setText(QApplication::translate("SelectFeatureDialog", "Stop words elimination", 0));
        checkBox_2->setText(QApplication::translate("SelectFeatureDialog", "TF-IDF", 0));
        checkBox_3->setText(QApplication::translate("SelectFeatureDialog", "Stemming", 0));
        pushButton->setText(QApplication::translate("SelectFeatureDialog", "Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class SelectFeatureDialog: public Ui_SelectFeatureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTFEATUREDIALOG_H
