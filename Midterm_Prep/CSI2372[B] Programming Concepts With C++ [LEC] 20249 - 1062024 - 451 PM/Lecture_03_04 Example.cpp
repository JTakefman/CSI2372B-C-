// CSI2372 example Code
// Lecture 02 and Lecture 03 and Lecture 04
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

// Classes in C++: Classes are user-defined data types in C++ that can hold attributes (variables) and methods (functions).

// Define a class named Point2D to represent a point in 2D space
class Point2D {
    double d_x;   // x-coordinate (private by default)
    double d_y;   // y-coordinate (private by default)

public:
    // Default constructor, uses compiler's default initialization
	// Compiler automatically generates the default constructor.
    Point2D() = default;

    // Parameterized constructor to initialize x and y with user-provided values
    Point2D(double _x, double _y) : d_x(_x), d_y(_y) {} // Initializes the object's d_x and d_y attributes with provided arguments.
	
	// Q: d_x(_x), d_y(_y) {} as d_x = _x, d_y = _y {}?
	// No: This is because the initializer list allows variables to be initialized before the constructor body is executed. Writing d_x = _x would only assign the values after the object has already been initialized
	
    // Method to add two Point2D objects and return a new Point2D object
    Point2D add(const Point2D& other) { // The parameter const ensures that the passed Point2D object is not modified inside the method
        double new_x = d_x + other.d_x;
		double new_y = d_y + other.d_y;
		return Point2D(new_x, new_y);

		// OR: this one statement instead of the previous three lines: return Point2D(d_x + other.d_x, d_y + other.d_y);
    }

    // Method to calculate the dot product of two Point2D objects ( x1×x2 + y1×y2​)
    double dot(const Point2D& other) const {
        return d_x * other.d_x + d_y * other.d_y;
    }
	
	/*Q: Write a method that is useful for cleaning up resources like dynamically allocated memory or file handles when an object goes out of scope or is deleted. In its body, print a notification message to let the user that we executed this cleaner method.
	public:
    ~Point2D() {
        std::cout << "Destructor called for Point2D" << std::endl;
    }
	*/
};
//**************************************************************************************
// Pointers and Arrays:
// A pointer is a variable that stores the address of another variable.
// Arrays are contiguous memory locations holding elements of the same type.
// Pointers are useful for more advanced use cases such as dynamic arrays, pointer arithmetic, or when passing arrays to functions.

int arr[] = {2, 4, 6, 8};  // Declare and initialize an integer array
int* ptr = arr;  // Pointer 'ptr' points to the first element of the array 'arr'

for (int i = 0; i < 4; ++i) {  // Loop through each element in the array
    std::cout << "Element " << i << " is " << *(ptr + i) << std::endl;  // Dereference the pointer to print the array value
	// Accesses the element at index i by using pointer arithmetic.
	
	// Note: Dereferencing a pointer means accessing the value that the pointer is pointing to. For example, if int* p = &x;, then *p dereferences the pointer p to get the value of x.
	
	// Note: *(ptr + i) is a pointer arithmetic expression that accesses the value at the memory address pointed to by ptr, offset by i. It’s equivalent to ptr[i].
	
	// Q: Modify the pointer so that it points to the second element of the array. Print its value.
	// Q: Can I print the array without using pointers? If so, why use pointers? - see below:
	/*
	int arr[] = {2, 4, 6, 8};
	for (int i = 0; i < 4; ++i) {
    std::cout << arr[i] << std::endl;
	}
	*/
}
//**************************************************************************************
//From Lectures 03 + Lecture 04
// Memory Management: Dynamic Memory Allocation: C++ allows dynamic allocation using new and deallocation using delete.
int* p = new int;  // Dynamically allocate memory for one integer
*p = 10;           // Assign the value 10 to the allocated memory

std::cout << *p << std::endl;  // Output the value stored at the pointer (10)

delete p;  // Free the dynamically allocated memory
// Q: What happens if you forget to delete dynamically allocated memory?

// Task: Write a program that dynamically allocates memory for an array of 10 integers, initializes them, and prints their values.

// Note: Static allocation: Memory is allocated at compile-time and remains allocated throughout the program's life. Automatic (stack) allocation: Memory is allocated when a function is called and deallocated when the function exits (e.g., local variables).

//**************************************************************************************
/* Function Overloading:  C++ allows functions with the same name but different parameter lists (overloading).
 Q: What is the function header/signeature?
*/

int add(int a, int b) {
    return a + b;  // Adds two integers
}

double add(double a, double b) {
    return a + b;  // Adds two doubles

// Q: Can we overload functions that differ only in their return type?
// Answer: C++ cannot distinguish between functions solely by their return type. The function signature (name + parameter list) must be different because the return type is not considered in the function's signature during compilation.
}
//**************************************************************************************
// Constructors: Initialize object attributes. Can be default or parameterized.
// Destructors: Clean up resources when the object is destroyed.

class MyClass {
    int* data;  // Pointer to dynamically allocated memory

public:
    // Constructor that allocates memory for an array
    MyClass(int size) {
        data = new int[size];  // Allocate memory dynamically for an array of 'size'
    }

    // Destructor that frees allocated memory
    ~MyClass() {
        delete[] data;  // Free dynamically allocated memory
    }
};
//**************************************************************************************
// Inheritance in C++: C++ supports single and multiple inheritance, where a class can inherit attributes and methods from one or more base classes
class Base {
public:
    void show() {
        std::cout << "Base class show()" << std::endl;  // Method in the base class
    }
};

class Derived : public Base {
public:
    void show() {
        std::cout << "Derived class show()" << std::endl;  // Method in the derived class overrides base class method
    }
};
//**************************************************************************************
/* Virtual Functions and Polymorphism
Virtual Functions: Allow dynamic binding in C++ for implementing polymorphism.
Polymorphism: The ability of a function to behave differently based on the object that calls it. Virtual functions enable polymorphism by allowing derived classes to override base class methods and ensuring the correct method is called at runtime.
*/
class Base {
public:
    virtual void print() {
        std::cout << "Base class" << std::endl;  // Virtual function in base class
    }
};
//**************************************************************************************
// Another Polymorphism/Inheritance Example
class Derived : public Base {
public:
    void print() override {
        std::cout << "Derived class" << std::endl;  // Override the base class virtual function
    }
};

class Animal {
public:
    virtual void sound() {
        std::cout << "Animal sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    void sound() override {
        std::cout << "Bark" << std::endl;
    }
};

class Cat : public Animal {
public:
    void sound() override {
        std::cout << "Meow" << std::endl;
    }
};

int main() {
    Animal* a = new Dog();
    a->sound();  // Outputs: Bark

    Animal* b = new Cat();
    b->sound();  // Outputs: Meow

    delete a;
    delete b;
    return 0;
}

//**************************************************************************************
/* Type Aliasing and Storage Class Modifiers: To make codes shorter and more readable
 Type Aliasing: Introduced with 'typedef' and 'using'. Simplifies using complex data types.
 Storage Class Modifiers: Control variable lifetime and visibility (static, extern, const).
*/
typedef unsigned int uint;  // Create a type alias 'uint' for 'unsigned int', allowing you to use uint as a shorthand for declaring unsigned integers.

uint a = 100;  // Use the alias to declare a variable


// Below is the same previous code without aliasing.
uint a = 100;
unsigned int b = 200;  // Without alias
std::cout << a << " " << b << std::endl;

/* Note: The difference between static, const, and extern variables?
    - static: Variable retains its value across multiple function calls.
    - const: Variable cannot be modified after initialization.
    - extern: Variable declared but defined elsewhere (used across multiple files).
*/


// Note: The slides in lecture03 are very important to read for detailed examples.