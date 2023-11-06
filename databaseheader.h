/*
 * Tạo file header về SqlDatabase được hỗ trợ trong qt6
*/

#ifndef DATABASEHEADER_H
#define DATABASEHEADER_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>

class dataHeader
{
public:
    dataHeader();

    QString getAppPath();
};

#endif // DATABASEHEADER_H
