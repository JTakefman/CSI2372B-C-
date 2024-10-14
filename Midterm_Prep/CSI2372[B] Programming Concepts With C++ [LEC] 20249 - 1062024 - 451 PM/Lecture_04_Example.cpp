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
#include <iostream>
#include <memory>    // Required for smart pointers
#include <vector>    // Required for vector (dynamic array)
#include <array>     // Required for std::array

// Class representing a 2D Point
class Point2D {
private:
    double x, y;  // Coordinates of the point

public:
    // Default constructor
    Point2D() : x(0), y(0) {
        std::cout << "Default constructor called" << std::endl;
    }

    // Parameterized constructor
    Point2D(double _x, double _y) : x(_x), y(_y) {
        std::cout << "Parameterized constructor called" << std::endl;
    }
	
	// From Lecture05 - Copy constructor
	/* is a special constructor used to create a new object as a copy of an existing object. The copy constructor is invoked when:
    - A new object is initialized from an existing object (e.g., Point2D p2 = p1;).
    - An object is passed by value to a function.
    - An object is returned by value from a function.
	*/
    Point2D(const Point2D& other) : x(other.x), y(other.y) {
        std::cout << "Copy constructor called" << std::endl;
    }

    // Destructor
    ~Point2D() {
        std::cout << "Destructor called for Point2D" << std::endl;
    }

    // Method to display the point's coordinates
    void display() const {
        std::cout << "Point (" << x << ", " << y << ")" << std::endl;
    }
	//Note: 'const' means that display() will not modify any data members of the object it's called on.

    // Method to add two points
    Point2D add(const Point2D& other) const {
        return Point2D(x + other.x, y + other.y);  // Returning a new Point2D object
    }

    // Method to calculate the dot product of two points
    double dot(const Point2D& other) const {
        return x * other.x + y * other.y;
    }
};

// Function demonstrating the use of function pointers
bool comparePoints(const Point2D& pt1, const Point2D& pt2) {
    return pt1.dot(pt2) > 0;  // Compare based on dot product
}

// Function that takes a function pointer as a parameter
void useFunctionPointer(const Point2D& pt1, const Point2D& pt2, bool (*compFunc)(const Point2D&, const Point2D&)) { // comparePoints is a function pointer
    if (compFunc(pt1, pt2)) {
        std::cout << "Dot product is positive." << std::endl;
    } else {
        std::cout << "Dot product is zero or negative." << std::endl;
    }
}

// Inheritance: Base class representing a Shape
class Shape {
public:
    virtual void area() const = 0;  // Pure virtual function (abstract class)

    // Virtual destructor
    virtual ~Shape() {
        std::cout << "Shape destructor called" << std::endl;
    }
};

// Derived class representing a Circle
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    // Overriding the pure virtual function area
    void area() const override {
        std::cout << "Circle Area: " << 3.1415 * radius * radius << std::endl;
    }

    // Destructor
    ~Circle() {
        std::cout << "Circle destructor called" << std::endl;
    }
};
}

// Demonstrating memory allocation and deallocation
void dynamicMemoryAllocation() {
    int* dynArray = new int[5];  // Dynamically allocate an array of 5 integers

    for (int i = 0; i < 5; ++i) {
        dynArray[i] = i * 2;  // Assign values to the array
    }

    std::cout << "Dynamically allocated array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << dynArray[i] << " ";
    }
    std::cout << std::endl;

    delete[] dynArray;  // Free the dynamically allocated memory
}

// Main function demonstrating multiple concepts
int main() {
    // Static and dynamic memory allocation example
    Point2D p1(2.0, 3.0);  // Stack allocation (automatic managed memory)
    Point2D* p2 = new Point2D(4.0, 5.0);  // Heap allocation (dynamic memory allocation and manually deallocated using delete.)

    // Displaying points
    p1.display();
    p2->display();

    // Adding two points
    Point2D p3 = p1.add(*p2);  // Add p1 and p2
    p3.display();

    // Dot product of two points
    double dotProduct = p1.dot(*p2);
    std::cout << "Dot product: " << dotProduct << std::endl;

    // Using function pointers
    useFunctionPointer(p1, *p2, comparePoints);

    // Demonstrate smart pointers
    demonstrateSmartPointers();

    // Demonstrate dynamic memory allocation and deallocation
    dynamicMemoryAllocation();

    // Inheritance and polymorphism
    Shape* shape = new Circle(5.0);  // Polymorphic behavior
    shape->area();  // Calls Circle's area method

    delete shape;  // Free memory allocated to shape

    delete p2;  // Free the dynamically allocated memory for p2

    return 0;
}
/* ***********************************************************************************
This is for you because many asked me about ptr, *ptr, &ptr :)

int main() {
    int var = 42;  // A regular integer variable
    int* ptr = &var;  // 'ptr' is a pointer to 'var'

    // ptr holds the address of var
    std::cout << "Address of var (held by ptr): " << ptr << std::endl;

    // Dereferencing ptr gives the value of var
    std::cout << "Value at the address ptr points to (value of var): " << *ptr << std::endl;

    // &ptr gives the memory address of the pointer itself
    std::cout << "Address of the pointer (ptr itself): " << &ptr << std::endl;

    return 0;
}
*************************************************************************************** */

// For Lecture04, please visit the slides notes to learn more about the theory.