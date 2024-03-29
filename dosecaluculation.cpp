#include "dosecaluculation.h"
#include "./ui_dosecaluculation.h"

#include "QDateTime"
#include "QIcon"
#include "QFileDialog"
#include "QDir"

DoseCaluculation::DoseCaluculation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DoseCaluculation)
{
    DatabaseConfig databaseConfig;
    QString dataPath = databaseConfig.databaseFolderPath();

    if (!dataPath.isEmpty()) {
        qDebug() << "Database folder path: " << dataPath;
    } else {
        qDebug() << "Database folder path is not set.";
        QMessageBox::information(
            nullptr,
            "Database Information",
            "Không tìm thấy cơ sở dữ liệu \n chương trình sẽ khởi tạo dữ liệu tại đường dẫn này!"
            );
        dataPath = setDataPathByUser();

        QMessageBox::information(
            nullptr,
            "Database Information",
            "Đã tạo xong cơ sở dữ liệu!"
            );
    }

    qDebug() << "Check database was existed";
    db_manager = new dataManager();
    qDebug() << "Initialize db_ptr";
    QString databasePath = "/databases/DosePackageManager.db";
    QDir directory(databasePath);
    if(!directory.exists()){
        qDebug() << "database file was not exist";
        db_manager->createDatabase();
        qDebug() << "am not sure";
    };
    qDebug() << "Checked!!!";

    ui->setupUi(this);

    // Khởi tạo các checkR
    //    checkR1 = new QCheckBox("R1", this);
    //    checkR2 = new QCheckBox("R2", this);
    //    checkR3 = new QCheckBox("R3", this);

    QIcon icon(":/resources/images/vinaIcon.ico");
    setWindowIcon(icon);


    QPixmap pic(":/resources/images/vinagamma.jpg");
    int w = ui->lbl_picture->width();
    int h = ui->lbl_picture->height();
    ui->lbl_picture->setPixmap(pic.scaled(w, h, Qt::KeepAspectRatio));

    QTimer* timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &DoseCaluculation::timerEvent);
    timer->start(1000);

    // Tính hoạt độ của các bản nguồn
    TgianBanRa = QDate(2021, 1, 6).daysTo(QDate::currentDate())/365.0;
    ActivityR1 = 64.9 * exp(-TgianBanRa * 0.693147181 / 5.27);
    ActivityR2 = 272.56 * exp(-TgianBanRa * 0.693147181 / 5.27);
    ActivityR3 = 112.78 * exp(-TgianBanRa * 0.693147181 / 5.27);

    ui->lbl_R1->setText("<font color='black'>" + QString::number(ActivityR1, 'f', 2) + "</font>" + " kCi");
    ui->lbl_R2->setText("<font color='black'>" + QString::number(ActivityR2, 'f', 2) + "</font>" + " kCi");
    ui->lbl_R3->setText("<font color='black'>" + QString::number(ActivityR3, 'f', 2) + "</font>" + " kCi");

    QObject::connect(ui->R1, &QCheckBox::stateChanged, this, &DoseCaluculation::on_R1_stateChanged);
    QObject::connect(ui->R2, &QCheckBox::stateChanged, this, &DoseCaluculation::on_R2_stateChanged);
    QObject::connect(ui->R3, &QCheckBox::stateChanged, this, &DoseCaluculation::on_R3_stateChanged);

    QObject::connect(ui->mass, &QLineEdit::textChanged, this, &DoseCaluculation::on_time_calculated);
    QObject::connect(ui->dose, &QLineEdit::textChanged, this, &DoseCaluculation::on_time_calculated);
}

DoseCaluculation::~DoseCaluculation()
{
    delete ui;
}

QString DoseCaluculation::setDataPathByUser()
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setOption(QFileDialog::ShowDirsOnly, true);

    // Get the database folder path from the user.
    QString databaseFolderPath = fileDialog.getExistingDirectory();

    // Convert the relative path to the database folder to an absolute path.
    QString absolutePath = QDir::cleanPath(QDir::currentPath() + "/" + databaseFolderPath);
    return absolutePath;
}

void DoseCaluculation::on_time_calculated()
{
    float num_mass = ui->mass->text().toFloat();
    num_dose   = ui->dose->text().toFloat();

    // Kiểm tra chọn hoạt độ nguồn chưa
    if (!ui->R1->isChecked() && !ui->R2->isChecked() && !ui->R3->isChecked()) {
        QMessageBox::information(this, "No Selection", "Chọn hoạt độ nguồn R trước");
        return;
    }

    double totalActivity = 0.85 * (TrueActy1 + TrueActy2 + TrueActy3);

    float weight = num_mass/280 ;
    double doseMean = 0.4026 * weight * weight - 0.8449 * weight + 0.6405;

    double time = 60 * (num_dose / (doseMean * totalActivity / 100));   // Đơn vị tính theo phút
    double timeMinute = static_cast<int>((time - 60 * (static_cast<int>(time) / 60)) / 5) * 5;
    irradiationTime = QString::number(static_cast<int>(time) / 60) + " giờ " + QString::number(timeMinute) + " phút";

    ui->text_result->setText(irradiationTime);

    double doseCalculated = doseMean * (timeMinute + 60 * (static_cast<int>(time) / 60)) * totalActivity / (60 * 100);
    ui->lbl_dose_recalculated->setText("<font color='red'><b>" + QString::number(doseCalculated, 'f', 2) + " kGy" + "</font>");
}

void DoseCaluculation::on_R1_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        // R1 checkbox is checked
        ui->lbl_R1->setText("<font color='red'><b>" + QString::number(ActivityR1, 'f', 2) + " kCi" + "</font>");
        TrueActy1 = ActivityR1;
    } else {
        // R1 checkbox is unchecked
        ui->lbl_R1->setText("<font color='black'>" + QString::number(ActivityR1, 'f', 2) + " kCi" + "</font>");
        TrueActy1 = 0.0;
    }
}

void DoseCaluculation::on_R2_stateChanged(int arg2)
{
    if (arg2 == Qt::Checked) {
        // R2 checkbox is checked
        ui->lbl_R2->setText("<font color='red'><b>" + QString::number(ActivityR2, 'f', 2) + " kCi" + "</font>");
        TrueActy2 = ActivityR2;
    } else {
        // R2 checkbox is unchecked
        ui->lbl_R2->setText("<font color='black'>" + QString::number(ActivityR2, 'f', 2) + " kCi" + "</font>");
        TrueActy2 = 0.0;
    }
}

void DoseCaluculation::on_R3_stateChanged(int arg3)
{
    if (arg3 == Qt::Checked) {
        // R3 checkbox is checked
        ui->lbl_R3->setText("<font color='red'><b>" + QString::number(ActivityR3, 'f', 2) + " kCi" + "</font>");
        TrueActy3 = ActivityR3;
    } else {
        // R3 checkbox is unchecked
        ui->lbl_R3->setText("<font color='black'>" + QString::number(ActivityR3, 'f', 2) + " kCi" + "</font>");
        TrueActy3 = 0.0;
    }
}

void DoseCaluculation::on_actioninfo_triggered()
{
    QMessageBox::information(this, "About", "Chưong trình chỉ sử dụng cho máy SVST-Co60B\n"
                                            "Áp dụng cho nguồn nạp ngày 26/12/2020 (-10%)\n"
                                            "\nLuu y: Vị trí đặt liều kế không phải Dmin\n"
                                            "Thùng hàng có kích thước 48 x 65 x 90 cm\n"
                                            "\nPhòng vận hành máy Cobalt 2023");
}

void DoseCaluculation::timerEvent()
{
    ui->lbl_currentTime->setText(QDateTime::currentDateTime().toString("dddd, MMMM d hh:mm:ss"));
}

void DoseCaluculation::on_btn_save_clicked()
{
    save = new SavePackage(this, irradiationTime, num_dose);
    save->show();
//    QString name = "Đây là tiếng việt";
//    qDebug() << name;
}

QString DoseCaluculation::getIrradiationTime() const
{
    return irradiationTime;
}

float DoseCaluculation::getNumDose() const
{
    return num_dose;
}

void DoseCaluculation::on_action_hisCustom_triggered()
{
    tbl_customer = new Customer_table(this);
    tbl_customer->show();
}


void DoseCaluculation::on_action_histoDose_triggered()
{
    tbl_data = new table_data(this);
    tbl_data->show();
}

