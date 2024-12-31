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
        cerr << "Usage: receiver <msgq_id> <receiver_number>" << endl;
        return 1;
    }

    int msgqId = std::stoi(argv[1]);
    int receiverNum = std::stoi(argv[2]);

    cout << "Receiver " << receiverNum << ", PID " << getpid() << ", begins execution." << endl;
    cout << "Receiver " << receiverNum << ", PID " << getpid() << ", received message queue id " << msgqId << endl;

    message msg;
    if (msgrcv(msgqId, &msg, sizeof(msg.text), receiverNum, 0) < 0) {
        perror("msgrcv");
        return 1;
    }

    cout << "Receiver " << receiverNum << ", PID " << getpid() << ", received message: " << msg.text << endl;

    // Send acknowledgment
    message ack;
    ack.msg_type = 999;  // 999 is reserved for acknowledgment
    sprintf(ack.text, "Receiver %d acknowledges receipt of message.", receiverNum);

    if (msgsnd(msgqId, &ack, sizeof(ack.text), 0) < 0) {
        perror("msgsnd");
        return 1;
    }

    cout << "Receiver " << receiverNum << ", PID " << getpid() << ", sent acknowledgment message." << endl;
    cout << "Receiver " << receiverNum << ", PID " << getpid() << ", terminates." << endl;

    return 0;
}
