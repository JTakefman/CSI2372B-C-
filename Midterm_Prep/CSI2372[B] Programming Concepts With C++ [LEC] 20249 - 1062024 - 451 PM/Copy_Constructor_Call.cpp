// CSI2372 example Code
// Extra Example about Copy Constructor call
// ==========================================================================
// (C)opyright:
//
//   Mohammad Alnabhan
//   SITE, University of Ottawa
//   800 King Edward Ave.
//   Ottawa, On., K1N 6N5
//   Canada. 
// 
// Creator: Malnabha (Mohammad Alnabhan)
// Email:   Malnabha@uottawa.ca
// ==========================================================================

#include <iostream>

class ClassA {
public:
    int* value;

    // Constructor
    ClassA(int v) {
        value = new int(v);
        std::cout << "ClassA Constructor called, value: " << *value << std::endl;
    }

    // Copy constructor (Deep Copy)
    ClassA(const ClassA& other) {
        value = new int(*other.value);
        std::cout << "ClassA Copy Constructor called, value: " << *value << std::endl;
    }

    // Destructor
    ~ClassA() {
        delete value;
        std::cout << "ClassA Destructor called" << std::endl;
    }
};

class ClassB {
public:
    int data;

    // Constructor
    ClassB(int d) : data(d) {
        std::cout << "ClassB Constructor called, data: " << data << std::endl;
    }

    // Copy constructor
    ClassB(const ClassB& other) {
        data = other.data;
        std::cout << "ClassB Copy Constructor called, data: " << data << std::endl;
    }

    // Destructor
    ~ClassB() {
        std::cout << "ClassB Destructor called" << std::endl;
    }
};

int main() {
    // Create objects using the parameterized constructor
    ClassA objA1(100);
    ClassB objB1(200);

    // Call the copy constructor for ClassA
    ClassA objA2 = objA1;  // Copying objA1 to objA2

    // Call the copy constructor for ClassB
    ClassB objB2 = objB1;  // Copying objB1 to objB2

    return 0;
}
