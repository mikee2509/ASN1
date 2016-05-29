#include "ASNObject.h"

using namespace std;

vector<char> ASNObject::taglength(int tag, int length, bool isConstructed, bool isIndefinite)
{
    if (tag>31 || tag<0) throw invalid_argument("Invalid tag number");
    if (length<0 || length>127) throw invalid_argument("Invalid length");
    vector<char> data;
    string bin = bitset<8>(tag).to_string();
    if(isConstructed) bin[2]='1';
    for(int i=0; i<8; i++)
        data.push_back(bin[i]);
    bin = bitset<8>(length).to_string();
    if(isIndefinite) bin[0]='1';
    for(int i=0; i<8; i++)
        data.push_back(bin[i]);
    return data;
}

void ASNObject::taglength(const vector<char> &code)
{
    if(any_of(code.begin(), code.end(), [](char i){ return (i!='0' && i!='1'); } ))
        throw invalid_argument("Unrecognised character");
    if(code[0]!='0' || code[1]!='0') throw invalid_argument("Only types native to ASN.1 accepted");
    isConstructed = code[2]-'0';
    isIndefinite = code[8]-'0';
    if(isIndefinite)
        if(any_of(code.begin()+9, code.end(), [](char i){ return i!='0'; } ))
            throw invalid_argument("Indefinite length set but bits encoding length are not 0s");

    bitset<5> bintag;
    for(int i=3, j=4; i<8; i++, j--)
        bintag.set(j, code[i]-'0');
    if((unsigned)tag != bintag.to_ulong()) throw invalid_argument("Tag doesn't match the object's type");

    bitset<7> binlength;
    for(int i=9, j=6; i<16; i++, j--)
        binlength.set(j, code[i]-'0');
    length = binlength.to_ulong();
}
