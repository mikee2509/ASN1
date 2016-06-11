#ifndef IASNBITSTRING_H
#define IASNBITSTRING_H

#include "IDisplayable.h"
#include "IStorable.h"
#include "../ASNBitstring.h"

class IASNBitstring: public IDisplayable, public IStorable, public ASNBitstring
{
public:
    IASNBitstring(std::string str): ASNBitstring(str) {}
    void printAll();
    void printStr();
};

#endif // IASNBITSTRING_H
