#ifndef OSOBA_H
#define OSOBA_H

#include "main.h"

class Osoba : public IASNSequence
{
public:
    Osoba(std::string name, std::string surname, int age, bool gender, std::string interests);
    void wyswietl();
};



class interests_error : public std::runtime_error
{
public:
    interests_error(const char* what_arg): runtime_error(what_arg) {};
};

#endif // OSOBA_H
