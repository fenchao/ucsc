//
//  intmatrix1.cpp
//  intmatrix1
//
//  Created by Fenchao Du on 2/12/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#include "intmatrix1.h"

void intmatrix1::init(){}

void intmatrix1::init(int row, int col, int val) {
    if (row && col) {
        _row = row;
        _col = col;
        _setw = _getDigits(val) + 1;
        _mat = new int*[row];
        for (int i = 0; i < row; ++i) {
            _mat[i] = new int[col];
            for (int j = 0; j < col; ++j) {
                _mat[i][j] = val;
            }
        }
    }
}

void intmatrix1::init(const char *initString) {
    int tmp_setw = 0;
    if(_getMatParam(initString, _row, _col)) {
        _mat = new int*[_row];
        for (int i = 0; i < _row; ++i) {
            _mat[i] = new int[_col];
            for (int j = 0; j < _col; ++j) {
                _mat[i][j] = _getNextInt(initString);
                tmp_setw = _getDigits(_mat[i][j]) + 1;
                _setw = max(tmp_setw, _setw);
            }
        }
    }
}

void intmatrix1::print(const char* printString) {
    cout << "--------" << printString << "--------" << endl;
    if (_mat) {
        for (int i = 0; i < _row; ++i) {
            for (int j = 0; j < _col; ++j) {
                cout << setw(_setw) << _mat[i][j];
            }
            cout << endl;
        }
    } else {
        cout << "Empty Matrix" << endl;
    }
}

void intmatrix1::fini() {
    if (_mat) {
        for (int i = 0; i < _row; ++i) {
            delete[] _mat[i];
        }
        delete[] _mat;
        _mat = nullptr;
    }
}

bool intmatrix1::isEmpty() {
    return !_mat;
}

bool intmatrix1::isEqual(intmatrix1 &mat) {
    if (!_mat && !(mat._mat)) {
        return true;
    }
    if (!_mat || !(mat._mat) || _row != mat._row || _col != mat._col) {
        return false;
    }
    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < _col; ++j) {
            if (_mat[i][j] != mat._mat[i][j]) {
                return false;
            }
        }
    }
    return true;
}

intmatrix1 intmatrix1::add(intmatrix1 &mat) {
    intmatrix1 ret;
    int i, j, tmp_setw;
    if (_mat && mat._mat && _row == mat._row && _col == mat._col) {
        ret.init(_row, _col);
        for (i = 0; i < _row; ++i) {
            for (j = 0; j < _col; ++j) {
                ret._mat[i][j] = _mat[i][j] + mat._mat[i][j];
                tmp_setw = _getDigits(ret._mat[i][j]) + 1;
                ret._setw = max(tmp_setw, ret._setw);
            }
        }
    }
    return ret;
}

intmatrix1 intmatrix1::mult(intmatrix1 &mat) {
    intmatrix1 ret;
    int i, j, k, tmp_setw;
    if (_mat && mat._mat && _col == mat._row) {
        ret.init(_row, mat._col);
        for (i = 0; i < _row; ++i) {
            for (j = 0; j < mat._col; ++j) {
                for(k = 0; k < _col; ++k) {
                    ret._mat[i][j] += _mat[i][k] * mat._mat[k][j];
                }
                tmp_setw = _getDigits(ret._mat[i][j]) + 1;
                ret._setw = max(tmp_setw, ret._setw);
            }
        }
    }
    return ret;
}

/*
 * @initString: Input string param for init()
 * @row: Row size for matrix
 * @col: Col size for matrix
 * @return true if we can create non-empty matrix
 */
bool intmatrix1::_getMatParam(const char* initString, int& row, int& col) {
    int pos = 0;
    int colPerRow = 0;
    row = 0;
    col = 0;
    
    while(initString[pos]) {
        if (!isdigit(initString[pos])
            && initString[pos] != '|'
            && initString[pos] != ' ') {
            return false;
        }
        if (isdigit(initString[pos]) && !isdigit(initString[pos+1])) {
            col++;
        }
        if (initString[pos] == '|') {
            if (!col) {
                return false;
            }
            if (!row) {
                colPerRow = col;
            } else if (col != colPerRow) {
                return false;
            }
            row++;
            col = 0;
        }
        pos++;
    }
    
    row++;
    return (col && (row == 1 || col == colPerRow));
}

/*
 * @initString: Input string param for init()
 * @begin: String position to read integer
 * @return next integer value
 */
int intmatrix1::_getNextInt(const char*& initString) {
    char buffer[12];
    int pos = 0;
    
    while(*initString && !isdigit(*initString)) {initString++;}
    
    while(*initString && isdigit(*initString)) {
        buffer[pos++] = *(initString++);
    }
    
    buffer[pos] = '\0';
    return stoi(buffer);
}

int intmatrix1::_getDigits(int val) {
    int digits = 0;
    do {
        digits++;
        val /= 10;
    } while (val);
    return digits;
}
