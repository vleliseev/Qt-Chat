#ifndef BASEDATA_H
#define BASEDATA_H

#include <QDataStream>

enum DataType : qint8
{
    None,
    Ping,
    AuthRequest,
    AuthResponse,
    UserListResponse,
    NewConnection,
    Disconnection
};

class BaseData
{
public:
    explicit BaseData();

    friend QDataStream &operator >> (QDataStream &stream, BaseData &data);
    friend QDataStream &operator << (QDataStream &stream, BaseData &data);

    virtual QDataStream& toStream(QDataStream &stream) = 0;
    virtual QDataStream& fromStream(QDataStream &stream) = 0;
    virtual size_t size() = 0;
    virtual DataType type() = 0;
};

QDataStream &operator >> (QDataStream &stream, BaseData &data);
QDataStream &operator << (QDataStream &stream, BaseData &data);

#endif // BASEDATA_H
