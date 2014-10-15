#include <QApplication>
#include <QDesktopWidget>
#include <QStyle>

#include <boost/shared_ptr.hpp>

#include "Runtime.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    boost::shared_ptr< Runtime > runtime(new Runtime(a.desktop()->availableGeometry()));

    runtime->start();

    return a.exec();
}
