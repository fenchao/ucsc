//
//  magicsquare.cpp
//  magicsquare
//
//  Created by Fenchao Du on 2/5/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#include "magicsquare.h"

int Magicsquare::getDigits(int num) {
    int digits = 0;
    while (num) {
        digits++;
        num /= 10;
    }
    return digits;
}

int Magicsquare::checkSum(int** table, int num) {
    int row = 0, col = 0, sum = 0, cur_sum = 0;

    //diag
    for (row = 0, col = 0; row < num; row++, col++) {
        sum += table[row][col];
    }
    for (row = 0, col = num-1; row < num; row++, col--) {
        cur_sum += table[row][col];
    }
    if (sum != cur_sum) {
        cout << "Checksum failure. Diagonals have different sum!" << endl;
        return 0;
    }

    //row
    for (row = 0; row < num; row++) {
        cur_sum = 0;
        for (col = 0; col < num; col++) {
            cur_sum += table[row][col];
        }
        if (sum != cur_sum) {
            cout << "Checksum failure. Row " << row << " has different sum!" << endl;
            return 0;
        }
    }
    
    //col
    for (col = 0; col < num; col++) {
        cur_sum = 0;
        for (row = 0; row < num; row++) {
            cur_sum += table[row][col];
        }
        if (sum != cur_sum) {
            cout << "Checksum failure. Col " << col << " has different sum!" << endl;
            return 0;
        }
    }
    
    return sum;
}

void Magicsquare::run(int num) {
    /* Ensure input is odd number */
    if (num < 0 || num/2 == num - num/2) {
        cout << "Invalid n = " << num << ". Works for only odd number." << endl;
        return;
    }
    
    /* Init variable and magic square table */
    int nsquare = num * num;
    int row = 0, col = 0;
    int** table = new int* [num]();
    for (row = 0; row < num; row++) {
        table[row] = new int[num]();
    }
    
    /* Fill magic square table */
    row = 0;
    col = num/2;
    for (int i = 1; i <= nsquare; i++) {
        table[row][col] = i;
        row = (row-1+num)%num;
        col = (col-1+num)%num;
        if (table[row][col]) {
            row = (row+2)%num;
            col = (col+1)%num;
        }
    }
    
    /* Display magic square table */
    {
        int digits = getDigits(nsquare);
        cout << "Magicsquare for n = " << num << endl;
        for (row = 0; row < num; row++) {
            for (col = 0; col < num; col++) {
                cout << setw(digits+1) << table[row][col];
            }
            cout << endl;
        }
    }
    
    /* All row, col, diag have same sum */
    if (int sum = checkSum(table, num)) {
        cout << "All row, col, diag have same sum " << sum << endl;
    }
    

Cleanup:
    /* Free allocated memory */
    for (row = 0; row < num; row++) {
        if (table[row]) {
            delete table[row];
            table[row] = nullptr;
        }
    }
    delete[] table;
}
