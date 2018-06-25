#ifndef AUTHANSWER_H
#define AUTHANSWER_H

#include "basedata.h"

class AuthAnswer : public BaseData
{
    Q_OBJECT
public:
    AuthAnswer(bool answer, QObject *parent = nullptr);
    AuthAnswer(QObject *parent = nullptr);

    virtual QDataStream& toStream(QDataStream &stream) override;
    virtual QDataStream& fromStream(QDataStream &stream) override;
    virtual size_t size() override;
    virtual DataType type() override;

    /* returns true on successful authentication */
    bool isSigned() const;

private:
    bool answer;
};

#endif // AUTHANSWER_H
