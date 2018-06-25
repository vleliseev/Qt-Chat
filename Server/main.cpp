#include "mainform.h"
#include <QApplication>

#include "Data/authdata.h"

void foo(QDataStream &st, BaseData &d)
{
    st >> d;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainForm w;
    w.show();

    return a.exec();
}
