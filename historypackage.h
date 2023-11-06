#ifndef HISTORYPACKAGE_H
#define HISTORYPACKAGE_H

#include <QDialog>

namespace Ui {
class HistoryPackage;
}

class HistoryPackage : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryPackage(QWidget *parent = nullptr);
    ~HistoryPackage();

private:
    Ui::HistoryPackage *ui;
};

#endif // HISTORYPACKAGE_H
