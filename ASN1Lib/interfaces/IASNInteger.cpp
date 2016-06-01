#include "IASNInteger.h"

using namespace std;

void IASNInteger::printAll()
{
    cout << "---ASN.1 INTEGER---" << endl;
    printNumber();
    printTag();
    printLength();
    printData();
    printConstructed();
    printIndefinite();
    cout << "-------------------" << endl;
}

void IASNInteger::printNumber()
{
    cout << "Integer: " << number << endl;
}
