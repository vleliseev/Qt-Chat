#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QTcpServer>
#include <QTcpSocket>

#include <QMap>
#include <QString>

#include "../Data/authanswer.h"
#include "../Data/userlist.h"
#include "../Data/userdata.h"
#include "../Data/message.h"

class ConnectionHandler : public QObject
{
    Q_OBJECT
public:

    explicit ConnectionHandler(QObject *parent = nullptr);
    void startServer();
    void stopServer();
    bool isListening() const;
    void write(QTcpSocket *socket, const BaseData &from);

    ~ConnectionHandler();

private slots:

    void on_New_Connection();
    void on_Client_Disconnection();
    void on_Socket_Error(QAbstractSocket::SocketError);
    void on_Socket_Ready_Read();

private:

    void readAuthRequest(QTcpSocket *socket);
    void readMessage(QTcpSocket *socket);
    void writeAuthAnswer(QTcpSocket *socket, bool answer);
    void writeUserList(QTcpSocket *socket, const QList<UserData> &lst);
    void sendOutMessage(QTcpSocket *sender, const Message &msg);
    void writeAboutNewConnection(const UserData &connectedUser);
    void writeAboutUserDisconnection(const UserData &disconnectedUser);

    QString getIPv4AddrString(QTcpSocket *socket);
    void connectSocketSignals(QTcpSocket *socket);

private:

    QMap<UserData, QTcpSocket*> clients;
    QTcpServer *serv;
};

#endif // CONNECTIONHANDLER_H
