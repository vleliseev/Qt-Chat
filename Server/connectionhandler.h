#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QTcpServer>
#include <QTcpSocket>

#include <QMap>
#include <QString>

#include "datahandler.h"

class ConnectionHandler : public QObject
{
    Q_OBJECT
public:

    explicit ConnectionHandler(QObject *parent = nullptr);
    void startServer();
    void stopServer();
    bool isListening() const;

    ~ConnectionHandler();

signals:

    void userConnected(QString);
    void userDisconnected(QString);

private slots:

    void on_New_Connection();
    void on_Client_Disconnection();
    void on_Socket_Error(QAbstractSocket::SocketError);

    /* this slot works when dataManager reads */
    /* authentication request data from socket */
    void on_Auth_Request(QTcpSocket* socket, AuthData &d);
private:

    QMap<AuthData, QTcpSocket*> clients;
    QTcpServer *serv;
    DataHandler *dataManager;
};

#endif // CONNECTIONHANDLER_H
