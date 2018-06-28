#include "datahandler.h"


DataHandler::DataHandler(QObject *parent) : QObject(parent)
{

}
void DataHandler::write(QTcpSocket *socket, BaseData &from)
{
    QByteArray datagram;
    QDataStream writeStream(&datagram, QIODevice::WriteOnly);
    qint16 size = sizeof(qint8) + from.size(); // sizeof(qint8) is size of DataType
    writeStream << size << (qint8)from.type();
    writeStream << from;
    socket->write(datagram);
    socket->waitForBytesWritten();
}

void DataHandler::on_Socket_Ready_Read()
{
    auto socket = static_cast<QTcpSocket *>(sender());
    QDataStream readStream(socket);
    qint16 sizeRead;
    qint8 type;

    readStream >> sizeRead;

    /* waiting till we get full data */
    if (socket->bytesAvailable() < sizeRead) return;
    readStream >> type;
    /* TODO: SQL database with usernames and passwords. */
    /* No password checking yet. */
    if (type == DataType::AuthRequest)
    {
        AuthData read;
        readStream >> read;
        emit authRequestRead(socket, read);
    }

    if (type == DataType::AuthResponse)
    {
        AuthAnswer read;
        readStream >> read;
        emit authAnswerRead(read);
    }

}

