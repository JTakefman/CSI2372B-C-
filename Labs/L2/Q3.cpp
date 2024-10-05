/*
300171459
Jordan Takefman
*/
#include <iostream>
#include <vector>
using namespace std;
class Animal {
    private:
        string name;
        string type;
    public:
        Animal(string name_in, string type_in) {
            name=name_in;
            type=type_in;
        }
        ~Animal() {
        }
        string getName() {
            return name;
        }
        string getType() {
            return type;
        }
};
class AnimalShelter {
    vector<Animal*> vec;

    public:

        AnimalShelter() {

        }

        ~AnimalShelter() {
            cleanup();
        }
        void addAnimal(string name, string type) {
            Animal* temp = new Animal(name, type);
            this->vec.push_back(temp);
        }

        void deleteAnimal(string name) {
            for (int i = 0; i < vec.size(); i++) {
                if (this->vec[i]->getName() == name) {
                    delete vec[i];
                    vec.erase(vec.begin()+i);
                    break;
                }
            }
        }

        void printAnimals() {
            cout << "Animal array contents:" << endl;
            for (int i = 0; i < vec.size(); i++) {

                cout << this->vec[i]->getName() << ", " << vec[i]->getType() << endl;
            }
            cout << endl;
        }
        
        //Free all remaining pointers once object lifetime is over.
        void cleanup() {
            for (auto p : vec)
            {
                delete p;
            } 
            vec.clear();
        }

};

int main() {
    AnimalShelter temp_shelter = AnimalShelter();
    temp_shelter.addAnimal("john", "fox");
    temp_shelter.addAnimal("kyle", "bear");
    temp_shelter.addAnimal("stew", "kangaroo");
    temp_shelter.printAnimals();
    temp_shelter.deleteAnimal("kyle");
    temp_shelter.printAnimals();
    return 1;
}