#ifndef AUTHDATA_H
#define AUTHDATA_H

#include "basedata.h"

#include <QString>
class AuthData : public BaseData
{
public:

    AuthData(QObject *parent = nullptr);
    AuthData(const QString &login, const QString &password, QObject *parent = nullptr);

    virtual QDataStream& toStream(QDataStream &stream) override;
    virtual QDataStream& fromStream(QDataStream &stream) override;
    virtual size_t size() override;
    virtual DataType type() override;

    void setPassword(const QString &password);
    void setLogin(const QString &login);

    QString getPassword();
    QString getLogin();

private:
    QString login;
    QString password;
};


#endif // AUTHDATA_H
