#include "basedata.h"

BaseData::BaseData(QObject *parent) : QObject(parent)
{ }


QDataStream &operator << (QDataStream &stream, BaseData &data)
{
    return data.toStream(stream);
}

QDataStream &operator >> (QDataStream &stream, BaseData &data)
{
    return data.fromStream(stream);
}
