//
//  iset64.cpp
//  iset64
//
//  Created by Fenchao Du on 3/3/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#include "iset64.h"

ostream& operator<< (ostream& o, const iset64& set) {
    bool first = true;
    u_int64_t bits = set._bits;
    o << "{";
    for (int i = 0; bits; ++i) {
        if (bits & 1) {
            if (first) {
                first = false;
            } else {
                o << ",";
            }
            o << i;
        }
        bits >>= 1;
    }
    o << "}";
    return o;
}
