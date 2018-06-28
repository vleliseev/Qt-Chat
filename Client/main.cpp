#include "netservice.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto core = new NetService;

    return a.exec();
}
