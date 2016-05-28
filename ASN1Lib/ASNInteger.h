#ifndef ASNINTEGER_H
#define ASNINTEGER_H

#include "ASNObject.h"


class ASNInteger : public ASNObject
{
private:
    int number; //!< Decimal integer
    int tag = 2; //!< ASN.1 INTEGER type tag

    void setLength(int decimalNum); //!< Calculates length from decimal number passed in argument
public:
    //! Standard constructor
    /*! Creates new object with appropriate length
        \param n : number to be saved in object */
    ASNInteger(int n);
    ASNInteger(const ASNInteger &asnint); //!< Copy constructor
    ASNInteger operator=(int newValue); //!< Assigns new value to the object and recalculates length

    virtual std::vector<char> serialize();
    virtual void deserialize(const std::vector<char> &buffer);
};

#endif // ASNINTEGER_H
