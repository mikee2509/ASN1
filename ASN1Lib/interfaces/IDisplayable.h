#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

#include "../ASNObject.h"

class IDisplayable : virtual public ASNObject
{
public:
    virtual void printAll() = 0;
    virtual void printData();
    virtual void printTag();
    virtual void printLength();
    virtual void printConstructed();
    virtual void printIndefinite();
};

#endif // IDISPLAYABLE_H
