#ifndef CONFIGSERVICE_H
#define CONFIGSERVICE_H

#include "configservice_global.h"

#include <QString>

class CONFIGSERVICESHARED_EXPORT ConfigService
{
public:
    static void init();
    static void setConfig(QString key, QString value);
    static QString getConfig(QString key);
};

#endif // CONFIGSERVICE_H
