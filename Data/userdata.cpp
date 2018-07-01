#include "userdata.h"

UserData::UserData(const QString &username) :
    username(username)
{   }

QDataStream& UserData::toStream(QDataStream &stream)
{
    stream << username;
    return stream;
}
QDataStream& UserData::fromStream(QDataStream &stream)
{
    stream >> username;
    return stream;
}
size_t UserData::size()
{
    return username.size();
}
DataType UserData::type()
{
    return None;
}

QString UserData::getUsername() const
{
    return username;
}

void UserData::setUsername(const QString &username)
{
    this->username = username;
}
