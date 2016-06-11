#include "IStorable.h"

using namespace std;

void IStorable::saveData(const string &filename)
{
    ofstream file;
    file.open(filename, ofstream::binary);
    for_each(data.begin(), data.end(), [&](char c) { file << c; });
    file.close();
}

void IStorable::saveHex(const std::string& filename)
{
    ofstream file;
    file.open(filename);
    bitset<4> bin;
    unsigned num, i,j,k;
    for(i=0; i<data.size(); i+=4)
    {
        for(j=i, k=3; j<i+4; j++, k--)
        {
            bin.set(k, data[j]-'0');
        }
        num = bin.to_ulong();
        file << hex << num;
        if (!((i+4)%8)) file << " ";
    }
    file.close();
}

