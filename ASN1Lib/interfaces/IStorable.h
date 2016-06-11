#ifndef ISTORABLE_H
#define ISTORABLE_H
#include <fstream>
#include "../ASNObject.h"

class IStorable : virtual public ASNObject
{
public:
    virtual ~IStorable() {}
    virtual void saveData(const std::string &filename);
};

#endif // ISTORABLE_H
