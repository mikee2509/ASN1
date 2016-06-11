#include "main.h"

using namespace std;

int main()
{
    try
    {
        string test("11100011");
        IASNBitstring two(test);
        two.printAll();
        two.saveData(string("Plikxyz.txt"));
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}
