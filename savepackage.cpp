#include "savepackage.h"
#include "ui_savepackage.h"

#include <QMessageBox>
#include <QFile>
#include <QDate>
#include <QStringListModel>
#include <QSet>

SavePackage::SavePackage(QWidget *parent, const QString& irradiationTime, float numDose) :
    QDialog(parent),
    ui(new Ui::SavePackage)
{
    ui->setupUi(this);

    this->irradiationTime = irradiationTime;
    this->numDose = numDose;

    ui->line_dose_required->setText(QString::number(numDose));
    ui->line_irradiation_time->setText(irradiationTime);

    companyCompleter = new QCompleter(this);
    packageTypeCompleter = new QCompleter(this);

    // sử dụng khi deploy app
    //    QString databasePath = dataPath.getAppPath();
    //    database = QSqlDatabase::addDatabase("QSQLITE", "save_package");
    //    database.setDatabaseName(databasePath);

    db_customer = QSqlDatabase::addDatabase("QSQLITE", "add_package");
    db_customer.setDatabaseName("D:/project/test/databases/DosePackageManager.db");

    if (!QFile::exists("D:/project/test/databases/DosePackageManager.db")) {
        QMessageBox::warning(this, "File Not Found", "Không tìm thấy database file");
    }

    if (db_customer.open()) {
        QSqlQuery query("SELECT CustomerName, PackageType FROM CustomerPackage", db_customer);

        QSet<QString> uniqueCompanyNames;
        QSet<QString> uniquePackageTypes;

        while (query.next()) {
            QString sugestCompanyName = query.value(0).toString(); // Index 0 is for CustomerName
            QString sugestPackageType = query.value(1).toString(); // Index 1 is for PackageType

            sugestCompanyNames.append(sugestCompanyName);
            sugestPackageTypes.append(sugestPackageType);

            uniqueCompanyNames.insert(sugestCompanyName); // Insert company names into the set
            uniquePackageTypes.insert(sugestPackageType); // Insert package types into the set
        }
        query.finish();

        uniqueCompanyNamesList = uniqueCompanyNames.values();
        uniquePackageTypesList = uniquePackageTypes.values();
//        qDebug() << uniqueCompanyNamesList;
//        qDebug() << uniquePackageTypesList;

        // kiểm tra lỗi
        if (query.lastError().isValid()) {
            qDebug() << "Error executing query: " << query.lastError().text();
        }

        QObject::connect(ui->line_company, &QLineEdit::textChanged, this, &SavePackage::onCompanyNameChanged);
        QObject::connect(ui->line_type_package, &QLineEdit::textChanged, this, &SavePackage::onTypePackageChanged);
        db_customer.close();
    }
}

SavePackage::~SavePackage()
{
    delete ui;
}

void SavePackage::onCompanyNameChanged()
{
    companyCompleter->setModel(new QStringListModel(uniqueCompanyNamesList, companyCompleter));
    ui->line_company->setCompleter(companyCompleter);
}

void SavePackage::onTypePackageChanged()
{
    packageTypeCompleter->setModel(new QStringListModel(uniquePackageTypesList, packageTypeCompleter));
    ui->line_type_package->setCompleter(packageTypeCompleter);
}

void SavePackage::on_btn_save_clicked()
{
    QDate currentDate = QDate::currentDate();
    QString currentDateStr = currentDate.toString("dd/MM/yyyy");

    QString companyName = ui->line_company->text().toLower();
    companyName[0] = companyName[0].toUpper();
    QString packageType = ui->line_type_package->text().toLower();
    packageType[0] = packageType[0].toUpper();
    QString quantity = ui->line_quantity->text();
    QString note = ui->text_note->toPlainText();

    // Kiểm tra ký tự của mục số lượng có đúng number ko
    bool isInt;
    int intQuantity = quantity.toInt(&isInt);

    if (!isInt) {
        QMessageBox::warning(this, "Invalid Input", "Kiểm tra lại ký tự được nhập");
        // Xóa dòng này nếu kiểm tra thấy sai ký tự
        ui->line_quantity->clear();
    }

    QSqlDatabase::removeDatabase("add_package");
    // Liên kết với database
    // sử dụng khi deploy app
    //    QString databasePath = dataPath.getAppPath();
    //    database = QSqlDatabase::addDatabase("QSQLITE", "save_package");
    //    database.setDatabaseName(databasePath);
    dataBase = QSqlDatabase::addDatabase("QSQLITE", "save_package");
    dataBase.setDatabaseName("D:/project/test/databases/DosePackageManager.db");

    if (dataBase.open()) {
        QSqlQuery query(dataBase);

        if (query.exec("SELECT * FROM DoseCustomer")) {
            query.prepare("INSERT INTO DoseCustomer(Date, Company, PackageType, Quantity, DoseRequired, IrradiationTime, Note)"
                          "VALUES(:currentDateStr, :companyName, :packageType, :quantity, :numDose, :irradiationTime, :note)");
            query.bindValue(":currentDateStr", currentDateStr);
            query.bindValue(":companyName", companyName);
            query.bindValue(":packageType", packageType);
            query.bindValue(":quantity", quantity);
            query.bindValue(":numDose", numDose);
            query.bindValue(":irradiationTime", irradiationTime);
            query.bindValue(":note", note);
            query.exec();
            qDebug() << "Last Error: " << query.lastError().text();
            query.finish();
        }
        dataBase.close();
    } else {
        QMessageBox::warning(this, "File Not Open", "Không thể mở database file");
        return;
    }

    // Check if the database file exists
    if (!QFile::exists("D:/project/test/databases/DosePackageManager.db")) {
        qDebug() << "Database file does not exist.";
        return;
    }

    // Close the connection if it's already open
    if (db_customer.isOpen()) {
        db_customer.close();
    }
    qDebug() << "prepare to open database";

    // sử dụng khi deploy app
    //    QString databasePath = dataPath.getAppPath();
    //    database = QSqlDatabase::addDatabase("QSQLITE", "save_package");
    //    database.setDatabaseName(databasePath);
    // Open the database
    db_customer = QSqlDatabase::addDatabase("QSQLITE", "add_package");
    db_customer.setDatabaseName("D:/project/test/databases/DosePackageManager.db");


    // Check if the database is open
    if (!db_customer.open()) {
        qDebug() << "Failed to open db_customer connection: " << db_customer.lastError().text();
        return;
    }
    qDebug() << "open successfully the db_customer";

    QSqlQuery db_customer_query(db_customer); // Use the existing db_customer object
    QString queryStr = "SELECT * FROM CustomerPackage WHERE CustomerName = :customerName AND PackageType = :packageType";
    db_customer_query.prepare(queryStr);

    db_customer_query.bindValue(":customerName", companyName);
    db_customer_query.bindValue(":packageType", packageType);

    // Check if the query returned any rows
    if (db_customer_query.exec() && db_customer_query.next()) {
        // The query returned at least one row
        bool entryExists = false;
        while (db_customer_query.next()) {
            //db_customer trả về giá trị value(0,1,2) lần lượt là id, companyName và packageType
            QString existingCompanyName = db_customer_query.value(1).toString();
            QString existingPackageType = db_customer_query.value(2).toString();
            qDebug() << "ComName: " << existingCompanyName << companyName;
            qDebug() << "eixstPackageType: " << existingPackageType << packageType;
            if (existingCompanyName == companyName && existingPackageType == packageType) {
                entryExists = true;
                qDebug() << "Có tìm thấy dữ liệu giống trong database";
                break;
            }
        }

//        if (!entryExists) {
//            // The combination of companyName and packageType does not exist in the database
//            qDebug() << "Không tìm thấy dữ liệu trong database1";
//        }
    } else {
        // The query returned no rows
        qDebug() << "Không tìm thấy dữ liệu trong database";

    // nếu ko tìm thấy, nghĩa là package này mới
        int result = QMessageBox::question(this, "Confirmation", "Đây là bản ghi khách hàng mới. Bạn có muốn thêm nó vào cơ sở dữ liệu khách hàng không?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No) {
            qDebug() << "Người dùng không muốn thêm khách hàng mới vào danh sách";
            return;
        } else {
            if (db_customer.isOpen()) {
                if (db_customer_query.exec("SELECT * FROM CustomerPackage")) {
                    db_customer_query.prepare("INSERT INTO CustomerPackage(CustomerName, PackageType)"
                                              "VALUES(:companyName, :packageType)");

                    db_customer_query.bindValue(":companyName", companyName);
                    db_customer_query.bindValue(":packageType", packageType);

                    if (db_customer_query.exec()) {
                        qDebug() << "Data inserted successfully.";
                        QMessageBox::information(this, "About", "Đã thêm mới vào trong cơ sở dữ liệu");
                    } else {
                        qDebug() << "Error inserting data into database A: " << db_customer_query.lastError().text();
                    }
                    db_customer_query.finish();
                    // Close the database connection when done
                }
                db_customer.close();
            }
        }
    }

    // Kiểm tra database connection nào còn mở
//    QStringList connectionNames = QSqlDatabase::connectionNames();

//    foreach (const QString &connectionName, connectionNames) {
//        QSqlDatabase db = QSqlDatabase::database(connectionName);

//        if (db.isOpen()) {
//            qDebug() << "Database connection" << connectionName << "is open.";
//        } else {
//            qDebug() << "Database connection" << connectionName << "is closed.";
//        }
//    }

    this->close();
}

void SavePackage::on_btn_cancel_clicked()
{
    close();
}

void SavePackage::on_btn_create_new_clicked()
{
    // regis_cus = new RegistCustomer(this);
    // regis_cus->show();
}
