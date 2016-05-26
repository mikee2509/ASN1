#include "ASNObject.h"

using namespace std;

vector<char> ASNObject::taglength(int tag, int length, bool isConstructed)
{
    if (tag>31 || tag<0) throw invalid_argument("Invalid tag number");
    if (length<0 || length>127) throw invalid_argument("Invalid length");
    vector<char> data;
    string bin = bitset<8>(tag).to_string();
    if(isConstructed) bin[2]='1';
    for(int i=0; i<8; i++)
        data.push_back(bin[i]);
    bin = bitset<8>(length).to_string();
    for(int i=0; i<8; i++)
        data.push_back(bin[i]);
    return data;
}
