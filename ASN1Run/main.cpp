#include "main.h"

using namespace std;

int main()
{
    try
    {
        string test("111000110");
        IASNBitstring two(test);
        two.printAll();
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}
