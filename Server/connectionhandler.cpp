#include "connectionhandler.h"

ConnectionHandler::ConnectionHandler(QObject *parent) :
    QObject(parent),
    serv(new QTcpServer(this)),
    dataManager(new DataHandler(this))
{
    connect(serv, SIGNAL(newConnection()),
            this, SLOT(on_New_Connection()));
    connect(dataManager, SIGNAL(authRequestRead(QTcpSocket*,AuthData&)),
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
    auto disconnectedSocket = static_cast<QTcpSocket *>(sender());
    auto username = clients.key(disconnectedSocket);
    clients.remove(username);
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
    AuthAnswer ans;
    if (d.getPassword() == "")
    {
        /* writing answer to connected client */
        ans.setSigned(true);
        clients.insert(d.getLogin(), socket);
        DataHandler::write(socket, ans);

        /* writing list of authenticated online users */
        UserList participants(clients.keys());
        DataHandler::write(socket, participants);

        qDebug() << getIPv4AddrString(socket) << "authentication successful. Accepted.";
    }

    else
    {
        ans.setSigned(false);
        qDebug() << getIPv4AddrString(socket) << "authentication usuccessful. Aborted.";
        DataHandler::write(socket, ans);
    }
}


QString ConnectionHandler::getIPv4AddrString(QTcpSocket *socket)
{
    QString IPv4IPv6 = socket->peerAddress().toString();
    QString IPv4 = IPv4IPv6.right(IPv4IPv6.size() - 7);
    return IPv4;
}



