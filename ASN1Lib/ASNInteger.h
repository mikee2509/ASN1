#ifndef ASNINTEGER_H
#define ASNINTEGER_H

#include "ASNObject.h"


class ASNInteger : public ASNObject
{
private:
    int number;
public:
//    ASNInteger();
//    virtual ~ASNInteger();

    virtual void serialize(char *buffer);
    virtual void deserialize(char *buffer);
};

#endif // ASNINTEGER_H
