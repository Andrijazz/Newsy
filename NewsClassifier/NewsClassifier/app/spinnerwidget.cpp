#include "spinnerwidget.h"
#include "ui_spinnerwidget.h"

SpinnerWidget::SpinnerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpinnerWidget)
{
    ui->setupUi(this);
    m_spinner.reset(new QtWaitingSpinner(this));
    m_spinner->setRoundness(70.0);
    m_spinner->setColor(QColor(81, 4, 71));

    QVBoxLayout *spinnerLayout = new QVBoxLayout;
    spinnerLayout->insertWidget(0, m_spinner.get());
    spinnerLayout->insertStretch(0);
    spinnerLayout->addStretch();
    ui->horizontalLayout->insertLayout(1, spinnerLayout);
}

void SpinnerWidget::start()
{
    m_spinner->start();
}

SpinnerWidget::~SpinnerWidget()
{
    delete ui;
}
