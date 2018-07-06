#ifndef USERLIST_H
#define USERLIST_H

#include "userdata.h"

class UserList : public BaseData
{
public:

    UserList() = default;
    UserList(const QList<UserData> &users);

    virtual QDataStream& toStream(QDataStream &stream) const override;
    virtual QDataStream& fromStream(QDataStream &stream) override;
    virtual DataType type() const override;

    QList<UserData> getUsers() const;

private:

    QList<UserData> users;

};
#endif // USERLIST_H
