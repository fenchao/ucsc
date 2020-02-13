/*----------------------------------------------------------------
Copyleft (c) 2014 Author: Jagadeesh Vasudevamurthy
file: Array.cpp
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
This file has Array class definition 
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
All includes here
-----------------------------------------------------------------*/
#include "array.h"

/*----------------------------------------------------------------
Definition of routines of Array class
-----------------------------------------------------------------*/
void Array::copy(char* s, const char* t) {
    int i = 0;
    while (t[i]) {
        s[i] = t[i];
        i++;
    }
    s[i] = '\0';
}

void Array::reverse(char *s) {
    int size = 0;
    while (s[size]) {
        size++;
    }
    for (int i = 0; i < size/2; i++) {
        s[i] ^= s[size-i-1];
        s[size-i-1] ^= s[i];
        s[i] ^= s[size-i-1];
    }
}

void Array::p(const char* str, char* s) {
    cout << str << s << endl;
}

void Array::p(const char* str, int* s, int size) {
    cout << str;
    for(int i = 0; i < size; i++) {
        cout << s[i] << " ";
    }
    cout << endl;
}

int Array::string2number(const char* s) {
    int i = 0;
    do {
        if(!isdigit(s[i])) {
            return 0;
        }
        i++;
    } while(s[i]);
    return stoi(s);
}

int Array::removedups(int* s, int l) {
    int i, j, k = 0;
    for (i = 0; i < l; i++) {
        for (j = 0; j < k; j++) {
            // check if dup and skip
            if (s[j] == s[i]) {
                break;
            }
        }
        if (j == k) {
            s[k++] = s[i];
        }
    }
    return k;
}

/*----------------------------------------------------------------
Write all code in this file
-----------------------------------------------------------------*/

//EOF
