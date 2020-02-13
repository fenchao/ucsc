/*----------------------------------------------------------------
Copyright (c) 2018 Author: Jagadeesh Vasudevamurthy
file: luhn.cpp
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
This file has luhn class definition
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
All includes here
-----------------------------------------------------------------*/
#include "luhn.h"

/*----------------------------------------------------------------
Write all code below
-----------------------------------------------------------------*/
bool luhn::check(long long num) {
    bool even = false;
    int sum = 0;
    while(num) {
        if (even) {
            int step1 = num % 10 * 2;
            int step2 = step1/10 + step1%10;
            sum += step2;
        } else {
            int step3 = num % 10;
            sum += step3;
        }
        num /= 10;
        even ^= true;
    }
    if (sum % 10 == 0) {
        return true;
    } else {
        return false;
    }
}


