#ifndef ASNOBJECT_H
#define ASNOBJECT_H
#include <vector>
#include <iostream>
#include <bitset>
#include <exception>
#include <algorithm>

//! Base class for all ASN.1 types' objects
class ASNObject
{
protected:
    std::vector<char> data;
    int tag; //!< ASN.1 data type tag
    int length; //!< Number of octets used to encode the data
    bool isConstructed; //!< Whether the contents octets contain 0, 1, or more element encodings
    bool isIndefinite; //!< Whether the length is defined or the content octets finish at marker octets
public:
    /*! \brief Function encodes tag, length and value of ASN.1 Object according to BER standard
               and saves the results in *data*. */
    virtual void serialize() = 0;
    virtual void deserialize(const std::vector<char> &buffer) = 0;

    //! Function returning identifier and length octets.
    /*! These two octets give information about each ASN.1 data structure. */
    std::vector<char> taglength(int tag, int length, bool isConstructed=0, bool isIndefinite=0);

    void taglength(const std::vector<char> &tags);

    int getLength() { return length; } //!< Returns the length of the object
    int getTag() { return tag; } //!< Returns object's tag
    std::vector<char> getData() { return data; } //!< Gives access to object's data
    bool getConstructed() { return isConstructed; }
    bool getIndefinite() { return isIndefinite; }
};

#endif // ASNOBJECT_H
