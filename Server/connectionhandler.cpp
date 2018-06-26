#include "connectionhandler.h"

ConnectionHandler::ConnectionHandler(QObject *parent) :
    QObject(parent),
    serv(new QTcpServer(this)),
    dataManager(new DataHandler(this))
{
    connect(serv, SIGNAL(newConnection()),
            this, SLOT(on_New_Connection()));
    connect(dataManager, SIGNAL(authRequest(QTcpSocket*,AuthData&)),
           this, SLOT(on_Auth_Request(QTcpSocket*,AuthData&)));

}

void ConnectionHandler::startServer()
{
    serv->listen(QHostAddress::Any, 8001);
}

void ConnectionHandler::stopServer()
{
    serv->close();
    clients.clear();
}


void ConnectionHandler::on_New_Connection()
{
    auto client = serv->nextPendingConnection();
    qDebug() << "New connection try from" << client->peerAddress().toString() << "...";
    connect(client, SIGNAL(readyRead()),
            dataManager, SLOT(on_Socket_Ready_Read()));
    connect(client, SIGNAL(disconnected()),
            this, SLOT(on_Client_Disconnection()));
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(on_Socket_Error(QAbstractSocket::SocketError)));
}

void ConnectionHandler::on_Client_Disconnection()
{

}

bool ConnectionHandler::isListening() const
{
    return serv->isListening();
}

ConnectionHandler::~ConnectionHandler()
{
    delete serv;
}

/* todo... */
void ConnectionHandler::on_Socket_Error(QAbstractSocket::SocketError)
{

}

void ConnectionHandler::on_Auth_Request(QTcpSocket *socket, AuthData &d)
{
    if (d.getPassword() == "")
    {
        AuthAnswer ans(true);
        DataHandler::write(socket, ans);
        qDebug() << socket->peerAddress().toString() << "authentication success. Accepted.";
    }
    else
        qDebug() << socket->peerAddress().toString() << "authentication usuccessful. Aborted.";
}



