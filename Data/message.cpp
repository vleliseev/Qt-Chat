#include "message.h"

Message::Message() :
    textFont(QFont("Gadugi", 15)),
    textColor(QColor(Qt::red))
{   }

Message::Message(const QString &sender,
                 const QString &message,
                 const QFont &font,
                 const QColor &color,
                 const QPixmap &image) :
    sender(sender),
    message(message),
    textFont(font),
    textColor(color),
    image(image)
{   }

QDataStream& Message::fromStream(QDataStream &stream)
{
    stream >> sender;
    stream >> message;
    stream >> textFont;
    stream >> textColor;
    stream >> image;
    return stream;
}

DataType Message::type() const
{
    return DataType::Msg;
}

QDataStream& Message::toStream(QDataStream &stream) const
{
    stream << sender;
    stream << message;
    stream << textFont;
    stream << textColor;
    stream << image;
    return stream;
}

void Message::setMessage(const QString &message)
{
    this->message = message;
}

void Message::setSender(const QString &sender)
{
    this->sender = sender;
}

void Message::setTextFont(const QFont &font)
{
    textFont = font;
}

void Message::setTextColor(const QColor &color)
{
    textColor = color;
}

void Message::setImage(const QPixmap &image)
{
    this->image = image;
}

QString Message::getMessage() const
{
    return message;
}

QString Message::getSender() const
{
    return sender;
}

QFont Message::getTextFont() const
{
    return textFont;
}

QColor Message::getTextColor() const
{
    return textColor;
}

QPixmap Message::getImage() const
{
    return image;
}
