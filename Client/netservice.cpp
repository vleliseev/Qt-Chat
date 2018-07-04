#include "netservice.h"

NetService::NetService(QObject *parent) :
    QObject(parent),
    menu(new AuthMenu()),
    chat(new ChatWidget()),
    socket(new QTcpSocket(this)),
    ctimer(new QTimer(this))
{

    menu->show();
    chat->setVisible(false);
    //chat->show();
    //chat->addParticipant("asdad");

    connect(menu, SIGNAL(signIn(QString, QString)),
            this, SLOT(onSignIn(QString, QString)));
    connect(ctimer, SIGNAL(timeout()), this, SLOT(onConnectionTimeOut()));

    connectSocketSignals();

}

void NetService::connectSocketSignals()
{
    connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
}

NetService::~NetService()
{
    delete menu;
    delete chat;
}

void NetService::onSignIn(const QString &username, const QString &password)
{
    identifier.setUsername(username);
    identifier.setPassword(password);
    socket->connectToHost(QHostAddress::LocalHost, 8001);
    ctimer->start(10000); // 10 seconds for connection try
}

void NetService::onSocketConnected()
{
    ctimer->stop();
    write(socket, identifier, DataType::AuthRequest);
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


void NetService::readAuthAnswer(QDataStream &readStream)
{
    AuthAnswer ans;
    readStream >> ans;

    if (!ans.isSigned())
    {
        menu->setStatus("Authentication error.");
        socket->abort();
        return;
    }

    menu->close();
    chat->show();
}

void NetService::readUserList(QDataStream &readStream)
{
    UserList lst;
    readStream >> lst;
    chat->addParticipants(lst);
}

void NetService::readNewConnection(QDataStream &readStream)
{
    UserData user;
    readStream >> user;
    chat->addParticipant(user);
}

void NetService::readDisconnection(QDataStream &readStream)
{
    UserData user;
    readStream >> user;
    chat->removeParticipant(user.getUsername());
}

void NetService::write(QTcpSocket *socket, const BaseData &data)
{
    QByteArray datagram;
    QDataStream writeStream(&datagram, QIODevice::WriteOnly);
    qint16 size = sizeof(qint8) + data.size();
    writeStream << size << (qint8)data.type();
    writeStream << data;
    socket->write(datagram);
    socket->waitForBytesWritten();
}

void NetService::write(QTcpSocket *socket, const UserData &data, DataType type)
{
    QByteArray datagram;
    QDataStream writeStream(&datagram, QIODevice::WriteOnly);
    qint16 size = sizeof(qint8) + data.size();
    writeStream << size << (qint8)type;
    writeStream << data;
    socket->write(datagram);
    socket->waitForBytesWritten();
}

void NetService::onSocketReadyRead()
{
    auto socket = static_cast<QTcpSocket *>(sender());
    QDataStream readStream(socket);
    qint16 sizeRead;
    qint8 type;

    readStream >> sizeRead;
    if (socket->bytesAvailable() < sizeRead) return;
    readStream >> type;

    if (type == DataType::AuthResponse)
        readAuthAnswer(readStream);
    if (type == DataType::UserListResponse)
        readUserList(readStream);
    if (type == DataType::NewConnection)
        readNewConnection(readStream);
    if (type == DataType::Disconnection)
        readDisconnection(readStream);
}
