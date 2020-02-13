//
//  nqueens.hpp
//  nqueens
//
//  Created by Fenchao Du on 2/5/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#ifndef nqueens_h
#define nqueens_h

#include "../util/util.h"

class nqueens {
public:
    nqueens (int nqueens = 8);
    ~nqueens();
    void set(int nqueens);
    void solve();
private:
    int _nqueens;
    int* _board;
    int _solution;
    bool checkMove (int row, int col);
    void printBoard();
};

#endif /* nqueens_h */
