#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::stoi;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    string name = argv[1]; 
    int age = stoi(argv[2]); 

    cout << "I am " << name << ", " << age << " years old." << endl;
    
    return 0; 
}