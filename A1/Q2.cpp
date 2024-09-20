#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int a=0,b=0;
    cout << "Input a: ";
    cin >> a;
    cout << endl;
    cout << "Input b: ";
    cin >> b;
    cout << endl;
    cout << "(a+b)^2 = " << pow(a+b, 2) << endl << endl;
    cout << "(a-b)^2 = " << pow(a-b, 2) << endl << endl;
}