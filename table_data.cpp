#include "table_data.h"
#include "ui_table_data.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTableView>

table_data::table_data(QWidget *parent, const QString& irradiationTime) :
    QDialog(parent),
    ui(new Ui::table_data)
{
    ui->setupUi(this);
    this->setWindowTitle("Lịch sử chiếu xạ");

    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
//  // sử dụng khi deploy app
//    QString databasePath = dataPath.getAppPath();
//    database = QSqlDatabase::addDatabase("QSQLITE", "save_package");
//    database.setDatabaseName(databasePath);

    database = QSqlDatabase::addDatabase("QSQLITE", "save_package");
    database.setDatabaseName("D:/project/test/databases/DosePackageManager.db");

    if (!database.open()) {
        qDebug() << "Failed to open database: " << database.lastError().text();
        return;
    }
    model = new QSqlQueryModel(this);

    // Set the query for the model
    QSqlQuery query(database);
    query.prepare("SELECT * FROM DoseCustomer ORDER BY id DESC LIMIT 20");

    if (!query.exec()) {
        qDebug() << "Failed to execute query: " << query.lastError().text();
        return;
    }

    model->setQuery(std::move(query));

    // Create a table view and set the model
    QTableView *tableView = new QTableView(this);
    tableView->setModel(model);

    // Resize the columns to fit the contents
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Create a close button
    QPushButton *closeButton = new QPushButton("Close", this);
    connect(closeButton, &QPushButton::clicked, this, &table_data::onCloseButtonClicked);

    closeButton->setStyleSheet("QPushButton {"
                               "  background-color: #FF5733;" // Background color
                               "  color: white;"              // Text color
                               "  border: 2px solid #D32F2F;" // Border style
                               "  border-radius: 5px;"        // Border radius
                               "  padding: 5px 10px;"          // Padding
//                               "}"

                               // Mouse hover effect
//                               "QPushButton:hover {"
//                               "  background-color: #D32F2F;"
                               "}");

    // Create a layout for the table view and button
    QVBoxLayout *tableLayout = new QVBoxLayout;
    tableLayout->addWidget(tableView);

    // Create a layout for the button
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch(); // Add stretch to push the button to the bottom

    // Create a horizontal layout to hold both the table and button layouts
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(tableLayout);
    mainLayout->addLayout(buttonLayout);

    // Set the layout for the widget
    setLayout(mainLayout);

    // Close the database when done
    database.close();
}

table_data::~table_data()
{
    delete ui;
    delete model;
}

void table_data::onCloseButtonClicked()
{
    close();
}
