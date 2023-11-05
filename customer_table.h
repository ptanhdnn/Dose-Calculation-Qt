/*
 * Tạo bảng để xuất dữ liệu về danh sách các khách hàng
 * và liều chiếu ứng với các loại hàng đã chiếu
*/

#ifndef CUSTOMER_TABLE_H
#define CUSTOMER_TABLE_H

#include <QDialog>
#include "databaseheader.h"

namespace Ui {
class Customer_table;
}

class Customer_table : public QDialog
{
    Q_OBJECT

public:
    explicit Customer_table(QWidget *parent = nullptr);
    ~Customer_table();

private slots:
    void onCloseButtonClicked();

private:
    Ui::Customer_table *ui;

    QSqlDatabase database;
    QSqlQueryModel *model;
};

#endif // CUSTOMER_TABLE_H
