#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "myShm.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_children> <shared_memory_name>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    const char *shm_name = argv[2];

    printf("Master begins execution\n");

    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    ftruncate(shm_fd, sizeof(struct CLASS));
    struct CLASS *shm_ptr = mmap(0, sizeof(struct CLASS), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    shm_ptr->index = 0;

    printf("Master created a shared memory segment named %s\n", shm_name);
    printf("Master created %d child processes to execute slave\n", n);

    for (int i = 1; i <= n; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            char child_num[10];
            sprintf(child_num, "%d", i);
            execl("./slave", "slave", child_num, shm_name, NULL);
            perror("execl");
            exit(1);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Master received termination signals from all %d child processes\n", n);
    printf("Updated content of shared memory segment after access by child processes:\n");

    for (int i = 0; i < shm_ptr->index; i++) {
        printf("Slot %d: %d\n", i, shm_ptr->report[i]);
    }

    munmap(shm_ptr, sizeof(struct CLASS));
    shm_unlink(shm_name);
    printf("Master removed shared memory segment, and is exiting\n");

    return 0;
}
