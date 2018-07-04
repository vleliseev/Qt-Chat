#include "basedata.h"

QDataStream &operator << (QDataStream &stream, const BaseData &data)
{
    return data.toStream(stream);
}

QDataStream &operator >> (QDataStream &stream, BaseData &data)
{
    return data.fromStream(stream);
}
