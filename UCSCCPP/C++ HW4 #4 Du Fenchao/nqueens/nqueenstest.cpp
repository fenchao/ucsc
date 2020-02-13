//
//  main.cpp
//  nqueens
//
//  Created by Fenchao Du on 2/5/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#include "nqueens.h"

void testbed () {
    nqueens nqueens(2);
    nqueens.solve();
    
    nqueens.set(4);
    nqueens.solve();
    
    nqueens.set(8);
    nqueens.solve();
}

int main() {
    testbed ();
    return 0;
}
