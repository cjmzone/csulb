#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include "myShm.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_children> <shared_memory_name>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    const char *shm_name = argv[2];

    // Create shared memory
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(struct CLASS));
    struct CLASS *shm_ptr = mmap(0, sizeof(struct CLASS), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

    shm_ptr->index = 0;

    // Create unnamed semaphore
    sem_t *mutex = sem_open("/mySem", O_CREAT, 0666, 1);

    // Create named semaphore for I/O
    sem_t *io_mutex = sem_open("/ioSem", O_CREAT, 0666, 1);

    // Fork child processes
    for (int i = 1; i <= n; i++) {
        if (fork() == 0) {
            char child_num[10];
            sprintf(child_num, "%d", i);
            execl("./slave", "slave", child_num, shm_name, NULL);
            perror("execl");
            exit(1);
        }
    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    // Display shared memory contents
    printf("Final shared memory content:\n");
    for (int i = 0; i < shm_ptr->index; i++) {
        printf("Slot %d: %d\n", i, shm_ptr->report[i]);
    }

    // Cleanup resources
    sem_close(mutex);
    sem_unlink("/mySem");
    sem_close(io_mutex);
    sem_unlink("/ioSem");
    munmap(shm_ptr, sizeof(struct CLASS));
    shm_unlink(shm_name);

    printf("Master exiting.\n");
    return 0;
}
