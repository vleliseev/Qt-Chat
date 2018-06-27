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
    connectSocketSignals(client);
    qDebug() << "New connection try from" << getIPv4AddrString(client) << "...";
}

void ConnectionHandler::connectSocketSignals(QTcpSocket *socket)
{
    connect(socket, SIGNAL(readyRead()),
            dataManager, SLOT(on_Socket_Ready_Read()));
    connect(socket, SIGNAL(disconnected()),
            this, SLOT(on_Client_Disconnection()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
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
    auto socket = static_cast<QTcpSocket *>(sender());
    qDebug() << getIPv4AddrString(socket) << socket->errorString();
}

void ConnectionHandler::on_Auth_Request(QTcpSocket *socket, AuthData &d)
{
    if (d.getPassword() == "")
    {
        AuthAnswer ans(true);
        DataHandler::write(socket, ans);
        //clients.insert(d.getLogin(), socket);
        qDebug() << getIPv4AddrString(socket) << "authentication successful. Accepted.";
    }
    else
    {
        AuthAnswer ans(false);
        DataHandler::write(socket, ans);
        qDebug() << getIPv4AddrString(socket) << "authentication usuccessful. Aborted.";
        socket->abort();
    }
}


QString ConnectionHandler::getIPv4AddrString(QTcpSocket *socket)
{
    QString IPv4IPv6 = socket->peerAddress().toString();
    QString IPv4 = IPv4IPv6.right(IPv4IPv6.size() - 7);
    return IPv4;
}



