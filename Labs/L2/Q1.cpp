/*
300171459
Jordan Takefman
*/
#include <iostream>
#include <vector>
using namespace std;

class student {
    private: int ID;
    private: string name;
   
    public: 
     student(int ID_in, string name_in) {
        ID=ID_in;
        name=name_in;
    }
    static vector<student> create_student_list() {
        vector<student> student_list;
        int n = 0;
        cout << "How many students do you want to create" << endl;
        cin  >> n;

        for (int i = 0; i < n; i++) {
            int id = 0;
            string name = "";
            cout << "Input an integer id ";
            cin >> id;
            cout << "Input the name of the student ";
            cin >> name;
            student temp (id, name);
            student_list.push_back(temp);
        }
        return student_list;
    }

    static void print_student_list(vector<student> student_list) {
        for (int i = 0; i < student_list.size(); i++) {
            cout << "Student " << i << ": " << student_list[i].ID << ", " << student_list[i].name << endl;
        }
    }
};

int main() {
    student::print_student_list(student::create_student_list());
}