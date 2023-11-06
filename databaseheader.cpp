#include "databaseheader.h"
#include <QCoreApplication>

dataHeader::dataHeader()
{}

QString dataHeader::getAppPath()
{
    QString appPath = QCoreApplication::applicationDirPath();
    QString databasePath = appPath + "/databases/database.db";
    return databasePath;
}
