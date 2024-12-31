#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string childNum = "1";
    string fileName = "out-"+childNum+".txt";  // create a unique file name
    ofstream myOutfile(fileName); // create an output file

    if (myOutfile.is_open()) { // check if file was opened successfully
        myOutfile << "Hello, world!" << endl;
        myOutfile.close(); // close the file
        cout << "Data written to " << fileName << endl;
    } else {
        cerr << "Error opening file" << endl;
    }

    ifstream myInfile(fileName);  // retrieve previously output file

    if (myInfile.is_open()) {
        cout << myInfile.rdbuf(); // send file stream buffer to standard out
        myInfile.close();
    }
}
