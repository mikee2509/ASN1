#ifndef ASNOBJECT_H
#define ASNOBJECT_H
#include <vector>
#include <iostream>
#include <bitset>
#include <exception>

//! Base class for all ASN.1 types' objects
class ASNObject
{
protected:
    std::vector<char> data;
    int tag; //!< ASN.1 type tag
    int length; //!< Number of octets needed to encode data
public:
    /*! Function encodes tag, length and value of ASN.1 Object according to BER standard
    \return STL vector of characters with encoded data */
    virtual std::vector<char> serialize() = 0;
    virtual void deserialize(const std::vector<char> &buffer) = 0;

    //! Function returning identifier and length octets.
    /*! These two octets give information about each ASN.1 data structure.
        \param tag : type's tag
        \param length : number of octets in which data is to be encoded
        \param isConstructed : whether the contents octets contain 0, 1, or more element encodings
        \param isIndefinite : whether the length is defined or the content octets finish at marker octets */
    std::vector<char> taglength(int tag, int length, bool isConstructed=0, bool isIndefinite=0);
};

#endif // ASNOBJECT_H
