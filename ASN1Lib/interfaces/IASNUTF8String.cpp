#include "IASNUTF8String.h"

using namespace std;

void IASNUTF8String::printAll()
{
    cout << "---ASN.1 UTF8String---" << endl;
    printStr();
    printTag();
    printLength();
    printData();
    printConstructed();
    printIndefinite();
    cout << "----------------------" << endl;
}

void IASNUTF8String::printStr()
{
    cout << "String: " << str << endl;
}
