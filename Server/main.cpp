#include <iostream>
#include <QCoreApplication>
#include "connectionhandler.h"


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    ConnectionHandler netmanager; // main network class
    std::cout << "This is Qt-Chat server console.\n"
                 "Server started at localhost.\n";
    netmanager.startServer();

    return app.exec();
    //MainForm w;
    //w.show();
}
