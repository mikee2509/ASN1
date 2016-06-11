#include "main.h"

using namespace std;

int main()
{
    try
    {
        Osoba student("Michal", "Sieczkowski", 19, 1, "1111");
        Osoba ktos("Jan", "Kowalski", 56, 1, "1010");
        Osoba dziewczyna("Joanna", "Mucha", 23, 0, "0111");

        student.wyswietl();
        ktos.wyswietl();
        dziewczyna.wyswietl();

        student.saveData("student.txt");
        dziewczyna.saveHex("dziewczyna.txt");
        return 0;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}
