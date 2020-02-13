//
//  iset64.hpp
//  iset64
//
//  Created by Fenchao Du on 3/3/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#ifndef iset64_h
#define iset64_h

#include "../util/util.h"

class iset64 {
private:
    u_int64_t _bits;
public:
    iset64():_bits(0) {}
    iset64(const int n):_bits(u_int64_t(1)<<n) {}
    iset64(const int* arr, int size):_bits(0) {for(int i=0;i<size;++i) _bits|=u_int64_t(1)<<arr[i];}
    iset64(const iset64& set):_bits(set._bits) {}

    iset64& operator= (const iset64& set) {_bits=set._bits; return *this;}
    friend ostream& operator<< (ostream& o, const iset64& set);

    friend iset64 operator+ (const iset64& seta, const iset64& setb) {iset64 ret(seta); ret._bits|=setb._bits; return ret;}
    friend iset64 operator+ (const iset64& set, const int n) {return set+iset64(n);}
    friend iset64 operator+ (const int n, const iset64& set) {return set+n;}
    iset64& operator+= (const iset64& set) {_bits|=set._bits; return *this;}

    friend iset64 operator- (const iset64& seta, const iset64& setb) {iset64 ret(seta); ret._bits&=~setb._bits; return ret;}
    friend iset64 operator- (const iset64& set, const int n) {return set-iset64(n);}
    friend iset64 operator- (const int n, const iset64& set) {return iset64(n)-set;}
    iset64& operator-= (const iset64& set) {_bits&=~set._bits; return *this;}

    friend iset64 operator* (const iset64& seta, const iset64& setb) {iset64 ret(seta); ret._bits&=setb._bits; return ret;}
    friend iset64 operator* (const iset64& set, const int n) {return set*iset64(n);}
    friend iset64 operator* (const int n, const iset64& set) {return set*n;}
    iset64& operator*= (const iset64& set) {_bits&=set._bits; return *this;}

    friend bool operator== (const iset64& seta, const iset64& setb) {return seta._bits==setb._bits;}
    friend bool operator!= (const iset64& seta, const iset64& setb) {return seta._bits!=setb._bits;}

    iset64& operator++() {_bits=_bits<<1|_bits>>63; return *this;}
    iset64 operator++(int j) {iset64 ret(*this); ++(*this); return ret;}

    iset64& operator--() {_bits=_bits>>1|_bits<<63; return *this;}
    iset64 operator--(int j) {iset64 ret(*this); --(*this); return ret;}

    iset64 operator~ () const {iset64 ret; ret._bits=~_bits; return ret;}

    operator bool() const {return _bits;}
    bool operator!() const {return !_bits;}
};

#endif /* iset64_h */
