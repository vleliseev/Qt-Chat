#include "userlist.h"

UserList::UserList(const QList<QString> &users) :
    users(users)
{ }


QDataStream& UserList::toStream(QDataStream &stream)
{
    stream << users;
    return stream;
}
QDataStream& UserList::fromStream(QDataStream &stream)
{
    stream >> users;
    return stream;
}
size_t UserList::size()
{
    return users.size();
}

DataType UserList::type()
{
    return UserListResponse;
}

QList<QString> UserList::getUsers() const
{
    return users;
}

