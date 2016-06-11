#ifndef ASNSEQUENCE_H
#define ASNSEQUENCE_H

#include "ASNObject.h"
#include "ASNInteger.h"
#include "ASNUTF8String.h"
#include "ASNBitstring.h"
#include "ASNEnumerated.h"
#include "ASNIntEnum.h"
#include "ASNSequence.h"

//! ASN.1 Sequence data structure
class ASNSequence : virtual public ASNObject
{
protected:
    std::vector<std::shared_ptr<ASNObject>> objects; //!< Vector of pointers to objects held in ASNSequence

    /*! Calculates the number of octets needed to store the objects held by pointes in *ptrvec*. */
    void setLength(std::vector<std::shared_ptr<ASNObject>> &ptrvec);

    /*! Reads the data structure's initial octets passed by *code* and saves the values in *tag* and *length*. */
    void readTags(const std::vector<char> &code, int &tag, int &length);
public:
    virtual ~ASNSequence() {}
    ASNSequence(); //!< Constructs an empty ASNSequence object

    //! Standard constructor
    /*! Creates new object with appropriate length
        \param ptrvec : vector of pointers to objects to be held in ASNSequence */
    ASNSequence(std::vector<std::shared_ptr<ASNObject>> &ptrvec);

    virtual void serialize();
    virtual void deserialize(const std::vector<char> &buffer);

    void push_back(std::shared_ptr<ASNObject> &pushptr); //!< Add new pointer to ASNObject at the end of *objects* vector
    std::vector<std::shared_ptr<ASNObject>>& getObjects() { return objects; } //!< Returns vector of pointers to objects held in ASNSequence
};

#endif // ASNSEQUENCE_H
