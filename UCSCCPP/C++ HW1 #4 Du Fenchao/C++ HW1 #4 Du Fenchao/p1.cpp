//
//  p1.cpp
//  p1
//
//  Created by Fenchao Du on 1/12/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#include "p1.h"

void p1::print_usa() {
    cout << __FUNCTION__ << endl;
    cout <<
    "XXX   XXX  XXXX X   XXX\n"
    " X     X  X    XX     X\n"
    " X     X  X     X    X X\n"
    " X     X  X          X X\n"
    " X     X   XXX      X   X\n"
    " X     X      XX    X   X\n"
    " X     X        X   XXXXX\n"
    " X     X  X     X  X     X\n"
    " XX   XX  XX    X  X     X\n"
    "   XXX    X XXXX  XXX   XXX"
    << endl;
}

void p1::print_n_n2_n3() {
    cout << __FUNCTION__ << endl;
    cout << "n  n^2  n^3" << endl;
    for (int n = 1; n <= 9; n++) {
        cout
        << n
        << setw(5) << setfill(' ') << (n * n)
        << setw(5) << setfill(' ') << (n * n * n)
        << endl;
    }
}

void p1::a_power_b() {
    cout << __FUNCTION__ << endl;
    cout << "a  b       a^b" << endl;
    for (int a = 1; a <= 7; a++) {
        int b = a + 1;
        int pow = 1;
        cout << a << "  " << b;
        while (b-- > 0) {
            pow *= a;
        }
        cout << setw(10) << setfill(' ') << pow << endl;
    }
}

void p1::two_power_n() {
    cout << __FUNCTION__ << endl;
    cout << "n       2^n" << endl;
    for (int n = 0, pow = 1; n <= 20; n++, pow *= 2) {
        cout << n << setw(10) << setfill(' ') << pow << endl;
    }
}

void p1::a1() {
    cout << __FUNCTION__ << endl;
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= i; j++) {
            cout << " " << j;
        }
        cout << endl;
    }
}

void p1::a2() {
    cout << __FUNCTION__ << endl;
    for (int i = 1; i <= 6; i++) {
        int j;
        for (j = 6; j > i; j--) {
            cout << "  ";
        }
        do {
            cout << " " << j;
        } while (j-- > 1);
        cout << endl;
    }
}

void p1::a3() {
    cout << __FUNCTION__ << endl;
    for (int i = 6; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            cout << " " << j;
        }
        cout << endl;
    }
}

void p1::a4() {
    cout << __FUNCTION__ << endl;
    for (int i = 6; i >= 1; i--) {
        int j;
        for (j = 6; j > i; j--) {
            cout << "  ";
        }
        for (j = 1; j <= i; j++) {
            cout << " " << j;
        }
        cout << endl;
    }
}

