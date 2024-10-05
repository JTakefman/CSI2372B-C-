/*
300171459
Jordan Takefman
*/
#include <iostream>
using namespace std;

int main() {

    /*
    The key insight to solving this problem is recognizing that the max water a given index
    can store is bounded by the smaller of the maximum heights to the right and left of said index. Thus
    if we iterate through the array and continually update the maximum left and right heights bounding,
    we can determine the maximum amount of water. 
    */
    int size = 7;
    int arr[size] = {0,3,2,5,1,4,6};

    int max_l = arr[0];
    int max_r = arr[size-1];

    int total = 0;
    int l = 1;
    int r = size-2;

    while (l <= r) {
        if (max_l < max_r) {
            total += max(0, max_l-arr[l]);
            max_l = max(max_l, arr[l]);
            l +=1;
        }
        else {
            total += max(0, max_r-arr[r]);
            max_r = max(max_r, arr[r]);
            r -=1;
        }
    }

    cout << "max is " << total << endl;

    return 0;
}