#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator> 
#include <map>
using namespace std;

//Q1
//In the absence of any underlying specificaton for how to hold the charaters
//I chose to use a vector storing characters.
class MyString {
    private:
        vector <char> chars;
    
    public:

        MyString(string val) {
            for (int i = 0; i < val.size(); i++) {
                chars.push_back(val[i]);
            }
        }

        int length() const {
            return chars.size();
        }

        bool operator == (const MyString &c) {
            if (c.chars.size() != chars.size()) {
                return false;
            }
            for (int i = 0; i < chars.size(); i++) {
                if (chars[i] != c.chars[i]) {
                    return false;
                }
            }
            return true;
        }

        friend std::ostream& operator<<(std::ostream& os, const MyString& ms) {
            string str(ms.chars.begin(), ms.chars.end()); 
            os << str;
            return os;
        }
};

class CompareByLength {
    public:
        bool operator()(const MyString& a, const MyString& b) const {
            return a.length() < b.length(); // Compare based on length
        }
};

//Q2
class DataAnalysis {
    private:
        vector<double> prices;
    public:
        DataAnalysis(vector<double> pr) {
            prices=pr;
        }

        double index(int i) const {
            return prices[i];
        }

        int length() const{
            return prices.size();
        }

};

class average {
    public:
        double operator()(const DataAnalysis a) const {
            double avg = 0.0;
            for (int i = 0; i < a.length(); i++) {
                avg+=a.index(i);
            }
            return (avg / a.length());
        }
};

class stand_deviation {
    public:
        double operator()(const DataAnalysis a) const {
            average avg;
            double mean = avg(a);
            double sum = 0.0;
            for (int i = 0; i < a.length(); i++) {
                sum+=pow((a.index(i)-mean), 2);
            }
            return (sum / a.length());
        }
};

//Q3
//I used the work at this site to help in designing my own iterator https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp

template <typename T>
class CustomContainer {
public:

    class Iterator {

    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    private:
        pointer ptr;
    
    public:
        //Doing some online research, these are the type aliases you need 
        //to define to comply with the C++ iterator standard.
        

        Iterator(pointer ptr) : ptr(ptr) {}

        reference operator*() const { return *ptr; }

        pointer operator->() { return ptr; }

        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }

        Iterator operator++(int) { 
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator++() { 
            ++ptr;
            return *this;
        }

        Iterator operator--(int) { 
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        Iterator& operator--() { 
            --ptr;
            return *this;
        }

    
    };

    void add(const T& value) { m_data.push_back(value); }
    //Reading online it s
    size_t size() const { return m_data.size(); }


    Iterator begin() { return Iterator(m_data.data()); }
    Iterator end() { return Iterator(m_data.data() + m_data.size()); }


    //The template allows passing any callable parameter so we can pass
    //both a lambda or a function
    template <typename Func>
    void ForEach(Func func) {
        for (auto it = begin(); it != end(); ++it) {
            func(*it);
        }
    }

private:
    std::vector<T> m_data; // Underlying storage
};

class Sensor {
    protected:
        int id;
    public:
        virtual void handleEvent()=0;
        int get_id() {return id;}
        int event() {
            srand(time(0));
            return rand() % 2;
        }
};

class TemperatureSensor : public Sensor {
    public:
        TemperatureSensor(int _id) {
            id=_id;
        }
        void handleEvent() override {
            cout << "Temperature sensor handled" << endl;
        }
};

class PressureSensor : public Sensor {
    public:
        PressureSensor(int _id) {
                id=_id;
        }
        void handleEvent() override {
            cout << "Pressure sensor handled" << endl;
        }
};

void run_Q1() {
    cout << "Q1\n";
    MyString str1("test");
    MyString str2("testing");
    MyString str3("testing");
    cout << (str1==str2) << endl << (str2 == str3) << endl << (str1 == str3) << endl;

    std::vector<MyString> myStrings = { MyString("apple"), MyString("kiwi"), MyString("blueberry"), MyString("grape") };
    std::sort(myStrings.begin(), myStrings.end(), CompareByLength());
    for (const auto& s : myStrings) {
        std::cout << s << " ";
    }
    cout << endl;
}

void run_Q2() {
    cout << "\nQ2\n";
    std::vector<DataAnalysis> data = {
        DataAnalysis({115.6, 102.35, 127.3}),
    };

    // Store the averages
    std::vector<double> averages(data.size());
    std::vector<double> stand_dev(data.size());

    // Apply the functor using std::transform
    std::transform(data.begin(), data.end(), averages.begin(), average());

    // Print the averages
    cout << "averages:\n";
    for (const auto& avg : averages) {
        std::cout << avg << std::endl;
    }
    std::transform(data.begin(), data.end(), stand_dev.begin(), stand_deviation());

    // Print the averages
    cout << "standard deviation:\n";
    for (const auto& std : stand_dev) {
        std::cout << std << std::endl;
    }
    cout << endl;

}

void time2(int& x) {
    x*= 2;
}

void run_Q3() {
    cout << "Q3" << endl;
    CustomContainer<int> container;

    // Add elements
    container.add(1);
    container.add(2);
    container.add(3);
    container.add(4);

    // Iterate and print
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    cout << endl;
    container.ForEach(&time2);

    // Iterate and print
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }

    cout << endl;
}


//I had to do some digging to figure out how to point to class member pointers
//https://isocpp.org/wiki/faq/pointers-to-members#fnptr-vs-memfnptr-types I came across this which I how I derived
//the below code

void run_Q4() {
    cout << endl << "Q4:" << endl;
    PressureSensor test(500);
    TemperatureSensor test2(600);
    map<int, void (Sensor::*)()> functionMap;

    functionMap[test2.get_id()]= &Sensor::handleEvent;
    functionMap[test.get_id()]= &Sensor::handleEvent;

    (test.*functionMap[test.get_id()])();
    (test2.*functionMap[test2.get_id()])();

}

int main() {
    run_Q1();
    run_Q2();
    run_Q3();
    run_Q4();
    return 1;
}