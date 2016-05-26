#ifndef ASNOBJECT_H
#define ASNOBJECT_H
#include <vector>
#include <iostream>
#include <bitset>
#include <exception>

//! Base class for all ASN.1 types' objects
class ASNObject
{
private:
    std::vector<char> data;
    int tag;
    int length;
public:
    //ASNObject();
    virtual void serialize(char* buffer) = 0;
    virtual void deserialize(char* buffer) = 0;

    std::vector<char> taglength(int tag, int length, bool isConstructed=0);
};

#endif // ASNOBJECT_H
