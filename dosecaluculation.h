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

#include "savepackage.h"
#include "table_data.h"


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


};
#endif // DOSECALUCULATION_H
