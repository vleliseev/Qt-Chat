#ifndef MESSAGE_H
#define MESSAGE_H

#include <QPixmap>
#include <QFont>
#include <QColor>

#include "basedata.h"

class Message : public BaseData
{

public:

    Message();
    Message(const QString &sender, const QString &message = "",
            const QFont &font = QFont("Gadugi", 15),
            const QColor &color = QColor(Qt::red),
            const QPixmap &image = QPixmap());


    virtual QDataStream& toStream(QDataStream &stream) const override;
    virtual QDataStream& fromStream(QDataStream &stream) override;
    virtual DataType type() const override;


    void setTextColor(const QColor &color);
    void setTextFont(const QFont &font);
    void setImage(const QPixmap &image);
    void setMessage(const QString &message);
    void setSender(const QString &sender);


    QColor getTextColor() const;
    QFont getTextFont() const;
    QPixmap getImage() const;
    QString getMessage() const;
    QString getSender() const;

private:

    QString sender;
    QString message;
    QFont textFont;
    QColor textColor;
    QPixmap image;

};

#endif // MESSAGE_H
