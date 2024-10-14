#include <iostream>
using namespace std;

enum class Color {
    Red,    // Red is assigned 0
    Green,  // Green is assigned 1
    Blue    // Blue is assigned 2
};

int main() {
    Color myColor = Color::Red;  // Setting color to Red
    if (myColor == Color::Red) {
        cout << "Color is Red!" << endl;
    }
    return 0;
	
	// Go to Lecture 1 - Slides 8 to 10 important
	int a = 5, b = 10;
	int sum = a + b;  // Addition
	int product = a * b;  // Multiplication
	int a += 5
	bool isGreater = b > a;  // Comparison (true if b is greater than a)

//#####################################################################################
	// Control Statements (if, switch)
	int num = 5;
	if (num > 3) {
		cout << "Num is greater than 3!" << endl;
	}
//#####################################################################################	
	// switch statement:
	int choice = 2;
	switch (choice) {
		case 1:
			cout << "You chose 1." << endl;
			break;
		case 2:
			cout << "You chose 2." << endl;
			break;
		default:
			cout << "Invalid choice." << endl;
		
	// C++17 allows you to initialize a variable directly within the switch statement, improving code readability. 
		switch (auto k = 1.51; counter) {
		    case 0: x = 3.0 * k; break;
			case 1: x = 8.0 * k; break;
			default: x = -1.0;
}
}
// Go to Lecture 1 to see examples about while and do/while

// *******************************************************************************

// Introduction to std::array and std::vector
// std::array is a fixed-size array, while std::vector is a dynamic array that grows in size as needed, making it similar to Java's ArrayList.

#include <iostream>
#include <array>
using namespace std;

int main() {
    array<int, 5> arr = {1, 2, 3, 4, 5};  // Fixed-size array of integers
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    return 0;
}

//#####################################################################################
#include <vector>
#include <iostream>
using namespace std;

int main() {
	// using an iterator to traverse and print the elements of a vector
    vector<int> iVec(10, 0);  // Initialize vector of size 10 with 0
    for (auto iter = iVec.begin(); iter != iVec.end(); ++iter) {
        cout << *iter << endl;
    }
    return 0;
}
//#####################################################################################

// Another vector-type

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 3};
    vec.push_back(4);  // Add element to the end
    vec.push_back(5);
    
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";  // Access elements
    }
    return 0;
}
// Type Conversion - What is the difference between the 3 casting types?
double x = 3.14;
int y = static_cast<int>(x);  // Explicitly casting double to int
cout << "y = " << y << endl;  // y = 3 (fractional part is discarded)

}

//#####################################################################################

