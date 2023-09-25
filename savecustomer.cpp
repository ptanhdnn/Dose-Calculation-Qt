#include "savecustomer.h"
#include "ui_savecustomer.h"

SaveCustomer::SaveCustomer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaveCustomer)
{
    ui->setupUi(this);
}

SaveCustomer::~SaveCustomer()
{
    delete ui;
}
