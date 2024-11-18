#include <iostream>
#include <math.h>

using namespace std;

class BigInteger {

    private:
        int base = 0;
        int num = 0;
        int *digits;
        int size;

    public:
        BigInteger() {
            base = 10;
        }

        BigInteger(int _num, int _base) {

            if (_base > 36 ||_base <= 0) {
                cout << "Invalid base provided defaulting to 10 " << endl;
                _base = 10;
            }

            //cout << "Declaring " << _num << " in base " << _base << endl;
            base = _base;
            num = _num;
            //Highest power to initalize digits length with
            //+1 to account for x^0
            int _size = floor(log_n(_base, _num))+1;
            //cout << endl << "Log_n" << endl << log_n(_base, _num) << endl;
            size = _size;
            //cout << "size is " << size << endl;
            digits = new int[size]{0};
            construct_digits();
            //cout << "back to base 10: " << val << endl;
        }

        int get_base() {
            return base;
        }

        int get_num() {
            return num;
        }

        BigInteger(const BigInteger& c) {
            base = c.base;
            num = c.num;
            size = c.size; 
            digits = new int[size]{0};
            for (int i = 0; i < size; i++) {
                digits[i] = c.digits[i];
            }
        }

        ~BigInteger() {
            delete[] digits;
        }

        double log_n(int base, int val) {
            //cout << val << "   Log val: " << log(val) << endl;
            //cout << base << "  Log base: " << log(base) << endl;
            return log(val) / log(base);
        }

        int construct_b10() const {
            int final = 0;
            for (int i = size-1; i > -1; i--) {
                //cout << "Next term is " << pow(base,i) << endl;
                final+= digits[i]*pow(base, i);
                //cout << "final is " << final << endl;
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
            for (int i = size-1; i > -1; i--) {
                
                if (digits[i] >= 10) {
                    //cout << "Digits[i] == " << digits[i] << endl; 
                    char test = char('A' + (digits[i]-10));
                    temp+=test;
                }
                else {
                    temp+=to_string(digits[i]);
                }
            }
            temp+="_b"+to_string(base);
            return temp;
        }

        void construct_digits() {
            int next = num;
            for (int i = size-1; i > -1; i--) {
                //cout << "In loop";
                if (next==0) {
                    break;
                }
                int p = pow(base, i);
                //cout << "Prior to div, next is "<< next << " p is " << p;
                int dig = floor(next / p);
                digits[i]=dig;
                //cout << "dig*p: " << dig*p << endl;
                next -=(dig*p);
                //cout << "p: " << p << ", dig: " << dig << ", next: " << next << " dig[i] " << digits[i] << endl;

            }
            //cout << "dig[4]" << digits[4] << endl;
            //print_digits();
        
        
        }

        int num_digits() {
            return size;
        }
        

        void add_digit(int new_digit) {
            int temp[size];
            for (int i = size-1; i > -1; i--) {
                temp[i]=digits[i];
                //cout << "Inserting " << temp[i] << " at " << i << endl;
            }
            //Delete existing array
            //print_digits();
            //cout << "Prior to delete in add_digit" << endl;
            //print_digits();
            delete[] digits;
            
            //cout << "Size prior is " << size << endl;
            size+=1;
            //cout << endl << endl;
            digits = new int[size]{0};
            //cout << "Size is " << size << endl;
            //2 to account for increase
            for (int i = size-1; i > 0; i--) {
                //cout << "Inserting " << temp[i-1] << " at " << i << endl;
                digits[i]=temp[i-1];
            }
            digits[0] = new_digit;
            //cout << "Following add digits showing new" << endl;
            //print_digits();
        }

        void remove_digit() {
            if (size==0) {
                cout << "Invalid remove, can't go lower than 1 digit" << endl;
                return;
            }
            int temp[size];
            for (int i = size-1; i > -1; i--) {
                temp[i]=digits[i];
            }
            //Delete existing array
            delete[] digits;
            size-=1;
            digits = new int[size]{0};
            //2 to account for increase
            for (int i = size-1; i > -1; i--) {
                digits[i]=temp[i+1];
            }
        }

        void insert_digit(int index, int value) {
            if (index >= size || index < 0) {
                cout << "Invalid index, exceeds bounds of array" << endl;
                return;
            }
            if (value < 0 || value > 36) {
                cout << "Invalid value, exceeds representation max " << endl;
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
            digits = new int[size]{0};
            
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
        

        int& operator[](int index){
            if (index >= size || index < 0) {
                cout << "Array index out of bound, exiting";
                exit(0);
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

        BigInteger operator+(BigInteger & x) {
            int sum = construct_b10() + x.construct_b10();
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }

        //Do we need to account for negatives?
        //Appropriate way to account for 0 case
        BigInteger operator-(BigInteger & x) {
            int sum = construct_b10() - x.construct_b10();
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }

        //Do we need to account for negatives?
        BigInteger operator*(BigInteger & x) {
            int sum = construct_b10() * x.construct_b10();
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }

        //NEEDS TO BE INTEGER DIVISION so your good
        BigInteger operator/(BigInteger & x) {
            int sum = construct_b10() / x.construct_b10();
            //cout << "Sum in addition is " << sum << endl;
            return BigInteger(sum, base);
        }  


        //Still need to figure out
        /*BigInteger& operator=(const BigInteger& other) {
            delete[] digits;

            size=other.size;
            base = other.base;
            digits = new int [size];

        }

        //Easier to just create a new object which will handle hte conversion to
        //the given base via the constructor, then rewriting to update the current 
        //object.
        BigInteger &operator++() {
            *this = BigInteger(construct_b10()+1, base);
            return *this;
        }*/

        

};

int main() {
    //BigInteger i2(92, 37);
    BigInteger i(4052, 29);
    cout  << i.get_num() << "b" << i.get_base() << " is " << i.ret_string() << endl;
    i.print_digits();
    cout << "Size of i is " << i.num_digits() << endl;

    //Add digit
    cout << "Now adding 2 3's as extra digit" << endl;
    i.add_digit(3);
    i.add_digit(3);
    cout << "Now i is " << i.ret_string() << endl;
    
    //Remove digit
    cout << "Now removing 2 extra digit" << endl;
    i.remove_digit();
    i.remove_digit();
    cout << "Now i is " << i.ret_string() << endl;

    //Insert Digit
    cout << "Now inserting digit at start" << endl;
    i.insert_digit(0, 35);
    cout << "Now i is " << i.ret_string() << endl;

    //Insert at end
    cout << "Now inserting digit at end" << endl;
    i.insert_digit(i.num_digits()-1, 2);
    cout << "Now i is " << i.ret_string() << endl;

    //Insert at middle
    cout << "Now inserting digit at middle" << endl;
    i.insert_digit(3, 6);
    cout << "Now i is " << i.ret_string() << endl;

    //[] operator

    cout << "Now changing i[3] from " << i[3] << " to A " << endl;
    i.print_digits();
    //Since only the display uses the character, we still assign with the undelying umerical value
    i[3] = 10;
    cout << "Now i is " << i.ret_string() << endl;

    BigInteger t1(405, 2);
    BigInteger t2(400, 15);
    BigInteger t3(30, 15);

    //Testing boolean operations.
    cout << "t1 is " << t1 << " or " << to_string(t1.construct_b10()) << endl;
    cout << "t2 is " << t2 << " or " << to_string(t2.construct_b10()) << endl;
    cout << "t3 is " << t3 << " or " << to_string(t3.construct_b10()) << endl;

    cout << "Testing t1 == t2 " <<  (t1==t2)<< endl;
    cout << "Testing t1 == t3 " <<  (t1==t3) << endl;

    cout << "Testing t1 != t2 " <<  (t1!=t2) << endl;
    cout << "Testing t1 != t3 " <<  (t1!=t3) << endl;

    cout << "Testing t1 < t2 " <<  (t1<t2) << endl;
    cout << "Testing t1 < t3 " <<  (t1<t3) << endl;

    //Testing arithmetic operations.
    BigInteger a1 = t1 + t2;
    cout << "a1 is " << a1 << " or " << to_string(a1.construct_b10()) << endl;
    BigInteger a2 = t1 - t2;
    cout << "a2 is " << a2 << " or " << to_string(a2.construct_b10()) << endl;
    BigInteger a3 = t1 * t3;
    cout << "a3 is " << a3 << " or " << to_string(a3.construct_b10()) << endl;
    BigInteger a4 = t1 / t2;
    cout << "a4 is " << a4 << " or " << to_string(a4.construct_b10()) << endl;

    //Increment operators
    cout << "testing incrment operator";
    cout << "a1 is " << a1 << " or " << to_string(a1.construct_b10()) << endl;
    //++a1;
    //cout << "a1 is " << a1 << " or " << to_string(a1.construct_b10()) << endl;

    return 0;  
}
