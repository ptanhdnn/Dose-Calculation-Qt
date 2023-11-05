#include "databaseconfig.h"

DatabaseConfig::DatabaseConfig()
    : settings("MyApp", "Database")
{
}

QString DatabaseConfig::databaseFolderPath() const
{
    return settings.value("database_folder_path").toString();
}

void DatabaseConfig::setDatabaseFolderPath(const QString &databaseFolderPath)
{
    settings.setValue("database_folder_path", databaseFolderPath);
}
