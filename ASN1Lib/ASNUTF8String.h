#ifndef ASNUTF8STRING_H
#define ASNUTF8STRING_H

#include "ASNObject.h"

//! ASN.1 UTF8String data structure
class ASNUTF8String : virtual public ASNObject
{
protected:
    std::string str; //!< Stored string
public:
    virtual ~ASNUTF8String() {}
    //! Standard constructor
    /*! Creates new object with appropriate length
        \param newstr : string to be saved in object */
    ASNUTF8String(const std::string &newstr);

    ASNUTF8String operator=(const std::string &newstr); //!< Assigns new value to the object and recalculates length

    virtual void serialize();
    virtual void deserialize(const std::vector<char> &buffer);

    std::string getStr() { return str; } //!< Returns the stored bitsting
};

#endif // ASNUTF8STRING_H
