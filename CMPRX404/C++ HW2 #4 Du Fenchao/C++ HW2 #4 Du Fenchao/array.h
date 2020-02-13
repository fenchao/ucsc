/*----------------------------------------------------------------
Copyright (c) 2018 Author: Jagadeesh Vasudevamurthy
file: Array.h
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
This file has Array class declaration 
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
All includes here
-----------------------------------------------------------------*/
#ifndef array_H
#define array_H

#include "../util/util.h"

/*----------------------------------------------------------------
Declaration of Array class
Write code below
-----------------------------------------------------------------*/
class Array {
public:
    void copy(char* s, const char* t);
    void p(const char* str, char* s);
    void p(const char* str, int* s, int size);
    void reverse(char* s);
    int string2number(const char* s);
    int removedups(int* s, int l);
private:
};

#endif
//EOF
