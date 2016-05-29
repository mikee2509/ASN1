#include "ASNInteger.h"

using namespace std;

void ASNInteger::setLength(int n)
{
    if(n>=-128 && n<=127) length = 1;
    else if(n>=-32768 && n<=32767) length = 2;
    else if(n>=-8388608 && n<=8388607) length = 3;
    else if(n>=-2147483648 && n<=2147483647) length = 4;
    else throw length_error("Maximal integer size is 4 bytes");
}

ASNInteger::ASNInteger(int n)
{
    number = n;
    tag = 2;
    isConstructed = 0;
    isIndefinite = 0;
    setLength(number);
    serialize();
}

ASNInteger::ASNInteger(const ASNInteger &asnint)
{
    number = asnint.number;
    length = asnint.length;
    tag = asnint.tag;
    isConstructed = asnint.isConstructed;
    isIndefinite = asnint.isIndefinite;
    data.clear();
    serialize();
}

ASNInteger ASNInteger::operator=(int newValue)
{
    number = newValue;
    setLength(number);
    data.clear();
    serialize();
    return *this;
}

void ASNInteger::serialize()
{
    data = taglength(tag, length, isConstructed, isIndefinite);
    const int len = length*8;
    string bin = bitset<32>(number).to_string();
    for(int i=32-len; i<32; i++)
        data.push_back(bin[i]);
}

void ASNInteger::deserialize(const vector<char> &buffer)
{
    int initialLength = length;

    vector<char> initialOctets(buffer.begin(), buffer.begin()+16);
    taglength(initialOctets); //!< Now the number of octets used to store the new integer is known

    if(isConstructed) {
        length = initialLength;
        isConstructed = 0;
        isIndefinite = 0;
        throw invalid_argument("ASN.1 INTEGER cannot be constructed");
    }
    if(isIndefinite) {
        length = initialLength;
        isConstructed = 0;
        isIndefinite = 0;
        throw invalid_argument("ASN.1 INTEGER must be of definite length");
    }

    vector<char> dataOctets(buffer.begin()+16, buffer.begin()+16+8*length);

    int newNum = 0, pow = 1;
    for(int i=dataOctets.size()-1; i>=0; i--, pow <<= 1)
    {
        if(i==0) newNum += (dataOctets[i]-'0') * -pow;
        else newNum += (dataOctets[i]-'0') * pow;
    }
    number = newNum;

    data = initialOctets;
    data.insert(data.end(), dataOctets.begin(), dataOctets.end());

}
