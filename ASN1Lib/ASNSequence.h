#ifndef ASNSEQUENCE_H
#define ASNSEQUENCE_H

#include "ASNObject.h"
#include "ASNInteger.h"
#include "ASNUTF8String.h"
#include "ASNBitstring.h"
#include "ASNEnumerated.h"
#include "ASNIntEnum.h"
#include "ASNSequence.h"

class ASNSequence : virtual public ASNObject
{
protected:
    std::vector<std::shared_ptr<ASNObject>> objects;

    void setLength(std::vector<std::shared_ptr<ASNObject>> &ptrvec);
    void readTags(const std::vector<char> &code, int &tag, int &length);
public:
    virtual ~ASNSequence() {}
    ASNSequence();
    ASNSequence(std::vector<std::shared_ptr<ASNObject>> &ptrvec);

    virtual void serialize();
    virtual void deserialize(const std::vector<char> &buffer);

    void push_back(std::shared_ptr<ASNObject> &pushptr);
    std::vector<std::shared_ptr<ASNObject>>& getObjects() { return objects; }
};

#endif // ASNSEQUENCE_H
