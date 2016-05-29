#include "main.h"

using namespace std;

int main()
{
    try
    {
        ASNInteger a;
        vector<char> aVect {'0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','1','0','0','0','1','0','0','0','0'};
        a.deserialize(aVect);
        cout << "Tag: " << a.getTag() << endl;
        cout << "Length: " << a.getLength() << endl;
        cout << "Number: " << a.getNumber() << endl;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}
