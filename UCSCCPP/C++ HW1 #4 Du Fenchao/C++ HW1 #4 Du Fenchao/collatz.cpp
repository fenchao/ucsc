//
//  collatz.cpp
//  collatz
//
//  Created by Fenchao Du on 1/12/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#include "collatz.h"

void collatz::conjecture(unsigned int n) {
    cout << "starting with n = " << n << ", one gets the sequence ";
    while(n != 1) {
        cout << n;
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        cout << ", ";
    }
    cout << "1." << endl;
}
