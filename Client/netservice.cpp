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

    connect(dataManager, SIGNAL(authAnswerRead(AuthAnswer&)),
            this, SLOT(onAuthAnswerRead(AuthAnswer&)));

    connect(dataManager, SIGNAL(userListRead(UserList&)),
            this, SLOT(onUserListRead(UserList&)));


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
    DataHandler::write(socket, identifier);
}

void NetService::onSocketDisconnected()
{
    socket->abort();
}

void NetService::onConnectionTimeOut()
{
    socket->abort();
    menu->setStatus("Connection timeout.");
}


void NetService::onAuthAnswerRead(AuthAnswer &ans)
{
    if (!ans.isSigned())
    {
        menu->setStatus("Authentication error.");
        socket->abort();
        return;
    }

    menu->close();
    chat->show();
}

void NetService::onUserListRead(UserList &lst)
{
    chat->setUserList(lst);
}
