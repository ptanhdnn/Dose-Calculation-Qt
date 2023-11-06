#ifndef IMPORTPACKAGE_H
#define IMPORTPACKAGE_H

#include <QDialog>

namespace Ui {
class ImportPackage;
}

class ImportPackage : public QDialog
{
    Q_OBJECT

public:
    explicit ImportPackage(QWidget *parent = nullptr);
    ~ImportPackage();

private:
    Ui::ImportPackage *ui;
};

#endif // IMPORTPACKAGE_H
