#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "databaseheader.h"


class dataManager
{
public:
    dataManager();
    void createDatabase();
    void insertCustomerPackage();
    void insertDoseCustomer();

    QString dataPath;
};

#endif // DATAMANAGER_H
