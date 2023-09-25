#ifndef SAVECUSTOMER_H
#define SAVECUSTOMER_H

#include <QWidget>

namespace Ui {
class SaveCustomer;
}

class SaveCustomer : public QWidget
{
    Q_OBJECT

public:
    explicit SaveCustomer(QWidget *parent = nullptr);
    ~SaveCustomer();

private:
    Ui::SaveCustomer *ui;
};

#endif // SAVECUSTOMER_H
