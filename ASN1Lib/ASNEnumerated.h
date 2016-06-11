#ifndef ASNENUMERATED_H
#define ASNENUMERATED_H

#include "ASNIntEnum.h"

//! ASN.1 ENUMERATED data type
class ASNEnumerated : public ASNIntEnum
{
public:
    virtual ~ASNEnumerated() {}
    //! Standard constructor
    /*! Creates new object with appropriate length
        \param n : number to be saved in object */
    ASNEnumerated(int n=0): ASNIntEnum(10, n) {}
};

#endif // ASNENUMERATED_H
