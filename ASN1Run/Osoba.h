#ifndef OSOBA_H
#define OSOBA_H

#include "main.h"
//! Class holding information about a single person
class Osoba : public IASNSequence
{
public:
    //! Standard constructor
    /*! Creates new object with appropriate attributes
        \param name : string with person's name
        \param surname : string with person's surname
        \param age : person's age
        \param gender : *1* for male, *0* for female
        \param interests : string of 4 bits giving information about chosen hobbies */
    Osoba(std::string name, std::string surname, int age, bool gender, std::string interests);
    void wyswietl(); //!< Prints person's information
};


//! Exception for invalid choice of interests in Osoba class
class interests_error : public std::runtime_error
{
public:
    interests_error(const char* what_arg): runtime_error(what_arg) {};
};

#endif // OSOBA_H
