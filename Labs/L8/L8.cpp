
//Q1

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
using namespace std;

//For the sake of ease and convention I'm not going to bother
//accounting for leap years or different dates of months or anything like that.
//I'm also gonna assume month's are 30 days and years are 360 days.

class Date {
    private:
        int day;
        int month;
        int year;

    public:
        //Ternary to check valid dates and default if invalid
        Date(int _day, int _month, int _year) {
            day = (_day < 31 && _day > 0) ? _day : 1;
            month = (_month < 13 && _month > 0) ? _month : 1;
            year = (_year > 0) ? _year : 2024;
        }

        //Ripple carry esq addition up from day to year
        Date operator+(int const& i) {
            //cout << endl << endl << "Adding" << endl;
            int temp = i;
            //cout << "temp is " << temp << endl;
            int a_year = floor(temp/360);
            //cout << "a_year is " << a_year << endl;
            temp -= 360*a_year;
            int a_month = floor(temp/30);
            //cout << "a_month is " << a_month << endl;
            temp-=30*a_month;
            //cout << "Temp is " << temp << endl;
            int a_day = temp;
            //cout << "a_day is " << a_day << endl;
            day+= a_day;
            if(day > 30) {
                month+=floor(day/30);
                day = day%30;
            }
            month+=a_month;
            if (month > 12) {
                year+=floor(month/12);
                month = month%12;
            }
            year+=a_year;
            return *this;
        }

        //Convert the day to an epoch, add, then convert back;
        Date operator-(int const& i) {
            //cout << endl << endl << "Subtracting" << endl;
            int temp = i;
            //cout << "temp is " << temp << endl;
            int a_year = floor(temp/360);
            //cout << "a_year is " << a_year << endl;
            temp -= 360*a_year;
            int a_month = floor(temp/30);
            //cout << "a_month is " << a_month << endl;
            temp-=30*a_month;
            //cout << "Temp is " << temp << endl;
            int a_day = temp;
            //cout << "a_day is " << a_day << endl;
            day-= a_day;
            if(day <= 0) {
                day-=30;
                //cout << "day is " << day << endl;
                month+=floor(day/30);
                //cout << "Month is " << month << endl;
                day = -1*(day%31);
            }
            month-=a_month;
            if (month <= 0) {
                month-=12;
                //cout << "Month is " << month << endl;
                year+=floor(month/12);
                //cout << "Year is " << endl;
                month = -1*(month%13);
            }
            year-=a_year;
            return *this;
        }

        void print() {
            cout << day << "/" << month << "/" << year << endl;
        }

        bool operator==(const Date& d) {
            return ((day==d.day) && (month == d.month) && (year == d.year));
        }

        bool operator<(const Date& d) {
            if (year < d.year) {
                return true;
            }
            if (year == d.year && month < d.month) {
                return true;
            }
            if (year == d.year && month == d.month && day < d.day) {
                return true;
            }
            return false;
        }

        bool operator>(const Date& d) {
            if (year > d.year) {
                return true;
            }
            if (year == d.year && month > d.month) {
                return true;
            }
            if (year == d.year && month == d.month && day > d.day) {
                return true;
            }
            return false;
        }


};


class Logger {
    private:
        std::ofstream logfile;
    public:

        //Ensure you don't leave an open stream
        ~Logger() {
            if (logfile.is_open()) {
                logfile.close();
            }
        }

        void open(string _path) {
            logfile.open(_path);
        }

        void close() {
            logfile.close();
        }

        Logger& operator<<(const string& data) {
            std::time_t result = std::time(nullptr);

            if (logfile.is_open()) {
                string str = asctime(std::localtime(&result));
                str.pop_back();
                logfile << str+":\t"+data+"\n";
            }
            else {
                cout << "Error: Open the logger";
            }
            return *this;
        }



};


class Employee{

    private:
        string name;
        string ID;
        string department;
        fstream file;

    public:
        void open(string f) {
            if (!file.is_open()) {
                file.open(f);
            }
            else {
                cout << "Close currently open file";
            }
        }

        void update_department(int id) {
            if (id<0) {
                cout << "Invalid input" << endl;
                return;
            }
            //Loop to correct position.
            for (int i =0; i < id-1; i++) {
                string temp = "";
                getline(file, temp);
            }
            string update;
            getline(file, update);
            
        }
    
};

class Complex {
    private:
        double a;
        double b;

        

    public:
        Complex(double _a, double _b) {
            a=_a;
            b=_b;
        }

        Complex operator+(Complex & x) {
            a+=x.a;
            b+=x.b;
            return *this;
        }
        Complex operator-(Complex & x) {
            a-=x.a;
            b-=x.b;
            return *this;
        }

        Complex operator*(Complex & x) {
            double temp_b = (b*x.b) + (a*x.a*-1.0);
            double temp_a = (b*x.a)+(a*x.b);
            a = temp_a;
            b = temp_b;
            return*this;
        }

        Complex operator/(Complex & x) {
            Complex numerator(a, b);
            Complex temp(0-x.a,x.b);
            numerator*temp;
            double denom = (x.a*x.a + x.b*x.b);
            a = numerator.a/denom;
            b=numerator.b/denom;
            return *this;
        }

        string comp_str() const {
            if (a < 0) {
                return to_string(b) + to_string(a) + "*i" ;
            }
            return to_string(b) + "+" + to_string(a) + "*i" ;
        }
        
        friend ostream& operator<<(ostream& os, const Complex& g) {
            os << g.comp_str();

            return os;
        }


};

void run_Q1() {
    Date d(1,1,2024);
    Date d2(30, 12, 1964);
    d.print();
    d2.print();
    cout << "Now subtracting 1 from d adding 1 to d2" << endl;
    d-1;
    d2+1;
    cout << endl << endl;
    d2.print();
    d.print();

    cout << "D2 < d " << (d2 < d) << endl;
    cout << "D > D2 " << (d > d2) << endl;
    cout << "D2 == d1 " << (d2 == d) << endl;
}

void run_Q2() {
    Logger l;
    l.open("test.txt");
    l << "INFO: Stargin the application";
    l << "WARNING: Stargin the application";
    l << "ERROR: Stargin the application";
}

//I just chose to have the operations apply to the first term for hte sake of ease
//so for testing, just swap out the operation and you'll see they match the test cases
void run_Q4() {

    Complex c(3, 2);
    Complex c2(5, 4);

    cout << c <<  " / " << c2 << endl << c/c2 << endl;

}
int main() {
    run_Q1();
    run_Q2();
    run_Q4();
    return 1;
}