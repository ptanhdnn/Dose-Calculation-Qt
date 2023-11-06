#include "historypackage.h"
#include "ui_historypackage.h"

HistoryPackage::HistoryPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryPackage)
{
    ui->setupUi(this);


}

HistoryPackage::~HistoryPackage()
{
    delete ui;
}
