#include "userdata.h"

UserData::UserData() :
    userFont(QFont("Gadugi", 12)),
    userColor(Qt::red)
{   }

UserData::UserData(const QString &username, const QFont &font, const QColor &color) :
    username(username),
    userFont(font),
    userColor(color)
{   }


QDataStream& UserData::toStream(QDataStream &stream) const
{
    stream << username << password << userFont << userColor;
    return stream;
}

QDataStream& UserData::fromStream(QDataStream &stream)
{
    stream >> username >> password >> userFont >> userColor;
    return stream;
}

size_t UserData::size() const
{
    return username.size();
}

DataType UserData::type() const
{
    return None;
}

void UserData::setUsername(const QString &username)
{
    this->username = username;
}

void UserData::setPassword(const QString &password)
{
    this->password = password;
}

void UserData::setFont(const QFont &font)
{
    userFont = font;
}

void UserData::setColor(const QColor &color)
{
    userColor = color;
}

QString UserData::getUsername() const
{
    return username;
}

QString UserData::getPassword() const
{
    return password;
}

QFont UserData::getFont() const
{
    return userFont;
}

QColor UserData::getColor() const
{
    return userColor;
}

bool operator <(const UserData &tmp1, const UserData &tmp2)
{
    return tmp1.getUsername() < tmp2.getUsername();
}
