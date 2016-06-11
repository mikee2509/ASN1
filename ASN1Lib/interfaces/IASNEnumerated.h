#ifndef IASNENUMERATED_H
#define IASNENUMERATED_H

#include "IDisplayable.h"
#include "IStorable.h"
#include "../ASNEnumerated.h"

//! Interface class for ASNEnumerated
class IASNEnumerated : public IDisplayable, public IStorable, public ASNEnumerated
{
public:
    IASNEnumerated(int i=0): ASNEnumerated(i) {}
    void printAll();
    void printNumber();

};
#endif // IASNENUMERATED_H
