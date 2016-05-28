#include "ASNInteger.h"

using namespace std;

ASNInteger::ASNInteger(int n)
{
    number = n;
    if(n>=-128 && n<=127) length = 1;
    else if(n>=-32768 && n<=32767) length = 2;
    else if(n>=-8388608 && n<=8388607) length = 3;
    else if(n>=-2147483648 && n<=2147483647) length = 4;
    else throw length_error("Maximal integer size is 4 bytes");
    serialize();
}

vector<char> ASNInteger::serialize()
{
    if(!data.empty()) return data;
//    cout << "Serialize" << endl;
    data = taglength(tag, length, 0, 0);
    const int len = length*8;
    string bin = bitset<32>(number).to_string();
    for(int i=32-len; i<32; i++)
        data.push_back(bin[i]);
    return data;
}

void ASNInteger::deserialize(char* buffer)
{
    cout << "Deserialize" << endl;
}
