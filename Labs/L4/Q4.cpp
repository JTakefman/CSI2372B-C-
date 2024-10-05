/*
300171459
Jordan Takefman
*/
#include <iostream>
using namespace std;

int main() {
    int m = 5;
    int n = 3;
    int max[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                max[i][j]=1;
            }
            else if (j == 0) {
                max[i][j]=1;
            }
            else {
                max[i][j]=max[i-1][j] + max[i][j-1];
            }
        }
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++) {
            cout << max[i][j] << ", ";
        }
        cout << endl;
    }

    cout << "there are " << max[m-1][n-1] << " possible paths" << endl;
    return 1;
}