#include "IASNSequence.h"

using namespace std;

void IASNSequence::printAll()
{
    cout << "======ASN.1 Sequence======" << endl;
    printTag();
    printLength();
    printData();
    printConstructed();
    printIndefinite();
    cout << "CONTAINS:" << endl;
    printObjects();
    cout << "==========================" << endl;
}

void IASNSequence::printObjects()
{
    for_each(objects.begin(), objects.end(), [](shared_ptr<ASNObject> obj)->void {
        shared_ptr<IASNInteger> intptr = dynamic_pointer_cast<IASNInteger>(obj);
        if(intptr) { cout << endl; intptr->printAll(); return; }
        shared_ptr<IASNEnumerated> enumptr = dynamic_pointer_cast<IASNEnumerated>(obj);
        if(enumptr) { cout << endl; enumptr->printAll(); return; }
        shared_ptr<IASNBitstring> bitptr = dynamic_pointer_cast<IASNBitstring>(obj);
        if(bitptr) { cout << endl; bitptr->printAll(); return; }
        shared_ptr<IASNUTF8String> utfptr = dynamic_pointer_cast<IASNUTF8String>(obj);
        if(utfptr) { cout << endl; utfptr->printAll(); return; }
              });
}
