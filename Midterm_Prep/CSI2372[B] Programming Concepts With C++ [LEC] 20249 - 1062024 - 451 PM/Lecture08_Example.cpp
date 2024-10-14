// CSI2372 Example Code
// Lecture08 
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
A friend function is a function that is not a member of a class but has the permission to access the private and protected members of the class. The purpose of a friend function is to allow certain external functions to access private or protected data, which is typically not accessible outside the class.

    - Access to Private Data: A friend function can access all the private and protected members of the class. This is useful when an external function needs to work closely with the internals of a class but should not be a member of that class.
    - Operator Overloading: Friend functions are often used for overloading operators when the left operand is not an object of the class (e.g., << and >> operators for std::ostream and std::istream).
    - Encapsulation and Access Control: They allow access to the private data without making the data public, preserving the encapsulation of the class.

Note1: Friendship is Not Inherited: If a function is a friend of a base class, it is not automatically a friend of derived classes.
Note2: Friendship is Not Transitive: If FunctionA is a friend of ClassA and FunctionB is a friend of FunctionA, FunctionB is not automatically a friend of ClassA.
Note3: Friendship is Granted, Not Taken: A class grants friendship to functions or other classes. It cannot make itself a friend of another class or function

*/

#include <iostream>

class Example {
private:
    int privateData;

public:
    Example(int val) : privateData(val) {}

    // Friend function declaration
    friend void displayPrivateData(const Example& obj);
};

// Definition of the friend function outside the class
void displayPrivateData(const Example& obj) {
    std::cout << "Private Data: " << obj.privateData << std::endl;  // Accesses privateData directly
}

int main() {
    Example ex(42);
    displayPrivateData(ex);  // Calls the friend function
    return 0;
}
// *******************************************************************************************************************************************
// A friend class gives all member functions of another class access to private members of the class.
#include <iostream>

class Stack {
private:
    int d_size;
    int d_capacity;
    std::string* d_stack;

public:
    // Constructor
    Stack(int capacity = 10) : d_capacity(capacity), d_size(0), d_stack(new std::string[capacity]) {}

    // Destructor
    ~Stack() {
        delete[] d_stack;
    }

    // Declare the entire class FriendStackInspector as a friend
    friend class FriendStackInspector;
};

// Friend class definition
class FriendStackInspector {
public:
    // This function can access private members of Stack because the entire class is a friend
    void inspectStack(const Stack& stack) {
        std::cout << "Inspecting stack. Size: " << stack.d_size << ", Capacity: " << stack.d_capacity << std::endl;
    }
};

int main() {
    Stack s(5);
    FriendStackInspector inspector;
    inspector.inspectStack(s);  // Accesses private members of Stack
    return 0;
}
// *************************************************************************************************************************************************
/* Quick Review:

(1)Polymorphism allows objects of different derived classes to be treated as objects of the base class.
This enables a base class handle (pointer or reference) to refer to objects of different derived classes and call functions that behave differently depending on the actual type of the object.
--- Example: Suppose we have different shapes like Circle, AABox, and OBBox, which all inherit from the base class Bounds. Each shape might implement its own version of a function (like enclose()) that processes bounding boxes differently.

(2)Virtual Functions allow derived classes to override base class functions. The key point is that dynamic binding happens at runtime: the correct function to call is determined based on the actual type of the object, not the type of the reference or pointer to the base class.

(3) Abstract Classes is a class that contains at least one pure virtual function. A pure virtual function is declared by assigning = 0 to the function in the class declaration.
Abstract classes cannot be instantiated, but they can serve as a base class for other classes to inherit from.
--- Pure Virtual Function: This function does not have an implementation in the base class and must be overridden in derived classes.

(4)Virtual Destructors: if a base class pointer is used to delete a derived class object, the destructor of the base class must be virtual to ensure proper cleanup of the derived class's resources.
--- Without a virtual destructor, only the base class's destructor will be called, which can lead to resource leaks or undefined behavior.

(5)Dynamic Cast is used to safely convert pointers or references from one type to another in a class hierarchy.
It is primarily used for downcasting (casting a base class pointer/reference to a derived class type).
--- dynamic_cast checks at runtime whether the cast is valid, returning nullptr for pointers or throwing std::bad_cast for references if the cast fails.
*/

#include <iostream>
#include <vector>

// Base class: Abstract class with a virtual destructor and a pure virtual function
class Bounds { // Bounds is an abstract class because it contains the pure virtual function enclose(). This means objects of Bounds cannot be instantiated.
public:
    // Virtual destructor to ensure proper cleanup
    virtual ~Bounds() {
        std::cout << "Bounds destructor called.\n";
    }

    // Pure virtual function making this class abstract
    virtual void enclose(const std::vector<int>& points) = 0;

    // Virtual function to be overridden in derived classes
    virtual bool isInside(int point) const = 0;
};

// Derived class: Axis-Aligned Bounding Box (AABox)
class AABox : public Bounds {
public:
    ~AABox() override {
        std::cout << "AABox destructor called.\n";
    }

    // Override the pure virtual function
    void enclose(const std::vector<int>& points) override {
        std::cout << "AABox encloses the points.\n";
    }

    // Override the virtual function
    bool isInside(int point) const override {
        return point > 0 && point < 100;  // Example condition for AABox
    }
};

// Derived class: Circle
class Circle : public Bounds {
public:
    ~Circle() override {
        std::cout << "Circle destructor called.\n";
    }

    // Override the pure virtual function
    void enclose(const std::vector<int>& points) override {
        std::cout << "Circle encloses the points.\n";
    }

    // Override the virtual function
    bool isInside(int point) const override {
        return point == 50;  // Example condition for Circle
    }
};

// Derived class: Oriented Bounding Box (OBBox)
class OBBox : public Bounds {
public:
    ~OBBox() override {
        std::cout << "OBBox destructor called.\n";
    }

    // Override the pure virtual function
    void enclose(const std::vector<int>& points) override {
        std::cout << "OBBox encloses the points.\n";
    }

    // Override the virtual function
    bool isInside(int point) const override {
        return point == 10;  // Example condition for OBBox
    }
};

// Function to check if a point is inside any Bounds
bool isInside(const Bounds& shape, int point) {
    return shape.isInside(point);
}

int main() {
    // Demonstrating polymorphism using base class pointers
    std::vector<int> points = {1, 2, 3, 4};

    // Using raw pointers to manage memory
    Bounds* aabox = new AABox();
    Bounds* circle = new Circle();
    Bounds* obbox = new OBBox();

    // Enclose points using different derived class implementations
    aabox->enclose(points);
    circle->enclose(points);
    obbox->enclose(points);

    // Checking if points are inside different shapes
    int pointToCheck = 50;
    std::cout << "Is point " << pointToCheck << " inside AABox? " 
              << isInside(*aabox, pointToCheck) << "\n";
    std::cout << "Is point " << pointToCheck << " inside Circle? " 
              << isInside(*circle, pointToCheck) << "\n";
    std::cout << "Is point " << pointToCheck << " inside OBBox? " 
              << isInside(*obbox, pointToCheck) << "\n";

    // Manually deleting the dynamically allocated memory to avoid memory leaks
    delete aabox;
    delete circle;
    delete obbox;

    return 0;
}

