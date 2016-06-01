#include "IDisplayable.h"

using namespace std;

void IDisplayable::printIndefinite()
{
    cout << "isIndefinite: " << isIndefinite << endl;
}

void IDisplayable::printConstructed()
{
    cout << "isConstructed: " << isConstructed << endl;
}

void IDisplayable::printLength()
{
    cout << "Length: " << length << endl;
}

void IDisplayable::printTag()
{
    cout << "Tag: " << tag << endl;
}

void IDisplayable::printData()
{
    cout << "Serialized data: ";
    //for_each(data.begin(), data.end(), [](char i)->void { cout << i; });
    vector<char>::iterator it;
    int i;
    for(i=0, it=data.begin(); it!=data.end(); it++, i++)
    {
        if(i==0)           cout << endl << "   Tag: ";
        if(i==8)           cout << endl << "Length: ";
        if(i==16)          cout << endl << " Value: ";
        if(!(i%8) && i>16) cout << endl << "        ";

        cout << *it;
    }

    cout << endl;
}

