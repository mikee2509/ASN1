#ifndef ASNINTENUM_H
#define ASNINTENUM_H

#include "ASNObject.h"

//! Base class for ASN.1 INTEGER and ENUMERATED data types
class ASNIntEnum : virtual public ASNObject
{
protected:
    int number; //!< Decimal number

    void setLength(int decimalNum); //!< Calculates length from decimal number passed in argument

    //! Constructor for INTEGER or ENUMERATED
    /*! Creates new object of chosen type with appropriate length
        \param tagvalue : 2 for INTEGER, 10 for ENUMERATED
        \param n : number to be saved in object */
    ASNIntEnum(int tagvalue, int n=0);

    ASNIntEnum(const ASNIntEnum &asnint); //!< Copy constructor
    ASNIntEnum operator=(int newValue); //!< Assigns new value to the object and recalculates length

public:
    virtual ~ASNIntEnum() {}
    virtual void serialize();
    virtual void deserialize(const std::vector<char> &buffer);

    int getNumber() { return number; }
};

#endif // ASNINTENUM_H
