#ifndef NETSERVICE_H
#define NETSERVICE_H

#include "authmenu.h"
#include "chatwidget.h"

#include "../Data/authanswer.h"
#include "../Data/userdata.h"
#include "../Data/userlist.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>

class NetService : QObject
{
    Q_OBJECT
public:

    explicit NetService(QObject *parent = nullptr);
    virtual ~NetService();

    void write(QTcpSocket *socket, const BaseData &data);

private slots:

    // Slot handles clicking "Sing in" button in auth menu
    void onSignIn(const QString &username, const QString &password);

    void onSocketConnected();
    void onSocketDisconnected();
    void onConnectionTimeOut();
    void onSocketReadyRead();
    void onMessageSent(Message &msg);

private:

    void connectSocketSignals();

    // Incoming data handling methods
    void readUserList(QDataStream &readStream);
    void readAuthAnswer(QDataStream &readStream);
    void readNewConnection(QDataStream &readStream);
    void readDisconnection(QDataStream &readStream);
    void readMessage(QDataStream &readStream);

private:

    AuthMenu *menu;
    ChatWidget *chat;
    QTcpSocket *socket;
    QTimer *ctimer; // connection timer
    UserData identifier;

};

#endif // NETSERVICE_H
