#include "ASNBitstring.h"

using namespace std;

void ASNBitstring::setLength(const string& bitstr)
{
    int x = bitstr.length();
    if(x%8) length = (x/8)+2;
    else length = (x/8)+1;
}

void ASNBitstring::strCheck(const std::string& bitstr)
{
    if(any_of(bitstr.begin(), bitstr.end(), [](char i){ return (i!='0' && i!='1'); } ))
        throw invalid_argument("Unrecognised character in bitstring");
}

ASNBitstring::ASNBitstring(const string& newstr)
{
    strCheck(newstr);
    str = newstr;
    tag = 3;
    isConstructed = 0;
    isIndefinite = 0;
    setLength(newstr);
    serialize();
}

ASNBitstring ASNBitstring::operator=(const string& newstr)
{
    strCheck(newstr);
    str = newstr;
    setLength(newstr);
    data.clear();
    serialize();
    return *this;
}

void ASNBitstring::serialize()
{
    data = taglength(tag, length, isConstructed, isIndefinite);
    int offset = ((length-1)*8)-str.length();
    string binoffset = bitset<8>(offset).to_string();
    data.insert(data.end(), binoffset.begin(), binoffset.end());
    data.insert(data.end(), str.begin(), str.end());
    data.insert(data.end(), offset, '0');
}

void ASNBitstring::deserialize(const vector<char>& buffer)
{
    int initialLength = length;

    vector<char> initialOctets(buffer.begin(), buffer.begin()+16);
    taglength(initialOctets);

    if(isConstructed) {
        length = initialLength;
        isConstructed = 0;
        isIndefinite = 0;
        throw invalid_argument("ASN.1 Bitstring cannot be constructed");
    }
    if(isIndefinite) {
        length = initialLength;
        isConstructed = 0;
        isIndefinite = 0;
        throw invalid_argument("ASN.1 Bitstring must be of definite length");
    }

    strCheck(string(buffer.begin()+16, buffer.end()));

    string binoffset(buffer.begin()+16, buffer.begin()+24);
    int offset = bitset<8>(binoffset).to_ulong();
    if(offset<0 || offset>8) throw invalid_argument("Invalid offset value");

    data = vector<char>(buffer.begin(), buffer.begin()+16+8*length);
    str = string(buffer.begin()+24, buffer.begin()+24+8*(length-1)-offset);
}
