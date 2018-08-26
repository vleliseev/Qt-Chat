#include <iostream>
#include <QCoreApplication>
#include "connectionhandler.h"


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    ConnectionHandler netmanager;
    std::cout << "This is Qt-Chat server console.\n"
                 "Server started at localhost.\n";
    netmanager.startServer();

    return app.exec();
}
