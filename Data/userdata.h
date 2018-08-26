#ifndef USERDATA_H
#define USERDATA_H

#include <QFont>
#include <QColor>

#include "basedata.h"

class UserData : public BaseData
{

public:

    UserData();
    UserData(const QString &username,
             const QFont &font = QFont("Gadugi", 20),
             const QColor &color = Qt::red);


    void setUsername(const QString &username);
    void setFont(const QFont &font);
    void setColor(const QColor &color);
    void setPassword(const QString &password);
    void setType(const DataType type);

    QString getUsername() const;
    QString getPassword() const;
    QFont getFont() const;
    QColor getColor() const;

    virtual QDataStream& toStream(QDataStream &stream) const override;
    virtual QDataStream& fromStream(QDataStream &stream) override;
    virtual DataType type() const override;


private:

    QString username;
    QString password;
    QFont userFont;
    QColor userColor;
    DataType currentType;
};

// Compare order for UserData if it is a key in QMap
bool operator <(const UserData &tmp1, const UserData &tmp2);



#endif // USERDATA_H
