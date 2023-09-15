#include "dosecaluculation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DoseCaluculation w;
    w.show();
    return a.exec();
}
