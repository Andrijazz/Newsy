#ifndef SPINNERWIDGET_H
#define SPINNERWIDGET_H

#include <QWidget>
#include "QtWaitingSpinner.h"

#include <boost/shared_ptr.hpp>

namespace Ui {
class SpinnerWidget;
}

class SpinnerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SpinnerWidget(QWidget *parent = 0);
    ~SpinnerWidget();

    void start();

private:
    Ui::SpinnerWidget *ui;
    boost::shared_ptr< QtWaitingSpinner > m_spinner;
};

#endif // SPINNERWIDGET_H
