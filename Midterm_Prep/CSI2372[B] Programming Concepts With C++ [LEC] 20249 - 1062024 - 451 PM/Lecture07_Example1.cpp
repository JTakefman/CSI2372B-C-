// CSI2372 example Code
// Lecture07
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
#include <string>

// Stack class demonstrating deep copy, assignment operator, and static members
class Stack {
private:
    int d_capacity;         // Stack capacity
    int d_size;             // Current size of the stack
    std::string* d_stack;   // Dynamically allocated stack array

    static int stackCount;  // Static member to track number of Stack objects. This is shared among all instances of Stack class. Unlike regular member variables (which are specific to each object), a static variable belongs to the class itself, meaning that all instances of the class share the same static variable.

public:
    // Constructor
    Stack(int capacity = 10) : d_capacity(capacity), d_size(0), d_stack(new std::string[capacity]) {
        ++stackCount;  // Increment static member
        std::cout << "Stack created. Current stack count: " << stackCount << std::endl;
    }

    // Copy constructor (Deep copy)
    Stack(const Stack& other) : d_capacity(other.d_capacity), d_size(other.d_size), d_stack(new std::string[other.d_capacity]) {
        for (int i = 0; i < d_size; ++i) {
            d_stack[i] = other.d_stack[i];
        }
        ++stackCount;
        std::cout << "Stack copied. Current stack count: " << stackCount << std::endl;
    }

    // Destructor
    ~Stack() {
        delete[] d_stack;
        --stackCount;
        std::cout << "Stack destroyed. Current stack count: " << stackCount << std::endl;
    }

    // Assignment operator (Deep copy)
    Stack& operator=(const Stack& other) { //it will be called with s1=s2
        if (this != &other) {  // Check for self-assignment
            delete[] d_stack;  // Free existing memory

            d_capacity = other.d_capacity;
            d_size = other.d_size;
            d_stack = new std::string[d_capacity];
            for (int i = 0; i < d_size; ++i) {
                d_stack[i] = other.d_stack[i];
            }
        }
        return *this;
    }

    // Static function to get current stack count
	// Static method can be called without creating an object and can only operate on static members of the class.
    static int getStackCount() {
        return stackCount;
    }

    // Inline function to push a string onto the stack
	// It is expanded in place where they are invoked, avoiding the overhead of a function call.
	// Inline functions should be short and used sparingly to improve performance.
    inline void push(const std::string& str) {
        if (d_size < d_capacity) {
            d_stack[d_size++] = str;
        } else {
            std::cerr << "Stack overflow!" << std::endl;
        }
    }

    // Inline function to pop a string from the stack
    inline std::string pop() {
        if (d_size > 0) {
            return d_stack[--d_size];
        } else {
            throw std::out_of_range("Stack underflow!");
        }
    }
	
};

// Initialize static member
int Stack::stackCount = 0;

};

int main() {
    try {
        Stack s1;  // Default stack
        s1.push("Hello");
        s1.push("World");

        Stack s2 = s1;  // Copy constructor (deep copy)
        s2.push("Copied stack");

        std::cout << "Popped from s1: " << s1.pop() << std::endl;
        std::cout << "Popped from s2: " << s2.pop() << std::endl;

        std::cout << "Current stack count: " << Stack::getStackCount() << std::endl; // getStackCount() is a static method so no need to use object to call it

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
// *******************************************************************************************************************************************************************************
/* Rule 3/5 in C++11:
refers to the principles of managing resources (like dynamic memory, file handles, or network connections) in classes that define their own custom destructors, copy constructors, or assignment operators
-  If a class defines any one of the following three functions, it should define all three: 1- copy constructor, 2- destructor, 3- Copy Assignment Operator.

The Rule of 5 extends the Rule of 3 to handle move resources rather than duplicating them, especially when dealing with large objects or temporary objects by defining:
 - Move Constructor: Transfers ownership of resources from a temporary object (r-value) to a new object, avoiding deep copying.
 - Move Assignment Operator: Transfers resources from one existing object to another, again avoiding deep copying.

* A move constructor "moves" resources from one object to another, rather than copying them. It was introduced in C++11 to improve performance when dealing with temporary objects, especially when those objects manage dynamic memory or other resources.
* The move constructor is designed to "steal" the resources from a source object that is about to be destroyed, avoiding the need for a deep copy of the object’s data. After the move, the source object is typically left in an empty but valid state.
*/

#include <iostream>

class MyClass {
private:
    int* data;

public:
    // Constructor
    MyClass(int value) : data(new int(value)) {
        std::cout << "Constructor called\n";
    }

    // Move Constructor
    MyClass(MyClass&& other) noexcept : data(other.data) {	// r-value reference (MyClass&&), which means it can accept temporary objects (r-values) that are about to go out of scope
        other.data = nullptr;  // Reset the source object's pointer
        std::cout << "Move constructor called\n";
		
		// 'noexcept' tells the compiler that the function does not throw exceptions.
    }

    // Destructor
    ~MyClass() {
        if (data) {
            std::cout << "Destructor called, deleting data\n";
            delete data;
        } else {
            std::cout << "Destructor called, nothing to delete\n";
        }
    }

    // Function to display the value
    void display() const {
        if (data) {
            std::cout << "Value: " << *data << std::endl;
        } else {
            std::cout << "No data to display\n";
        }
    }
};

int main() {
    MyClass obj1(10);  // Calls the regular constructor, creating an object with dynamic memory (data = new int(10)).
    obj1.display();

    MyClass obj2 = std::move(obj1);  // Calls move constructor, transferring ownership
									// It transfers ownership of the dynamically allocated memory (data) from obj1 to obj2. After the move, obj1.data is set to nullptr, so obj1 is in a valid but empty state.
    obj2.display();   // Shows the value (10) that was moved from obj1 because obj1's resource was transferred to obj2.
    obj1.display();  // obj1 is left in an empty state

    return 0;
}
/*
Ouput:

Constructor called
Value: 10
Move constructor called
Value: 10
No data to display
Destructor called, nothing to delete
Destructor called, deleting data

*/