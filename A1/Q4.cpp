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
    double running = 0;
    double temp = 0;
    double n = 0;
    bool brk = false;
    while (!brk) {
        cout << "Input an integer" << endl;
        cin >> temp;
        if (temp < 0) {
            brk=true;
        }
        else {
            running+=temp;
            n++;
        }
           
    }
    cout << "Average is " << running/n << endl;

}