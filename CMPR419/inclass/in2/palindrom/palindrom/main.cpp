//
//  main.cpp
//  palindrom
//
//  Created by Fenchao Du on 7/12/18.
//  Copyright © 2018 Fenchao Du. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(const string & str) {
    int i = 0, j = str.size()-1;
    while(i < j) {
        while(i < str.size() && (tolower(str[i]) < 'a' || tolower(str[i]) > 'z')) {
            ++i;
        }
        
        /* if no valid letter in string, we consider it's empty and a valid palindrome */
        if (i == str.size()) {
            return true;
        }
        
        /* if we reach here, there is at least one letter, j is always valid */
        while(tolower(str[j]) < 'a' || tolower(str[j]) > 'z') {
            --j;
        }
        
        if (tolower(str[i]) != tolower(str[j])) {
            return false;
        }
        
        ++i;
        --j;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    if (isPalindrome("jaNo!...devil....,..'....lived....onbj")) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    return 0;
}
