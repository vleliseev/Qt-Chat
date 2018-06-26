#ifndef DATAHANDLER_H
#define DATAHANDLER_H



#include <QTcpSocket>

#include "../Data/authdata.h"
#include "../Data/authanswer.h"


class DataHandler : public QObject
{
    Q_OBJECT
public:

    explicit DataHandler(QObject *parent = nullptr);

    /* writing data to socket */
    static void write(QTcpSocket *socket, BaseData &data);

signals:
    void authRequest(QTcpSocket*, AuthData&);
    void authAnswer(AuthAnswer&);

private slots:

    /* reading data from socket */
    void on_Socket_Ready_Read();

};

#endif // DATAHANDLER_H
