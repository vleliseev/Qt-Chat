#include "userlist.h"

UserList::UserList(const QList<UserData> &users) :
    users(users)
{ }


QDataStream& UserList::toStream(QDataStream &stream) const
{
    stream << users;
    return stream;
}
QDataStream& UserList::fromStream(QDataStream &stream)
{
    stream >> users;
    return stream;
}
size_t UserList::size() const
{
    return users.size();
}

DataType UserList::type() const
{
    return UserListResponse;
}

QList<UserData> UserList::getUsers() const
{
    return users;
}
