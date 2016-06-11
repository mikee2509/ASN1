#include "ASNSequence.h"

using namespace std;

void ASNSequence::setLength(vector<shared_ptr<ASNObject>>& ptrvec)
{
    for(unsigned i=0; i<ptrvec.size(); i++)
    {
        length += 2 + ptrvec[i]->getLength();
    }
}

ASNSequence::ASNSequence()
{
    tag = 16;
    isConstructed = 1;
    isIndefinite = 0;
    length = 0;
}

ASNSequence::ASNSequence(vector<shared_ptr<ASNObject>>& ptrvec)
{
    tag = 16;
    isConstructed = 1;
    isIndefinite = 0;
    setLength(ptrvec);
    for_each(ptrvec.begin(), ptrvec.end(), [&](shared_ptr<ASNObject> &ptr)->void { objects.push_back(move(ptr)); });
    serialize();
}

void ASNSequence::serialize()
{
    data = taglength(tag, length, isConstructed, isIndefinite);
    for(unsigned i=0; i<objects.size(); i++)
    {
        vector<char> temp = objects[i]->getData();
        data.insert(data.end(), temp.begin(), temp.end());
    }
}


void ASNSequence::readTags(const vector<char> &code, int& tag, int& length)
{
    if(any_of(code.begin(), code.end(), [](char i){ return (i!='0' && i!='1'); } ))
        throw argument_error("Unrecognised character");
    if(code[0]!='0' || code[1]!='0') throw argument_error("Only types native to ASN.1 accepted");

    bitset<5> bintag;
    for(int i=3, j=4; i<8; i++, j--)
        bintag.set(j, code[i]-'0');
    tag = bintag.to_ulong();

    bitset<7> binlength;
    for(int i=9, j=6; i<16; i++, j--)
        binlength.set(j, code[i]-'0');
    length = binlength.to_ulong();
}

void ASNSequence::deserialize(const vector<char>& buffer)
{
    if(buffer.size()<16) throw unexpected_end("ASN.1 Sequence error: input ends unexpectedly");
    int initialLength = length;

    vector<char> initialOctets(buffer.begin(), buffer.begin()+16);
    taglength(initialOctets);
    if(!isConstructed) {
        length = initialLength;
        isConstructed = 1;
        isIndefinite = 0;
        throw argument_error("ASN.1 Sequence must be constructed");
    }
    if(isIndefinite) {
        length = initialLength;
        isConstructed = 1;
        isIndefinite = 0;
        throw argument_error("ASN.1 Sequence must be of definite length");
    }
    if(buffer.size()!=16+8*(unsigned)length)
    {
        length = initialLength;
        isConstructed = 1;
        isIndefinite = 0;
        throw unexpected_end("ASN.1 Sequence error: wrong input size");
    }

    objects.clear();
    data = vector<char>(initialOctets.begin(), initialOctets.end());

    vector<char>::const_iterator it = buffer.begin()+16;
    vector<char> temp;
    int newTag, newLength;
    while (it<buffer.end())
    {
        temp = vector<char>(it, it+16);
        readTags(temp, newTag, newLength);
        temp = vector<char>(it, it+16+8*newLength);
        switch (newTag)
        {
            case 2:
            {
                shared_ptr<ASNObject> objptr(new ASNInteger);
                objptr->deserialize(temp);
                objects.push_back(move(objptr));
                break;
            }
            case 10:
            {
                shared_ptr<ASNObject> objptr(new ASNEnumerated);
                objptr->deserialize(temp);
                objects.push_back(move(objptr));
                break;
            }
            case 12:
            {
                shared_ptr<ASNObject> objptr(new ASNUTF8String(string("")));
                objptr->deserialize(temp);
                objects.push_back(move(objptr));
                break;
            }
            case 3:
            {
                shared_ptr<ASNObject> objptr(new ASNBitstring(string("")));
                objptr->deserialize(temp);
                objects.push_back(move(objptr));
                break;
            }
            default:
            {
                throw argument_error("Unsupported data type. Only INTEGER, ENUMERATED, UTF8String and Bitstring accepted.");
                break;
            }
        }
        data.insert(data.end(), temp.begin(), temp.end());
        advance(it, 16+8*newLength);
    }
}
