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

class Nqueens {
public:
    Nqueens (int nqueens = 8);
    ~Nqueens();
    void set(int nqueens);
    void solve();
private:
    int nqueens;
    int* board;
    int solution;
    bool checkMove (int row, int col);
    void printBoard();
};

#endif /* nqueens_h */
