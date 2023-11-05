#include "customer_table.h"
#include "ui_customer_table.h"

#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTableView>

Customer_table::Customer_table(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Customer_table)
{
    ui->setupUi(this);
    this->setWindowTitle("Danh sách khách hàng");

    // Make the window resizable
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    database = QSqlDatabase::addDatabase("QSQLITE", "save_package");
    QString dbPath = getenv("DATABASE_PATH");
    database.setDatabaseName(dbPath + "/DosePackageManager.db");

    if (!database.open()) {
        qDebug() << "Failed to open database: " << database.lastError().text();
        return;
    }

    // Create a query model
    model = new QSqlQueryModel(this);

    // Set the query for the model
    QSqlQuery query(database);
    query.prepare("SELECT * FROM CustomerPackage ORDER BY id DESC LIMIT 20");

    if (!query.exec()) {
        qDebug() << "Failed to execute query: " << query.lastError().text();
        return;
    }

    // Populate the model with the query result
    model->setQuery(std::move(query));

    // Create a table view and set the model
    QTableView *tableView = new QTableView(this);
    tableView->setModel(model);

    // Resize the columns to fit the contents
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Create a close button
    QPushButton *closeButton = new QPushButton("Close", this);
    connect(closeButton, &QPushButton::clicked, this, &Customer_table::onCloseButtonClicked);

    closeButton->setStyleSheet("QPushButton {"
                               "  background-color: #FF5733;" // Background color
                               "  color: white;"              // Text color
                               "  border: 2px solid #D32F2F;" // Border style
                               "  border-radius: 5px;"        // Border radius
                               "  padding: 5px 10px;"          // Padding
                               "}"

                               // Mouse hover effect
                               "QPushButton:hover {"
                               "  background-color: #D32F2F;"
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

Customer_table::~Customer_table()
{
    delete ui;
    delete model;
}

void Customer_table::onCloseButtonClicked()
{
    close();
}
