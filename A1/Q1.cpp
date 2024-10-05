// ------------------------------------------------------------------------------
// Assignment 1
// Written by: Jordan Takefman, 300171459
// For CSI2372 Section B
// Time needed to complete this assignment
// List the resources used to complete this assignment
// -----------------------------------------------------------------------------

#include <iostream>
using namespace std;

int read_number(void)
{
    int n;
    /* Read a number */
    cout << "Enter a number : ";
    cin >> n;
    return n;
}
int main()
{
    int i, n;
    long total = 0;
    n = read_number();
    for (i = 1; i <= n; i++)
    {
        total += i; /* accumulation in the variable « total » */
        cout << "i = " << i <<" total = " << total << endl;
    }
    cout << endl;
    cout << "*** Final Total = " << total << " *** \n" << total;
    return 1;
} /* end of main() */