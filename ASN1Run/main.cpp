#include "main.h"
/*! \mainpage Project 3 documentation
 *  \section intro_sec ASN.1 Encoder and Decoder
 *    Library of classes for easy encoding and decoding ASN.1 data structures using BER format.
 * \author Michal Sieczkowski
 * \date 11.06.2016
 */
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
