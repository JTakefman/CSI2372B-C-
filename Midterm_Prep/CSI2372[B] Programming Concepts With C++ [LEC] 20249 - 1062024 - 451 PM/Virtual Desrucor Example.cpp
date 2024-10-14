// CSI2372 example Code
// Lecture 02 and Lecture 04
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
/*
What is a Virtual Destructor? A virtual destructor in C++ ensures that the correct destructor is called for an object when it is deleted through a pointer to the base class, especially in the case of inheritance and polymorphism.

Why Use a Virtual Destructor?
    - When a derived class object is deleted through a base class pointer, the base class destructor is called if the destructor is not virtual. This can lead to a situation where the resources of the derived class are not properly released, causing memory leaks or undefined behavior.
    - Declaring the destructor as virtual ensures that the derived class's destructor is invoked first, followed by the base class destructor. This is necessary to ensure proper cleanup of resources, especially in the context of dynamic memory management.
*/

// Syntax of a Virtual Destructor:
class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor called" << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Derived destructor called" << std::endl;
    }
};

//Example:
#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base constructor called" << std::endl;
    }

    // Virtual destructor
    virtual ~Base() {
        std::cout << "Base destructor called" << std::endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived constructor called" << std::endl;
    }

    ~Derived() {
        std::cout << "Derived destructor called" << std::endl;
    }
};

int main() {
    Base* obj = new Derived();  // Base pointer pointing to Derived object
    delete obj;  // Correctly calls both Derived and Base destructors

    return 0;
}
/* Output:
Base constructor called
Derived constructor called
Derived destructor called
Base destructor called
*/

// Q: What if I create a non pointer like this: Base obj = Derived(); instead Base* obj = new Derived();
// A: (1) It eleminates the polymorphism concept (no pointer), (2) Object slicing occurs here where the second part of the assignment will be ignored (3) The new keyword dynamically allocates memory for the object on the heap. This allows the object to persist beyond the scope of the current function, giving more control over its lifetime.