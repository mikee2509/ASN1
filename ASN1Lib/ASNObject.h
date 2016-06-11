#ifndef ASNOBJECT_H
#define ASNOBJECT_H
#include <vector>
#include <iostream>
#include <bitset>
#include <exception>
#include <algorithm>
#include <memory>
#include <iterator>
#include "exceptions.h"

//! Base class for all ASN.1 structures
class ASNObject
{
protected:
    std::vector<char> data;
    int tag; //!< ASN.1 data type tag
    int length; //!< Number of octets used to encode the data
    bool isConstructed; //!< Whether the contents octets contain 0, 1, or more element encodings
    bool isIndefinite; //!< Whether the length is defined or the content octets finish at marker octets
public:
    virtual ~ASNObject() {}
    //! Encodes tag, length and value of ASN.1 Object according to BER standard.
    /*! The results are saved in *data* vector. */
    virtual void serialize() = 0;

    //! Reads the encoded data from *buffer* and changes the object's attributes values.
    virtual void deserialize(const std::vector<char> &buffer) = 0;

    //! Returns identifier and length octets.
    /*! These two octets give information about each ASN.1 data structure. */
    std::vector<char> taglength(int tag, int length, bool isConstructed=0, bool isIndefinite=0);

    //! Sets object's attributes based on given encoded octets.
    /*! Function modifies *length*, *isConstructed* and *isIndefinite* values. */
    void taglength(const std::vector<char> &code);

    int getLength() { return length; }
    int getTag() { return tag; }
    std::vector<char> getData() { return data; }
    bool getConstructed() { return isConstructed; }
    bool getIndefinite() { return isIndefinite; }
};

#endif // ASNOBJECT_H
