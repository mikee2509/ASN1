#ifndef ASNINTEGER_H
#define ASNINTEGER_H

#include "ASNObject.h"

//! ASN.1 INTEGER data type
class ASNInteger : public ASNObject
{
private:
    int number; //!< Decimal integer

    void setLength(int decimalNum); //!< Calculates length from decimal number passed in argument
public:
    //! Standard constructor
    /*! Creates new object with appropriate length
        \param n : number to be saved in object */
    ASNInteger(int n=0);

    ASNInteger(const ASNInteger &asnint); //!< Copy constructor
    ASNInteger operator=(int newValue); //!< Assigns new value to the object and recalculates length

    virtual void serialize();
    virtual void deserialize(const std::vector<char> &buffer);

    int getNumber() { return number; }
};

#endif // ASNINTEGER_H
