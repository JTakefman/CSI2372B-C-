/*
300171459
Jordan Takefman
*/
#include <iostream>
#include <vector>
using namespace std;




class diary {
    private: static const int default_diary_size=3;

    private: struct entry {
        int ID;
        string name;
    };

    private: static entry* entry_list = new entry[default_diary_size];

    private: int ID;
    private: string name;
   
    public: 
    diary(int ID_in, string name_in) {
    }
    
    static 

    static void print_student_list(vector<student> student_list) {
        for (int i = 0; i < student_list.size(); i++) {
            cout << "Student " << i << ": " << student_list[i].ID << ", " << student_list[i].name << endl;
        }
    }
};

int main() {
    student::print_student_list(student::create_student_list());
}