#include "main.h"

using namespace std;

int main()
{
    try
    {
        string lols = "a";
        ASNUTF8String nowy(lols);
        vector<char> temp = nowy.getData();
        for_each(temp.begin(), temp.end(), [](char i)->void { cout<<i; });
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}
