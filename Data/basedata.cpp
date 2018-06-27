#include "basedata.h"

BaseData::BaseData()
{ }


QDataStream &operator << (QDataStream &stream, BaseData &data)
{
    return data.toStream(stream);
}

QDataStream &operator >> (QDataStream &stream, BaseData &data)
{
    return data.fromStream(stream);
}
