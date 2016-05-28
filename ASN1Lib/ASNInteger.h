#ifndef ASNINTEGER_H
#define ASNINTEGER_H

#include "ASNObject.h"


class ASNInteger : public ASNObject
{
private:
    int number;
    int tag = 2;
public:
    ASNInteger(int n);
    //virtual ~ASNInteger();

    virtual std::vector<char> serialize();
    virtual void deserialize(char *buffer);
};

#endif // ASNINTEGER_H
