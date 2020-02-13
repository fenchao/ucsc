//
//  nqueens.cpp
//  nqueens
//
//  Created by Fenchao Du on 2/5/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#include "nqueens.h"

Nqueens::Nqueens(int nqueens) {
    this->nqueens = nqueens;
    board = new int[nqueens]();
    solution = 0;
}

Nqueens::~Nqueens() {
    delete[] board;
}

void Nqueens::set(int nqueens) {
    if (this->nqueens != nqueens) {
        this->nqueens = nqueens;
        delete[] board;
        board = new int[nqueens]();
    }
}

void Nqueens::solve() {
    int row = 0, col = 0;
    
    while(board[0] < nqueens) {
        if (col == nqueens) {
            /* full row - backtrack */
            board[--row]++;
            col = board[row];
            continue;
        }
        
        if (checkMove(row, col)) {
            board[row] = col;
            if (row + 1 == nqueens) {
                /* found a solution */
                solution++;
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
    cout << solution << " total solutions for " << nqueens << " queens." << endl;
    
Reset:
    board[0] = 0;
    solution = 0;
}

bool Nqueens::checkMove (int row, int col) {
    int old_row = 0, old_col = 0;
    
    // check col
    for (old_row = 0; old_row < row; old_row++) {
        if (board[old_row] == col) {
            return false;
        }
    }
    
    // check diag
    for (old_row = 0; old_row < row; old_row++) {
        old_col = board[old_row];
        if (row - old_row == col - old_col || row - old_row == old_col - col) {
            return false;
        }
    }
    
    return true;
}

void Nqueens::printBoard() {
    cout << endl;
    for (int row = 0; row < nqueens; row++) {
        for (int col = 0; col < nqueens; col++) {
            if (col == board[row]) {
                cout << "Q";
            } else {
                cout << "-";
            }
        }
        cout << endl;
    }
}
