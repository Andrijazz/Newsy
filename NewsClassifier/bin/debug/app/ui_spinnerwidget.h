/********************************************************************************
** Form generated from reading UI file 'spinnerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPINNERWIDGET_H
#define UI_SPINNERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpinnerWidget
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *SpinnerWidget)
    {
        if (SpinnerWidget->objectName().isEmpty())
            SpinnerWidget->setObjectName(QStringLiteral("SpinnerWidget"));
        SpinnerWidget->setWindowModality(Qt::NonModal);
        SpinnerWidget->setEnabled(true);
        SpinnerWidget->resize(71, 61);
        horizontalLayoutWidget = new QWidget(SpinnerWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 71, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(SpinnerWidget);

        QMetaObject::connectSlotsByName(SpinnerWidget);
    } // setupUi

    void retranslateUi(QWidget *SpinnerWidget)
    {
        SpinnerWidget->setWindowTitle(QApplication::translate("SpinnerWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class SpinnerWidget: public Ui_SpinnerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPINNERWIDGET_H
