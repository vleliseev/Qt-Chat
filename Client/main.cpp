#include "netservice.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //time to talk starting !!!
    auto t2t = new NetService();

    return a.exec();
}
