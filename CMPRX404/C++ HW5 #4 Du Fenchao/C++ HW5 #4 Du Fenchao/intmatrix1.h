//
//  intmatrix1.hpp
//  intmatrix1
//
//  Created by Fenchao Du on 2/12/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#ifndef intmatrix1_h
#define intmatrix1_h

#include "../util/util.h"

class intmatrix1 {
public:
    void init();
    void init(int row, int col, int val = 0);
    void init(const char* initString);
    void print(const char* printString);
    void fini();
    bool isEmpty();
    bool isEqual(intmatrix1& mat);
    intmatrix1 add(intmatrix1& mat);
    intmatrix1 mult(intmatrix1& mat);
private:
    int** _mat = nullptr;
    int _row = 0;
    int _col = 0;
    int _setw = 0;
    int _getNextInt(const char*& initString);
    bool _getMatParam(const char* initString, int& row, int& col);
    int _getDigits(int val);
};

#endif /* intmatrix1_h */
