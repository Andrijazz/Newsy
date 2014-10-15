/********************************************************************************
** Form generated from reading UI file 'SelectCorpusDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTCORPUSDIALOG_H
#define UI_SELECTCORPUSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectCorpusDialog
{
public:
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *pushButton;

    void setupUi(QDialog *SelectCorpusDialog)
    {
        if (SelectCorpusDialog->objectName().isEmpty())
            SelectCorpusDialog->setObjectName(QStringLiteral("SelectCorpusDialog"));
        SelectCorpusDialog->resize(214, 148);
        label = new QLabel(SelectCorpusDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 161, 17));
        comboBox = new QComboBox(SelectCorpusDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(10, 50, 191, 27));
        pushButton = new QPushButton(SelectCorpusDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 90, 191, 27));
        pushButton->setAutoFillBackground(false);
        pushButton->setText(QStringLiteral("Ok"));
        pushButton->setAutoDefault(false);

        retranslateUi(SelectCorpusDialog);

        QMetaObject::connectSlotsByName(SelectCorpusDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectCorpusDialog)
    {
        SelectCorpusDialog->setWindowTitle(QApplication::translate("SelectCorpusDialog", "Newsy", 0));
        label->setText(QApplication::translate("SelectCorpusDialog", "Select  corpus:", 0));
    } // retranslateUi

};

namespace Ui {
    class SelectCorpusDialog: public Ui_SelectCorpusDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTCORPUSDIALOG_H
