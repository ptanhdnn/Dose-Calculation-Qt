#include "importpackage.h"
#include "ui_importpackage.h"

ImportPackage::ImportPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportPackage)
{
    ui->setupUi(this);
}

ImportPackage::~ImportPackage()
{
    delete ui;
}
