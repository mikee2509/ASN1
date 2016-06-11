#ifndef ASNBITSTRING_H
#define ASNBITSTRING_H

#include "ASNObject.h"

//! ASN.1 Bitstring data structure
class ASNBitstring : virtual public ASNObject
{
protected:
    std::string str; //!< Stored bitstring

    void setLength(const std::string &bitstr); //!< Calculates length from bitstring passed in argument
    void strCheck(const std::string &bitstr); //!< Checks whether *bitstr* have other characters than 1 or 0, if so an exception is thrown
public:
    virtual ~ASNBitstring() {}
    //! Standard constructor
    /*! Creates new object with appropriate length
        \param newstr : bitstring to be saved in object */
    ASNBitstring(const std::string &newstr);

    ASNBitstring operator=(const std::string &newstr); //!< Assigns new value to the object and recalculates length

    virtual void serialize();
    virtual void deserialize(const std::vector<char> &buffer);

    std::string getStr() { return str; } //!< Returns the stored bitsting
};

#endif // ASNBITSTRING_H
