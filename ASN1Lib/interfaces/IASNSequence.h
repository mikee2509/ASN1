#ifndef IASNSEQUENCE_H
#define IASNSEQUENCE_H

#include "../ASNSequence.h"
#include "IDisplayable.h"
#include "IStorable.h"
#include "IASNInteger.h"
#include "IASNUTF8String.h"
#include "IASNBitstring.h"
#include "IASNEnumerated.h"

//! Interface class for ASNSequence
class IASNSequence : public IDisplayable, public IStorable, public ASNSequence
{
public:
    IASNSequence(std::vector<std::shared_ptr<ASNObject>> &vec): ASNSequence(vec) {}
    IASNSequence(): ASNSequence() {}
    void printAll();
    void printObjects();
};

#endif // IASNSEQUENCE_H
