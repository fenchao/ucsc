//
//  main.cpp
//  magicsquare
//
//  Created by Fenchao Du on 2/5/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#include "magicsquare.h"

void testbed () {
    Magicsquare a;
    a.run(-5);
    a.run(10);
    a.run(3);
    a.run(5);
    a.run(11);
}

int main() {
    testbed ();
    return 0;
}
