#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::to_string;

#define MSGQ_KEY 1234  // A unique key for message queue

void createSender(int msgqId, int numReceivers) {
    pid_t pid = fork();
    if (pid == 0) {  // Child process
        execl("./sender", "sender", std::to_string(msgqId).c_str(), std::to_string(numReceivers).c_str(), (char*)NULL);
        perror("Failed to execute sender");
        exit(1);
    } else if (pid > 0) {
        cout << "Master created sender process, PID " << pid << endl;
    } else {
        perror("Fork failed for sender");
    }
}

void createReceivers(int msgqId, int numReceivers) {
    for (int i = 1; i <= numReceivers; i++) {
        pid_t pid = fork();
        if (pid == 0) {  // Child process
            execl("./receiver", "receiver", to_string(msgqId).c_str(), to_string(i).c_str(), (char*)NULL);
            perror("Failed to execute receiver");
            exit(1);
        } else if (pid > 0) {
            cout << "Master created receiver " << i << ", PID " << pid << endl;
        } else {
            perror("Fork failed for receiver");
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <number_of_receivers>" << endl;
        return 1;
    }

    int numReceivers = std::stoi(argv[1]);
    cout << "Master, PID " << getpid() << ", begins execution." << endl;

    // Create message queue
    int msgqId = msgget(MSGQ_KEY, IPC_CREAT | 0666);
    if (msgqId < 0) {
        perror("msgget");
        exit(1);
    }
    cout << "Master acquired message queue, ID " << msgqId << endl;

    // Create sender and receiver processes
    createSender(msgqId, numReceivers);
    createReceivers(msgqId, numReceivers);

    // Wait for all child processes to terminate
    while (wait(NULL) > 0);

    // Remove the message queue
    if (msgctl(msgqId, IPC_RMID, NULL) < 0) {
        perror("msgctl");
        exit(1);
    }
    cout << "Master removed message queue and terminates." << endl;

    return 0;
}
