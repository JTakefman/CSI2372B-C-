// ------------------------------------------------------------------------------
// Assignment 4
// Written by: Jordan Takefman, 300171459
// For CSI2372 Section B
// Time to complete:
// Resources: Standard C++ Documentation
// -----------------------------------------------------------------------------

#include <iostream>
#include <math.h>

using namespace std;

class BigInteger {

    private:
        int base = 0;
        bool negative = false;
        long long int *digits;
        int size;

    public:
        BigInteger() {
            base = 10;
        }

        BigInteger(long long int _num, int _base) {

            if (_base > 36 ||_base <= 1) {
                cout << "ERROR: Invalid base provided: " << _base << "\t defaulting to 10 " << endl;
                _base = 10;
            }

            //cout << "Declaring " << _num << " in base " << _base << endl;
            base = _base;
            if (_num<0) {
                negative=true;
            }
            //Account for negatives
            _num = abs(_num);
            //cout << "Num is " << num << endl;
            //cout << "Neg is " << negative << endl;
            //Highest power to initalize digits length with
            //+1 to account for x^0

            //1 as default minimum size to store a given integer
            int _size = 1;
            if (_num!=0) {
                _size = floor(log_n(_base, _num))+1;
                //cout << endl << "Log_n: " << log_n(_base, _num) << endl;
                //cout << "_size is " << _size;
            }
            size = _size;
            //cout << "size is " << size << endl;
            digits = new long long int[size]{0};
            //cout << "Now constructing digits for value " << _num << endl;
            construct_digits(_num);
            //cout << "back to base 10: " << val << endl;
        }

        int get_base() {
            return base;
        }

        int num_digits() {
            return size;
        }

        BigInteger(const BigInteger& c) {
            base = c.base;
            size = c.size; 
            digits = new long long int[size]{0};
            for (int i = 0; i < size; i++) {
                digits[i] = c.digits[i];
            }
        }

        ~BigInteger() {
            delete[] digits;
        }

        //
        long double log_n(long double base, long double val) {
            //cout << val << "   Log val: " << log(val) << endl;
            //cout << base << "  Log base: " << log(base) << endl;
            return log(val) / log(base);
        }

        long long int construct_b10() const {
            long long int final = 0;
            for (int i = size-1; i > -1; i--) {
                //cout << "Next term is " << pow(base,i) << endl;
                //cout << "digits[i] is " << digits[i] << " with i " << i << endl;
                final+= digits[i]*pow(base, i);
                //cout << "final is " << final << endl;
            }
            //cout << "Negative status currently is " << negative << endl;
            //cout << "Current constructed final is " << final << endl;
            if (negative==true) {
                //cout << "Constructing negative value " << endl;
                return (0-final);
            }
            return final;
        }

        void print_digits() {
            for (int i = size-1; i > -1; i--) {
                cout << pow(base, i) << "\t";
            }
            cout << endl;
            for (int i = size-1; i > -1; i--) {
                if (digits[i] >= 10) {
                    char test = char('A' + (digits[i]-10));
                    cout << test << "\t";
                }
                else {
                    cout << digits[i] << "\t";
                }

            }
            cout << endl;
        }

        string ret_string() const {
            string temp ="";
            if (negative==true) {
                temp+="-";
            }
            //cout << "Now initializing string size is " << size << endl; 
            for (int i = size-1; i > -1; i--) {
                //cout << "Digits[ " << i << "] == " << digits[i] << endl; 
                if (digits[i] >= 10) {
                    char test = char('A' + (digits[i]-10));
                    temp+=test;
                }
                else {
                    temp+=to_string(digits[i]);
                }
            }
            temp+="_"+to_string(base);
            return temp;
        }

        void construct_digits(long long int num) {
            long long int next = num;
            for (int i = size-1; i > -1; i--) {
                //cout << "In loop";
                if (next==0) {
                    break;
                }
                long long int p = pow(base, i);
                //cout << "Prior to div, next is "<< next << " p is " << p;
                long long int dig = floor(next / p);
                digits[i]=dig;
                //cout << "dig*p: " << dig*p << endl;
                next -=(dig*p);
                //cout << "p: " << p << ", dig: " << dig << ", next: " << next << " dig[i] " << digits[i] << endl;

            }
            //cout << "dig[4]" << digits[4] << endl;
            //print_digits();
        
        
        }
        

        void add_digit(int new_digit) {
            //Check edge cases
            if (new_digit > (base-1) || new_digit < 0) {
                cout << "ERROR: Trying to add an invalid digit: " << new_digit << " returning " << endl;
                return;
            }
            int temp[size];
            //Copy over digits to temporary array
            for (int i = size-1; i > -1; i--) {
                temp[i]=digits[i];
            }
            //Delete existing array and increase size
            delete[] digits;
            size+=1;
            digits = new long long int[size]{0};

            for (int i = size-1; i > 0; i--) {
                digits[i]=temp[i-1];
            }
            digits[0] = new_digit;
        }

        void remove_digit() {
            if (size==1) {
                cout << "ERROR: Invalid remove_digit, can't go lower than 1 digit" << endl;
                return;
            }
            int temp[size];
            for (int i = size-1; i > -1; i--) {
                temp[i]=digits[i];
            }
            //Delete existing array
            delete[] digits;
            size-=1;
            digits = new long long int[size]{0};
            //2 to account for increase
            for (int i = size-1; i > -1; i--) {
                digits[i]=temp[i+1];
            }
        }

        void insert_digit(int index, int value) {
            if (index >= size || index < 0) {
                cout << "ERROR: Invalid index " << index << " exceeds bounds of array" << endl;
                return;
            }
            if (value < 0 || value > 36) {
                cout << "ERROR: Invalid value " << value << " exceeds representation max " << endl;
                return;
            }

            if (value > base-1) {
                cout << "ERROR: Invalid value" << value << " exceeds base max" << endl;
                return;
            }

            if (index == 0) {
                add_digit(value);
                return;
            }
            int temp[size];
            for (int i = size-1; i > -1; i--) {
                temp[i]=digits[i];
            }
            
            //Delete existing array
            //cout << "Prior to delete digits in insert_digit" << endl;
            //print_digits();
            delete[] digits;
            size+=1;
            digits = new long long int[size]{0};
            
            if (index == size-2) {
                //Update last value
                //cout << "Inserting digit at end aaaaah" << endl;
                //cout << "Size is " << size << " and index is " << index << endl;
                digits[index+1]=value;
                //Do the rest
                //cout << "Digits end is " << digits[index+1];
                for (int i = index; i > -1; i--) {
                    //cout << "Entered loop" << endl;
                    //cout << "Inserting " << temp[i] << " into position " << i << endl;
                    digits[i] = temp[i];
                }

            }
            //Between 0 and size-2
            else {
                //First half
                //cout << "Doing first half" << endl;
                //cout << "size is " << size << " and index is " << index << endl;
                for (int i = size-1; i > index; i--) {
                    //cout << "I is " << i << " and temp is " << temp[i-1] << endl;
                    digits[i] = temp[i-1];
                }
                //Middle
                digits[index]=value;
                //Insert index
                for (int i = index-1; i > -1; i--) {
                    //cout << "I is " << i << " and temp is " << temp[i] << endl;
                    digits[i] = temp[i];
                }
            }
        }
        
        //Since we have the insert digit method for assigning at a given index, I'm assuming
        //that this operator is meant to be read only hence returning just the value at 
        //the provided indesx. Furthermore, the standard convention would be to throw an exception obviously 
        //but since that isn't specified in the document, I'm assuming that we're ok to 
        //just return a value an indicate an error.

        long long int operator[](int index){
            if (index >= size || index < 0) {
                cout << "ERROR: Array index out of bound, exiting" << endl;
                return -1;
            }
            return digits[index];
        }

        bool operator == (const BigInteger &other) {
            //cout << "Comparing " << construct_b10() << " with " << other.construct_b10() << endl;
            return (construct_b10() == other.construct_b10());
        }

        bool operator < (const BigInteger &other) {
            //cout << "Comparing " << construct_b10() << " with " << other.construct_b10() << endl;
            return (construct_b10() < other.construct_b10());
        }

        bool operator > (const BigInteger &other) {
            //cout << "Comparing " << construct_b10() << " with " << other.construct_b10() << endl;
            return (construct_b10() > other.construct_b10());
        }

        bool operator >= (const BigInteger &other) {
            //cout << "Comparing " << construct_b10() << " with " << other.construct_b10() << endl;
            return (construct_b10() >= other.construct_b10());
        }

        bool operator <= (const BigInteger &other) {
            //cout << "Comparing " << construct_b10() << " with " << other.construct_b10() << endl;
            return (construct_b10() <= other.construct_b10());
        }

        bool operator != (const BigInteger &other) {
            //cout << "Comparing " << construct_b10() << " with " << other.construct_b10() << endl;
            return (construct_b10() != other.construct_b10());
        }

        friend ostream & operator << (ostream &out, const BigInteger &c) {
            string str = c.ret_string();
            out << str;
            return out;
        }

        //I chose the convention of simply _n to represent the base at the end of
        //a number
        BigInteger& operator>>(const string input){
            if (input.size() < 3) {
                cout << "ERROR: Invalid string input to >>, less than 3 characters" << endl;
                return *this;
            }
            string back= "";
            int base = 0;
            int len = input.size()-1;
            if (input[len-1]!='_' && input[len-2]!='_') {
                cout << "ERROR: Invalid string input to >>, missing underscore in valid positions" << endl;
                return *this;
            }

            for (int i = len; i > len-2; i--) {
                if (input[i]=='_') {
                    break;
                }
                if (isdigit(input[i])==false) {
                    cout << "ERROR: Invalid string input to >>, non numeric character at end" <<endl;
                    return *this;
                }
                back=input[i]+back;
            }
            //cout << "Base in >> is " << base << endl;
            //cout << "Back is " << back << endl;
            //cout << "Back length is " << back.length() << endl;
            base = stoi(back);
            //Remove back characters from loop so we don't go over them

            if (base > 36 || base < 2) {
                cout << "ERROR: Invalid string input to >>, base exceeds 36 or less than 2" << endl;
                return *this;
            }

            len -= back.size();
            long long int val = 0;
            bool negative = false;
            int i = 0;
            if (input[0] == '-') {
                //cout << "Number is negative " << endl;
                negative=true;
            }
            //cout << "Prior to starting loop len is " << len << endl;
            for (int i = 0; i < len; i++) {
                long long int num = 0;
                //cout << "Input[i] for " << i << "is " << input[i] << endl;
                if (input[i]=='-') {
                    negative=true;
                    continue;
                }
                if (isdigit(input[i])==false) {
                    if (input[i] >= 'A' && input[i] <= 'Z') {
                        num = input[i] - 'A' + 10;
                        if (num > base-1) {
                            cout << "ERROR: coefficient exceeds maximum allowed by base" << endl;
                            return *this;
                        }
                    }
                    else {
                        cout << "ERROR: Invalid string input to >>, character exceeds maximum value" <<endl;
                        return *this;
                    }
                    
                }
                else {
                    num = input[i] - '0';
                    if (num > base-1) {
                        cout << "ERROR: coefficient exceeds maximum allowed by base" << endl;
                        return *this;
                    }
                }
                //cout << "Num is " << num << " pow is " << pow(base, len-i-1) << endl;
                val+=num*pow(base, len-i-1);
                //cout << "Intermediate calculation at i= " << i << " is " << val << endl;
                //cout << "Exponent is " << len-i-1 << endl;
            }
            //cout << "Final val prior to reinitilzation is " << val << endl;
            if(negative) {
                val*=-1;
            }
            *this = BigInteger(val, base);
            return *this;
        }

        BigInteger operator+(BigInteger & x) {
            long long int sum = construct_b10() + x.construct_b10();
            //cout << "First term b_10() is " << construct_b10() << endl;
            //cout << "Second term b_10() is " << x.construct_b10() << endl;
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }

        BigInteger operator+(int x) {
            long long int sum = construct_b10() + x;
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }

        //Do we need to account for negatives?
        //Appropriate way to account for 0 case
        BigInteger operator-(BigInteger & x) {
            long long int sum = construct_b10() - x.construct_b10();
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }

        BigInteger operator-(int x) {
            long long int sum = construct_b10() - x;
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }

        //Do we need to account for negatives?
        BigInteger operator*(BigInteger & x) {
            long long int sum = construct_b10() * x.construct_b10();
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }

        BigInteger operator*(int x) {
            long long int sum = construct_b10() * x;
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }

        //NEEDS TO BE INTEGER DIVISION so your good
        BigInteger operator/(BigInteger & x) {
            long long int sum = construct_b10() / x.construct_b10();
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }

        BigInteger operator/(int x) {
            long long int sum = construct_b10() / x;
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }

        BigInteger operator%(BigInteger & x) {
            long long int sum = construct_b10() % x.construct_b10();
            cout << "vals are " << construct_b10() << " and " << x.construct_b10() << endl;
            cout << "Sum in modulus is " << sum << endl;
            return BigInteger(sum, base);
        }
        BigInteger operator%(int x) {
            long long int sum = construct_b10() % x;
            //cout << "Sum in modulus is " << sum << endl;
            return BigInteger(sum, base);
        }  


        //Still need to figure out
        BigInteger& operator=(const BigInteger& other) {
            delete[] digits;

            size=other.size;
            base = other.base;
            digits = new long long int[size];
            negative=other.negative;

            for (int i = 0; i < size; i++) {
                digits[i]=other.digits[i];
            }

            return *this;
        }

        //Easier to just create a new object which will handle hte conversion to
        //the given base via the constructor, then rewriting to update the current 
        //object.
        BigInteger &operator++(int) {
            *this = BigInteger(construct_b10()+1, base);
            return *this;
        }

        BigInteger operator++() {
            BigInteger temp = *this;
            ++(*this);
            return *this;
        }

        BigInteger &operator--(int) {
            //cout << "for -- value is currently " << construct_b10()-1 << endl;
            *this = BigInteger(construct_b10()-1, base);
            //cout << "for -- value is after" << construct_b10() << endl;
            return *this;
        }

        BigInteger operator--() {
            BigInteger temp = *this;
            --(*this);
            return *this;
        }

        

};

void standard_tests() {
    cout << "***********************\nSTART OF STANDARD TESTS\n******************\n\n";
    BigInteger b(52643, 16);
    //Test copy constructor
    BigInteger b1 = b;
    //Demonstrate << opreator
    cout << "b is " << b << " or " << b.construct_b10() << " in b10 " << endl;
    cout << "b2 is " << b1<< endl << b1.construct_b10() << " in b10 " << endl;;
    //Test num digits
    cout << "num_digits in b is " << b.num_digits() << endl;
    cout << "num_digits in b is " << b.num_digits() << endl << endl;
    //Testing add digits
    //Valid
    cout << "Now testing add_digit(5/0/15)" << endl;
    b.add_digit(5);
    b.add_digit(0);
    b.add_digit(15);
    cout << "b is " << b << " or " << b.construct_b10() << " in b10 " << endl;
    //Invalid
    b.add_digit(200);
    b.add_digit(16);
    b.add_digit(-1);
    cout << "b is " << b << " or " << b.construct_b10() << " in b10 " << endl << endl;
    cout << "Now testing remove_digit() by clearing b" << endl;
    int size = b.num_digits();

    for (int i = 0; i < size; i++) {
        cout << "On iteration " << i << " calling remove_digit on b" << endl;
        b.remove_digit();
        cout << "b is " << b << " or " << b.construct_b10() << " in b10 " << endl;
    }
    cout << endl << "Now testing insert_digit()" << endl;
    //Invalid tests due to size
    b.insert_digit(50, 5);
    b.insert_digit(-1, 5);
    b.insert_digit(1, 5);
    cout << "b is " << b << " or " << b.construct_b10() << " in b10 " << endl;
    //Now valid tests
    b.insert_digit(0, 5);
    cout << "b is " << b << " or " << b.construct_b10() << " in b10 " << endl;
    //Exceeds base-1
    b.insert_digit(1, 16);
    //Back to valid
    b.insert_digit(0, 13);
    cout << "b is " << b << " or " << b.construct_b10() << " in b10 " << endl;
    b.insert_digit(1, 10);
    cout << "b is " << b << " or " << b.construct_b10() << " in b10 " << endl;
    b.insert_digit(2, 3);
    cout << "b is " << b << " or " << b.construct_b10() << " in b10 " << endl;
    b.print_digits();
    //Now testing indexing
    cout << "b num digits is " << b.num_digits() << endl;
    cout << "b[6]=" << b[6] << endl;
    cout << "b[-1]=" << b[-1] << endl;
    cout << "b[0]=" << b[0] << endl;
    cout << "b[3]=" << b[3] << endl;
    cout << "b[2]=" << b[2] << endl;
    //Now testing the boolean operators
    cout << endl << endl << " now testing equality operators " << endl;
    BigInteger b2(365, 5);
    BigInteger b3(492, 29);
    cout << "b2: " << b2 << endl;
    cout << "b3: " << b3 << endl << endl;;
    cout << "b2==b3: " << (b2==b3) << endl;
    cout << "b2<b3: " << (b2<b3) << endl; 
    cout << "b2>b3: " << (b2>b3) << endl; 
    cout << "b2>=b3: " << (b2>=b3) << endl; 
    cout << "b2<=b3: " << (b2<=b3) << endl; 
    cout << "b2!=b3: " << (b2!=b3) << endl << endl;

    
    cout << "b2 is " << b2 << " or " << b2.construct_b10() << " in b10 " << endl;
    cout << "b3 is " << b3 << " or " << b3.construct_b10() << " in b10 " << endl;
    cout << "Now testing assignment operator" << endl;
    b2 = b3;
    cout << "b2 is " << b2 << " or " << b2.construct_b10() << " in b10 " << endl;
    cout << "b3 is " << b3 << " or " << b3.construct_b10() << " in b10 " << endl << endl;

    cout << "Now testing arithmetic operators" << endl;
    BigInteger b4(-129207, 32);
    BigInteger b5(90583, 7);
    cout << "b2 is " << b4 << " or " << b4.construct_b10() << " in b10 " << endl;
    cout << "b3 is " << b5 << " or " << b5.construct_b10() << " in b10 " << endl;
    cout << "b4+b5: " << (b4+b5) << " or " << (b4+b5).construct_b10() << " in b10 " << endl;
    cout << "b4-b5: " << (b4-b5) << " or " << (b4-b5).construct_b10() << " in b10 " << endl;
    cout << "b4*b5: " << (b4*b5) << " or " << (b4*b5).construct_b10() << " in b10 " << endl;
    cout << "b4/b5: " << (b4/b5) << " or " << (b4/b5).construct_b10() << " in b10 " << endl;
    BigInteger modulus = (b4%b5);
    cout << "b4%b5: " << modulus << " or " << modulus.construct_b10() << " in b10 " << endl;

}

int main() {
    standard_tests();
    return 0;  
}
