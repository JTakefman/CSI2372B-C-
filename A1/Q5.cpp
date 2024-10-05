// ------------------------------------------------------------------------------
// Assignment 1
// Written by: Jordan Takefman, 300171459
// For CSI2372 Section B
// Time needed to complete this assignment
// List the resources used to complete this assignment
// -----------------------------------------------------------------------------

#include <iostream>
#include <cmath>
#include <string>
#include <ctype.h>
using namespace std;

/*
Questions for TA:
    Do we need to account for edge cases, do exception handling.
    Is it ok to read across multiple ines
    Do we really need to use an array
*/

long conversion(char* s) {
    long out = 0;
    int size = 0;
    bool neg = false;
    //I was told by the professor that error checking wasn't necessary
    //so the program simply assumes that if it encounters any non digit characters
    //other than '-' the string is done.
    for (int i = 0; i < 80; i++) {
        if (!isdigit(s[i])) {
            if (i==0 && s[i]=='-') {
                neg=true;
            }
            else {
                break;
            }
        }
        size++;
    }
    int j = 0;
    if (neg) {
        j = 1;
    }
    while(j < size) {
        int coef = (int)s[j] - 48;
        out += coef*pow(10.0, size-j-1);
        j++;
    }
    if (neg){
        return 0-out;
    }
    return out;
}

int main() {
    char str[80];
    cout << "Input a number: ";
    cin >> str;
    long conv = conversion(str);
    cout << "Converted long is: " << conv << endl;
}