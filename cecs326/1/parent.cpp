#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using std::string;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {

    // check for valid arguments 
    if (argc < 3 || (argc % 2) != 1) {
        cout << "Invalid arguments!";
        return 1;
    }

    // calculate and print number of children
    int numArgs = argc - 1;
    int numChildren = numArgs / 2;
    cout << "I have " << numChildren << " children." << endl;

    // loop through arguments 
    for (int i = 1; i < argc; i += 2) {
        pid_t pid = fork(); 

        if (pid < 0) {
            perror("Fork failed");
            return 1;
        } else if (pid == 0) {
            // execute ./child
            cout << "Child process created for " << argv[i] << ", " << argv[i + 1] << endl; 
            const char *args[] = { "./child", argv[i], argv[i + 1], NULL }; 
            execv(args[0], const_cast < char *const * >(args)); 
            perror("Exec failed");
            return 1; 
        } 
    }

    // debug
    while (wait(NULL) > 0) {
        cout << "A child process has terminated." << endl; 
    }
    cout << "All child processes terminated. Parent exits." << endl;

    return 0;
}