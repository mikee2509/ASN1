#include "ASNUTF8String.h"

using namespace std;

ASNUTF8String::ASNUTF8String(const string& newstr)
{
    str = newstr;
    tag = 12;
    isConstructed = 0;
    isIndefinite = 0;
    length = newstr.length();
    serialize();
}

ASNUTF8String ASNUTF8String::operator=(const string& newstr)
{
    str = newstr;
    length = newstr.length();
    data.clear();
    serialize();
    return *this;
}

void ASNUTF8String::deserialize(const vector<char>& buffer)
{
    int initialLength = length;

    vector<char> initialOctets(buffer.begin(), buffer.begin()+16);
    taglength(initialOctets);

    if(isConstructed) {
        length = initialLength;
        isConstructed = 0;
        isIndefinite = 0;
        throw invalid_argument("ASN.1 UTF8String cannot be constructed");
    }
    if(isIndefinite) {
        length = initialLength;
        isConstructed = 0;
        isIndefinite = 0;
        throw invalid_argument("ASN.1 UTF8String must be of definite length");
    }

    str.clear();
    vector<char> dataOctets(buffer.begin()+16, buffer.begin()+16+8*length);
    string binary;
    char character;
    for(int i=0; i<8*length; i+=8)
    {
        binary = string(dataOctets.begin()+i, dataOctets.begin()+i+8);
        character = bitset<8>(binary).to_ulong();
        str.push_back(character);
    }
}

void ASNUTF8String::serialize()
{
    data = taglength(tag, length, isConstructed, isIndefinite);
    string binary;
    for(int i=0; i<length; i++)
    {
        binary = bitset<8>((int)str[i]).to_string();
        data.insert(data.end(), binary.begin(), binary.end());
    }
}



