#ifndef IASNUTF8STRING_H
#define IASNUTF8STRING_H

#include "IDisplayable.h"
#include "../ASNUTF8String.h"

class IASNUTF8String : public IDisplayable, public ASNUTF8String
{
public:
    IASNUTF8String(std::string &str): ASNUTF8String(str) {}
    void printAll();
    void printStr();

};

#endif // IASNUTF8STRING_H
