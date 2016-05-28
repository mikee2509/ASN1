#include "main.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    ASNInteger a(0);
    vector<char> vref = a.taglength(12,36);
    vector<char>::iterator it;
    for (it=vref.begin(); it<vref.end(); it++)
        cout << *it;
cout << endl << endl;
    ASNInteger wiek(16);
    vector<char> temp = wiek.serialize();
    for(it=temp.begin(); it<temp.end(); it++)
        cout << *it;
    return 0;
}
