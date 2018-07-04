#include "authanswer.h"

AuthAnswer::AuthAnswer(bool answer) :
    answer(answer)
{ }

QDataStream& AuthAnswer::toStream(QDataStream &stream) const
{
    stream << answer;
    return stream;
}

QDataStream& AuthAnswer::fromStream(QDataStream &stream)
{
    stream >> answer;
    return stream;
}

size_t AuthAnswer::size() const
{
    return sizeof(bool);
}

DataType AuthAnswer::type() const
{
    return DataType::AuthResponse;
}

bool AuthAnswer::isSigned() const
{
    return answer;
}

void AuthAnswer::setSigned(bool answer)
{
    this->answer = answer;
}
