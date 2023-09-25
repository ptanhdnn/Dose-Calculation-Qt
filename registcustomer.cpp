#include "registcustomer.h"
#include "ui_registcustomer.h"

#include "databaseheader.h"
#include <QFile>
#include <QMessageBox>

RegistCustomer::RegistCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistCustomer)
{
    ui->setupUi(this);
}

RegistCustomer::~RegistCustomer()
{
    delete ui;
}

void RegistCustomer::on_btn_cancel_clicked()
{
    close();
}

void RegistCustomer::on_btn_save_clicked()
{
    QString companyName = ui->line_customerName->text().toLower();
    companyName[0]=companyName[0].toUpper();
    QString packageType = ui->line_package_type->text().toLower();
    packageType[0] = packageType[0].toUpper();

    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE", "add_new_package");
    dataBase.setDatabaseName("D:/project/DoseCalculation/databases/DosePackageManager.db");

    if(!QFile::exists("D:/project/DoseCalculation/databases/DosePackageManager.db")){
        QMessageBox::warning(this, "File Not Found", "Không tìm thấy database file");
    }
    qDebug() << "found it" ;

    if(dataBase.open()){
        QSqlQuery query(dataBase);

        if(query.exec("SELECT * FROM CustomerPackage")){
            query.prepare("INSERT INTO CustomerPackage(CustomerName, PackageType)"
                          "VALUES(:companyName, :packageType)");

            query.bindValue(":companyName", companyName);
            query.bindValue(":packageType", packageType);

            query.exec();
            qDebug() << "Last Error: " << query.lastError().text();
            query.finish();
        }
        dataBase.close();
    } else {
        QMessageBox::warning(this, "File Not Open", "Không thể mở database file");
        return;
    }

    this->close();
}

