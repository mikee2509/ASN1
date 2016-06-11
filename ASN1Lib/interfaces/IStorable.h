#ifndef ISTORABLE_H
#define ISTORABLE_H
#include <fstream>
#include "../ASNObject.h"

//! Base class for ASNObject interface classes providing save-in-file methodes
class IStorable : virtual public ASNObject
{
public:
    virtual ~IStorable() {}
    virtual void saveData(const std::string &filename); //!< Saves binary data in a file
    virtual void saveHex(const std::string &filename); //!< Saves data in hexadecimal format in a file
};

#endif // ISTORABLE_H
