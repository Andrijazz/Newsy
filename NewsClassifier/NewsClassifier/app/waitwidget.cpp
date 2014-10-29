#include "waitwidget.h"
#include "ui_waitwidget.h"

waitwidget::waitwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::waitwidget)
{
    ui->setupUi(this);
}

waitwidget::~waitwidget()
{
    delete ui;
}
