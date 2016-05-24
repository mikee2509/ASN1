#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

class Student
{
public:
    Student(int nn);
    int getNo() { return no; }
private:
    int no;
};

#endif // STUDENT_H
