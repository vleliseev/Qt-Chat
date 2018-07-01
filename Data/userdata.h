#ifndef USERDATA_H
#define USERDATA_H

#include "basedata.h"

class UserData : public BaseData
{
public:
    UserData() = default;
    UserData(const QString &username);

    void setUsername(const QString &username);
    QString getUsername() const;

    virtual QDataStream& toStream(QDataStream &stream) override;
    virtual QDataStream& fromStream(QDataStream &stream) override;
    virtual size_t size() override;
    virtual DataType type() override;



private:
    QString username;
};

#endif // USERDATA_H
