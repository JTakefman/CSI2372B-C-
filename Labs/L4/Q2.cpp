/*
300171459
Jordan Takefman
*/
#include <iostream>
#include <stdlib.h>

using namespace std;

class SetInt
{
public:
    SetInt() : elem(NULL), size(0) {};
    SetInt(int arr[], int in_size) {
        size=in_size;
        elem = new int[size];
        for (int i = 0; i < size; i++) {
            elem[i]=arr[i];
        }
    };
    ~SetInt(){delete[] elem;}
    SetInt(const SetInt& in) {
        size = in.size;
        elem = in.tabElem();
    }; // copy constructor
    void add(int in) {
        if (contains(in)) {
            cout << "Element " << in << " contained in set" << endl;
            return;
        }
        size++;
        int *temp = new int[size];
        for (int i = 0; i < size; i++) {
            if (i == size-1) {
                temp[i]=in;
            }
            else {
                temp[i]=elem[i];
            }
        }
        delete[] elem;
        elem = temp;

    };

    void remove(int in) {
        if (!contains(in)) {
            cout << "Integer " << in << " not found for removal" << endl;
            return;
        }
        size--;
        int *temp = new int[size];
        int j = 0;
        for (int i = 0; i < size+1; i++) {
            if (elem[i] != in) {
                temp[j]=elem[i];
                j++;
            }
        }
        delete[] elem;
        elem = temp;
    }
    bool contains(int in) {
        for (int i = 0; i < size; i++) {
            if (elem[i] == in) {
                return true;
            }
        }
        return false;
    }
    int nbElem() {
        return size;
    }
    int *tabElem() const {
        int *ret = new int[size];
        for (int i = 0; i < size; i++) {
            ret[i]=elem[i];
        }
        return ret;
    }

    void printSet() {
        if (size ==0) {
            cout << "Set is empty";
        }
        for(int i = 0; i < size; i++) {
            cout << elem[i] << ", ";
        }
        cout << endl;
    }

private:
    int *elem;
    int size;
    bool containsAux(int n, int at) {
        if (elem[at]==n) {
            return true;
        }
        return false;
    }
};

int main() {
    SetInt test;
    test.add(5);
    test.add(4);
    test.add(3);
    test.add(7);
    test.printSet();
    test.add(3);
    test.printSet();
    test.remove(12);
    test.remove(5);
    test.printSet();
    cout << test.nbElem() << endl;
    cout << "List contains 4? " << test.contains(4) << endl;
    int *testarr = test.tabElem();
    cout << "Printing returned testarr" << endl;
    for (int i = 0; i < test.nbElem(); i++) {
        cout << testarr[i] << ", ";
    }
    cout << endl;
    delete[] testarr;
    SetInt test2(test);
    cout << "Copied test " << endl;
    test2.printSet();
    return 0;
}