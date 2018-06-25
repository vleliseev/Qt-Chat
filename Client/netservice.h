#ifndef NETSERVICE_H
#define NETSERVICE_H

#include "authmenu.h"
#include "chatwidget.h"
#include "datahandler.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>

class NetService : QObject
{
    Q_OBJECT
public:

    explicit NetService(QObject *parent = nullptr);
    virtual ~NetService();

private slots:

    void onSignIn(const QString &username, const QString &password);
    void onSocketConnected();
    void onSocketDisconnected();
    void onConnectionTimeOut();

    /* handling authentication answer from server */
    void onAuthAnswer(AuthAnswer &ans);

private:
    AuthMenu *menu;
    ChatWidget *chat;
    QTcpSocket *socket;
    QTimer *ctimer; // connection timer
    DataHandler *dataManager;
    AuthData identifier;
};

#endif // NETSERVICE_H
