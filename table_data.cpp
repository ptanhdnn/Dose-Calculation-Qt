#include "table_data.h"
#include "ui_table_data.h"
#include <QVBoxLayout>

table_data::table_data(QWidget *parent, const QString& irradiationTime) :
    QWidget(parent),
    ui(new Ui::table_data)
{
    ui->setupUi(this);

    database = QSqlDatabase::addDatabase("QSQLITE", "save_package");
    database.setDatabaseName("D:/project/DoseCalculation/databases/DosePackageManager.db");

    if(!database.open()){
        qDebug() << "Failed to open database: " << database.lastError().text();
        return;
    }

    // Create QSqlTableModel
    QSqlQuery query(database);
    query.prepare("SELECT * FROM DoseCustomer ORDER BY id DESC LIMIT 20");

    // Execute the query and get the results
    if (!query.exec()) {
        qDebug() << "Failed to execute query: " << query.lastError().text();
        return;
    }

    // Create QTableView
    QTableView *tableView = new QTableView(this);
    model = new QSqlQueryModel(this); // Initialize the model

    // Set the model to the table view
    tableView->setModel(model);
    tableView->resize(600, 900); // Adjust the size as needed

    // Show the QTableView
    QVBoxLayout *layout = new QVBoxLayout(this); // Create a layout for the widget
    layout->addWidget(tableView); // Add the table view to the layout
    setLayout(layout); // Set the layout for the widget

    model->setQuery(query);
    database.close();
}

table_data::~table_data()
{
    delete ui;
    delete model; // Don't forget to delete the model
}
