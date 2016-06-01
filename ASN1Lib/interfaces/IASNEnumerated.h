#ifndef IASNENUMERATED_H
#define IASNENUMERATED_H

#include "IDisplayable.h"
#include "../ASNEnumerated.h"

class IASNEnumerated : public IDisplayable, public ASNEnumerated
{
public:
    IASNEnumerated(int i=0): ASNEnumerated(i) {}
    void printAll();
    void printNumber();

};
#endif // IASNENUMERATED_H
