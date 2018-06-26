#include "authdata.h"

AuthData::AuthData(QObject *parent) :
    BaseData(parent)
{ }

AuthData::AuthData(const QString &login, const QString &password, QObject *parent) :
    BaseData(parent),
    login(login),
    password(password)
{ }

QDataStream& AuthData::toStream(QDataStream &stream)
{
    stream << this->login;
    stream << this->password;
    return stream;
}
QDataStream& AuthData::fromStream(QDataStream &stream)
{
    stream >> this->login;
    stream >> this->password;
    return stream;
}

QString AuthData::getLogin()
{
    return this->login;
}

QString AuthData::getPassword()
{
    return this->password;
}

void AuthData::setLogin(const QString &login)
{
    this->login = login;
}

void AuthData::setPassword(const QString &password)
{
    this->password = password;
}

size_t AuthData::size()
{
    return login.size() + password.size();
}

DataType AuthData::type()
{
    return AuthRequest;
}
