#include "IASNBitstring.h"

using namespace std;

void IASNBitstring::printAll()
{
    cout << "---ASN.1 Bitstring---" << endl;
    printStr();
    printTag();
    printLength();
    printData();
    printConstructed();
    printIndefinite();
    cout << "---------------------" << endl;
}

void IASNBitstring::printStr()
{
    cout << "String: " << str << endl;
}

