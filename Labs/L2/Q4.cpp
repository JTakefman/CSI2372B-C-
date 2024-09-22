/*
300171459
Jordan Takefman

Notes for Corector:
I interpreted this question to mean that each child with higher rating needed to have
a total amount of candy greater than it's immmediate neighbours with no regard for
how the child ranked globally.
*/
#include <iostream>
#include <vector>
using namespace std;

int minCandies(int arr_r[], int size) {
    int min_candies = 0;
    int arr_length = size;
    int arr_c[arr_length];  //Array of candies
    //First assign all candies to one
    
    for (int i = 0; i < arr_length; i++) {
        arr_c[i]=1;
    }
    cout << endl;
    //Compare each index to left neighbour and 
    //see if more candies are needed.
    int cand_max = 0;
    
    //Is each greater than left neighbour
    for (int i = 0; i < arr_length; i++) {
        if (arr_r[i+1] > arr_r[i]) {
            arr_c[i+1] = arr_c[i] + 1;
        }
    }

    //Is each greater than right neibhour

    for (int i = arr_length-2; i > -1; i--) {
        if (arr_r[i] > arr_r[i+1] && arr_c[i] <= arr_c[i+1]) {
            arr_r[i] = arr_c[i+1]+1;
        }
    }

    cout << "candy array: ";
    for (int i = 0; i < arr_length; i++) {
        cout << arr_c[i] << ", ";
        min_candies+= arr_c[i];
    }
    cout << endl;

    return min_candies;
}


int main() {
    int ratings[7] = {1,2,3,4,4,6,5};
    cout << "ratng array: ";
    for (int i = 0; i < 7; i++) {
        cout << ratings[i] << ", ";
    }
    int minCand = minCandies(ratings,7);
    cout << endl << minCand << endl;
}