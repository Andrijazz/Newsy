#ifndef WAITWIDGET_H
#define WAITWIDGET_H

#include <QWidget>

namespace Ui {
class waitwidget;
}

class waitwidget : public QWidget
{
    Q_OBJECT

public:
    explicit waitwidget(QWidget *parent = 0);
    ~waitwidget();

private:
    Ui::waitwidget *ui;
};

#endif // WAITWIDGET_H
