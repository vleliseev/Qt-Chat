#include "datahandler.h"


DataHandler::DataHandler(QObject *parent) : QObject(parent)
{

}
void DataHandler::write(QTcpSocket *socket, BaseData &from)
{
    QByteArray datagram;
    QDataStream writeStream(&datagram, QIODevice::WriteOnly);
    qint16 size = sizeof(qint8) + from.size();
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
    if (socket->bytesAvailable() < sizeRead) return;
    readStream >> type;

    if (type == DataType::AuthRequest)
    {
        AuthData read;
        readStream >> read;
        emit authRequest(socket, read);
    }

    if (type == DataType::AuthResponse)
    {
        AuthAnswer read;
        readStream >> read;
        qDebug() << read.isSigned();
        emit authAnswer(read);
    }

}

