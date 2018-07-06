#include "message.h"

Message::Message() :
    textFont(QFont("Gadugi", 20)),
    textColor(QColor(Qt::red))
{   }

Message::Message(const QString &receiver, const
                 QString &message,
                 const QFont &font,
                 const QColor &color,
                 const QPixmap &image) :
    receiver(receiver),
    message(message),
    textFont(font),
    textColor(color),
    image(image)
{   }

QDataStream& Message::fromStream(QDataStream &stream)
{
    stream >> receiver;
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
    stream << receiver;
    stream << message;
    stream << textFont;
    stream << textColor;
    stream << image;
    return stream;
}

void Message::setReceiver(const QString &receiver)
{
    this->receiver = receiver;
}

void Message::setMessage(const QString &message)
{
    this->message = message;
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


QString Message::getReceiver() const
{
    return receiver;
}

QString Message::getMessage() const
{
    return message;
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
