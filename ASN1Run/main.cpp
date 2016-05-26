#include "main.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    ASNInteger a;
    vector<char> vref = a.taglength(12,36);
    vector<char>::iterator it;
    for (it=vref.begin(); it<vref.end(); it++)
        cout << *it;
    return 0;
}
