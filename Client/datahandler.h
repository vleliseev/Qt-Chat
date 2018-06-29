#ifndef DATAHANDLER_H
#define DATAHANDLER_H



#include <QTcpSocket>

#include "../Data/authdata.h"
#include "../Data/authanswer.h"
#include "../Data/userlist.h"


class DataHandler : public QObject
{
    Q_OBJECT
public:

    explicit DataHandler(QObject *parent = nullptr);
    static void write(QTcpSocket *socket, BaseData &data);
signals:

    void authRequestRead(QTcpSocket*, AuthData&);
    void authAnswerRead(AuthAnswer&);
    void userListRead(UserList &lst);
    void newConnection(QString &username);

private slots:
    void on_Socket_Ready_Read();

};

#endif // DATAHANDLER_H
