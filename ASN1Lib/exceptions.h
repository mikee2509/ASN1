#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <stdexcept>

class unexpected_end : public std::runtime_error
{
public:
    unexpected_end(const char* what_arg): runtime_error(what_arg) {};
};

class argument_error : public std::runtime_error
{
public:
    argument_error(const char* what_arg): runtime_error(what_arg) {};
};
#endif // EXCEPTIONS_H
