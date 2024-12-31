#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

struct message {
    long msg_type;
    char text[100];
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: sender <msgq_id> <num_receivers>" << endl;
        return 1;
    }

    int msgqId = std::stoi(argv[1]);
    int numReceivers = std::stoi(argv[2]);

    cout << "Sender, PID " << getpid() << ", begins execution." << endl;
    cout << "Sender, PID " << getpid() << ", received message queue id " << msgqId << endl;

    for (int i = 0; i < 5; i++) {  // Send 5 messages
        message msg;
        cout << "Sender, PID " << getpid() << ": Please input your message: ";
        cin.getline(msg.text, sizeof(msg.text));

        cout << "Sender, PID " << getpid() << ": Which receiver is this message for? (1-" << numReceivers << "): ";
        cin >> msg.msg_type;
        cin.ignore();  // Ignore leftover newline

        if (msgsnd(msgqId, &msg, sizeof(msg.text), 0) < 0) {
            perror("msgsnd");
            return 1;
        }

        cout << "Sender, PID " << getpid() << ", sent message to receiver " << msg.msg_type << endl;
    }

    return 0;
}
