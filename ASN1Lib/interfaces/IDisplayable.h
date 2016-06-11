#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

#include "../ASNObject.h"

//! Base class for all interfaces of ASNObject's subclasses
class IDisplayable : virtual public ASNObject
{
public:
    virtual ~IDisplayable() {}
    virtual void printAll() = 0;
    virtual void printData();
    virtual void printTag();
    virtual void printLength();
    virtual void printConstructed();
    virtual void printIndefinite();
};

#endif // IDISPLAYABLE_H
