//
//  nqueens.cpp
//  nqueens
//
//  Created by Fenchao Du on 2/5/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#include "nqueens.h"

nqueens::nqueens(int nqueens) : _nqueens(nqueens),_solution(0) {
    _board = new int[nqueens]();
}

nqueens::~nqueens() {
    delete[] _board;
}

void nqueens::set(int nqueens) {
    if (_nqueens != nqueens) {
        _nqueens = nqueens;
        delete[] _board;
        _board = new int[nqueens]();
    }
}

void nqueens::solve() {
    int row = 0, col = 0;
    
    while(_board[0] < _nqueens) {
        if (col == _nqueens) {
            /* full row - backtrack */
            _board[--row]++;
            col = _board[row];
            continue;
        }
        
        if (checkMove(row, col)) {
            _board[row] = col;
            if (row + 1 == _nqueens) {
                /* found a _solution */
                _solution++;
                printBoard();
                col++;
            } else {
                /* next row */
                row++;
                col = 0;
            }
        } else {
            /* next col */
            col++;
        }
    }
    cout << _solution << " total _solutions for " << _nqueens << " queens." << endl;
    
Reset:
    _board[0] = 0;
    _solution = 0;
}

bool nqueens::checkMove (int row, int col) {
    int old_row = 0, old_col = 0;
    
    // check col
    for (old_row = 0; old_row < row; old_row++) {
        if (_board[old_row] == col) {
            return false;
        }
    }
    
    // check diag
    for (old_row = 0; old_row < row; old_row++) {
        old_col = _board[old_row];
        if (row - old_row == col - old_col || row - old_row == old_col - col) {
            return false;
        }
    }
    
    return true;
}

void nqueens::printBoard() {
    cout << endl;
    for (int row = 0; row < _nqueens; row++) {
        for (int col = 0; col < _nqueens; col++) {
            if (col == _board[row]) {
                cout << "Q";
            } else {
                cout << "-";
            }
        }
        cout << endl;
    }
}
