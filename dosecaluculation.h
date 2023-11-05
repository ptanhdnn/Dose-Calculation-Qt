/*
 * Cửa sổ chính của chương trình
 *
 * Tính toán liều chiếu dựa trên sự lựa chọn các bản nguồn,
 * sau đó có thể lưu nếu có nhu cầu.
 * Ngoài ra, các trên các thanh menu có thể theo dõi lại lịch
 * sử chiếu xạ, danh sách khách hàng và thông tin về nguồn.
 *
*/

#ifndef DOSECALUCULATION_H
#define DOSECALUCULATION_H

#include <QMainWindow>

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QDate>
#include <QCheckBox>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QDir>

#include "savepackage.h"
#include "table_data.h"
#include "customer_table.h"
#include "datamanager.h"
#include "databaseconfig.h"


QT_BEGIN_NAMESPACE
namespace Ui { class DoseCaluculation; }
QT_END_NAMESPACE

class DoseCaluculation : public QMainWindow
{
    Q_OBJECT

public:
    DoseCaluculation(QWidget *parent = nullptr);
    ~DoseCaluculation();

    double TgianBanRa;
    double ActivityR1, TrueActy1;
    double ActivityR2, TrueActy2;
    double ActivityR3, TrueActy3;
    QString irradiationTime;
    float num_dose;

    QString getIrradiationTime() const;
    float getNumDose() const;

protected:
    void timerEvent();

private slots:
    void on_R1_stateChanged(int arg1);

    void on_R2_stateChanged(int arg2);

    void on_R3_stateChanged(int arg3);

    void on_actioninfo_triggered();

    void on_time_calculated();

    void on_btn_save_clicked();

    void on_action_hisCustom_triggered();

    void on_action_histoDose_triggered();

private:
    Ui::DoseCaluculation *ui;

    QTimer *timer;
    QCheckBox *checkR1;
    QCheckBox *checkR2;
    QCheckBox *checkR3;

    SavePackage *save;
    table_data *tbl_data;
    Customer_table *tbl_customer;
    dataManager *db_manager;
//    DatabaseConfig databaseConfig;
    QString setDataPathByUser();

};
#endif // DOSECALUCULATION_H
