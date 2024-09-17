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