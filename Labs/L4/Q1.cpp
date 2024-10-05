/*
300171459
Jordan Takefman
*/
#include <iostream>

using namespace std;

class Course {
    private:
        int hours;
        int code;

    public:
        Course(int in_hours, int in_code) {
            hours=in_hours;
            code=in_code;
        }
        Course() = default;

        int getNum() {
            return code;
        }
        int getHours() {
            return hours;
        }
};

class Student {
    private:
        int id;
        int *gradeList;
        Course **courseList;
        int max_courses;
        int num_courses;
    
    public:
        Student(int in_id, int in_max_courses) {
            id = in_id;
            max_courses = in_max_courses;
            num_courses = 0;
            courseList=new Course*[max_courses];
        }

        ~Student() {
            for (int i = 0; i < num_courses; i++) {
                delete courseList[i];
            }
            delete[] courseList;
        }

        double average() {
            double avg = 0.0;
            for (int i = 0; i < num_courses; i++) {
                avg += gradeList[i];
            }
            return avg/num_courses;
        }

        int totalHours() {
            int hours = 0;
            for (int i = 0; i < num_courses; i++) {
                hours+=courseList[i]->getHours();
            }
            return hours;
        }

        void addCourse(int hours, int code) {
            if (num_courses==max_courses) {
                cout << "Hit max courses cannot add more" << endl;
                return;
            }
            courseList[num_courses]=new Course(hours, code);
            num_courses++;
        }

        void printList() {
            for (int i = 0; i < num_courses; i++) {
                cout << "Course " << i+1 << ": " << courseList[i]->getNum() << endl;
            }
        }


};

int main() {
    Student test(100, 7);

    test.addCourse(3, 3001);
    test.addCourse(4, 3002);
    test.addCourse(6, 4500);
    test.addCourse(3, 3001);
    test.addCourse(4, 3002);
    test.addCourse(6, 4500);
    test.addCourse(3, 3001);
    test.addCourse(4, 3002);
    test.addCourse(6, 4500);

    test.printList();

    return 0;
}