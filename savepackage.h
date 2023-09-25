#ifndef SAVEPACKAGE_H
#define SAVEPACKAGE_H

#include <QDialog>

#include <QCompleter>
#include <QSet>
#include "databaseheader.h"

namespace Ui {
class SavePackage;
}

class SavePackage : public QDialog
{
    Q_OBJECT

public:
    explicit SavePackage(QWidget *parent = nullptr, const QString& irradiationTime = "", float numDose = 0.0);
    ~SavePackage();

    QString getIrradiationTime() const;
    float getNumDose() const;
    QStringList sugestCompanyNames, sugestPackageTypes, uniqueCompanyNamesList, uniquePackageTypesList;


private slots:
    void on_btn_save_clicked();

    void on_btn_cancel_clicked();

    void on_btn_create_new_clicked();
    void onCompanyNameChanged();
    void onTypePackageChanged();

private:
    Ui::SavePackage *ui;

    QString irradiationTime;
    float numDose;

    QCompleter *companyCompleter;
    QCompleter *packageTypeCompleter;

    void updateNewPackage(QString companyName, QString packageType);

    QSqlDatabase db_customer;
    QSqlDatabase dataBase;

};

#endif // SAVEPACKAGE_H
