#ifndef TABLE_DATA_H
#define TABLE_DATA_H

#include <QWidget>
#include "databaseheader.h"

namespace Ui {
class table_data;
}

class table_data : public QWidget
{
    Q_OBJECT

public:
    explicit table_data(QWidget *parent = nullptr, const QString &irradiationTime = "");
    ~table_data();

private:
    Ui::table_data *ui;

    QSqlDatabase database;
    QSqlQueryModel *model;


};

#endif // TABLE_DATA_H
