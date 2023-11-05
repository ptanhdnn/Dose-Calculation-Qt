#include "datamanager.h"

dataManager::dataManager()
{}

void dataManager::createDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("createDatabase");
    db.setDatabaseName("DosePackageManager.db");

    // Get the directory of the database file.
    QString databaseDirectory = db.databaseName();

    // Print the directory of the database file to the console.
    qDebug() << "??????" << databaseDirectory;

    QSqlQuery query("CREATE DATABASE IF NOT EXISTS my_database");
    if (!query.exec()) {
        qDebug() << "Failed to create database.";
    }

    query.prepare("CREATE TABLE IF NOT EXISTS CustomerPackage"
                       "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "CustomerName TEXT,"
                        "PackageType TEXT);");
    if (!query.exec()) {
        qDebug() << "Failed to create CustomerPackage table.";
    }

    query.prepare("CREATE TABLE IF NOT EXISTS DoseCustomer"
                  "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "Date TEXT,"
                  "CustomerName TEXT,"
                  "PackageType TEXT,"
                  "Quantity INTEGER,"
                  "DoseRequired REAL,"
                  "IrradiationTime TEXT,"
                  "Note TEXT,);");
    if (!query.exec()) {
        qDebug() << "Failed to create DoseCustomer table.";
    }
    query.clear();
    db.close();
}

void dataManager::insertCustomerPackage()
{

}

void dataManager::insertDoseCustomer()
{

}
