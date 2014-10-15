#include "configservice.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>

#define CONFIG_PATH "../../../../config"

void ConfigService::init()
{
    QFile file("../../../../config/config.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
}

void ConfigService::setConfig(QString key, QString value)
{
    QFile file("../../../../config/config.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << key << ":" << value << "\n";
}

QString ConfigService::getConfig(QString key)
{
    QFile file("../../../../config/config.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.startsWith(key))
        {
            QString value = line.split(":").back();
            return value;
        }
    }

    return "";
}
