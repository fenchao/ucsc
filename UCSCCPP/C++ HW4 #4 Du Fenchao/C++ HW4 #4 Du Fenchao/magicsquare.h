//
//  magicsquare.hpp
//  magicsquare
//
//  Created by Fenchao Du on 2/5/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#ifndef magicsquare_h
#define magicsquare_h

#include "../util/util.h"

class Magicsquare {
public:
    void run(int num);
private:
    int getDigits(int num);
    int checkSum(int** table, int num);
};

#endif /* magicsquare_h */
