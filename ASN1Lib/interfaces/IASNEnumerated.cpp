#include "IASNEnumerated.h"

using namespace std;

void IASNEnumerated::printAll()
{
    cout << "---ASN.1 Enumerated---" << endl;
    printNumber();
    printTag();
    printLength();
    printData();
    printConstructed();
    printIndefinite();
    cout << "----------------------" << endl;
}

void IASNEnumerated::printNumber()
{
    cout << "Number: " << number << endl;
}
