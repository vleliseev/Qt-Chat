#include "netservice.h"

NetService::NetService(QObject *parent) :
    QObject(parent),
    menu(new AuthMenu()),
    chat(new ChatWidget()),
    socket(new QTcpSocket(this)),
    ctimer(new QTimer(this)),
    dataManager(new DataHandler(this))
{

    menu->show();
    chat->setVisible(false);

    connect(menu, SIGNAL(signIn(QString, QString)),
            this, SLOT(onSignIn(QString, QString)));
    connect(socket, SIGNAL(connected()),
            this, SLOT(onSocketConnected()));
    connect(socket, SIGNAL(disconnected()),
            this, SLOT(onSocketDisconnected()));
    connect(socket, SIGNAL(readyRead()),
            dataManager, SLOT(on_Socket_Ready_Read()));
    connect(ctimer, SIGNAL(timeout()),
            this, SLOT(onConnectionTimeOut()));
    connect(dataManager, SIGNAL(authAnswer(AuthAnswer&)),
            this, SLOT(onAuthAnswer(AuthAnswer&)));


}

NetService::~NetService()
{

}

void NetService::onSignIn(const QString &username, const QString &password)
{
    identifier.setLogin(username);
    identifier.setPassword(password);
    socket->connectToHost(QHostAddress::LocalHost, 8001);
    ctimer->start(10000); // 10 seconds for connection try
}

void NetService::onSocketConnected()
{
    ctimer->stop();
    qDebug() << "connected";
    DataHandler::write(socket, identifier);
}

void NetService::onSocketDisconnected()
{
    socket->abort();
    //menu->setStatus("Connection lost.");
}

void NetService::onConnectionTimeOut()
{
    socket->abort();
    menu->setStatus("Connection timeout.");
}


void NetService::onAuthAnswer(AuthAnswer &ans)
{
    if (!ans.isSigned())
    {
        menu->setStatus("Authentication error.");
        socket->abort();
    }
    menu->close();
    chat->show();
}
