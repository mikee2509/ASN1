#ifndef IASNINTEGER_H
#define IASNINTEGER_H

#include "IDisplayable.h"
#include "IStorable.h"
#include "../ASNInteger.h"

class IASNInteger : public IDisplayable, public IStorable, public ASNInteger
{
public:
    IASNInteger(int i=0): ASNInteger(i) {}
    void printAll();
    void printNumber();

};

#endif // IASNINTEGER_H
