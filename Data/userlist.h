#ifndef USERLIST_H
#define USERLIST_H

#include "authdata.h"

class UserList : public BaseData
{
public:

    UserList() = default;
    UserList(QList<QString> &users);


    virtual QDataStream& toStream(QDataStream &stream) override;
    virtual QDataStream& fromStream(QDataStream &stream) override;
    virtual size_t size() override;
    virtual DataType type() override;

    QList<QString> getUsers() const;


private:

    QList<QString> users;

};
#endif // USERLIST_H
