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
using namespace std;

/*
Questions for TA:
    Do we need to account for edge cases, do exception handling.
    Is it ok to read across multiple ines
    Do we really need to use an array
*/

int main() {
    int largest = 0;
    int temp = 0;
    int n = 0;
    bool brk = false;
    while (!brk) {
        cout << "Input an integer" << endl;
        cin >> temp;
        if (temp > largest) {
            largest=temp;
        }
        else if (temp < 0) {
            brk=true;
        }
    }
    cout << "Largest is " << largest << endl;

}