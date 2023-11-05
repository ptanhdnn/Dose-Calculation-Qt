/*
 *  Để lưu đường dẫn của database khi cài đặt bước đầu
 */

#ifndef DATABASECONFIG_H
#define DATABASECONFIG_H

#include <QSettings>
#include <QString>

class DatabaseConfig
{
public:
    DatabaseConfig();

    QString databaseFolderPath() const;

    void setDatabaseFolderPath(const QString &databaseFolderPath);

private:
    QSettings settings;
};

#endif // DATABASECONFIG_H

