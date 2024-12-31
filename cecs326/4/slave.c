#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h> 
#include "myShm.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <child_number> <shared_memory_name>\n", argv[0]);
        exit(1);
    }

    int child_num = atoi(argv[1]);
    const char *shm_name = argv[2];

    printf("Slave begins execution\n");
    printf("I am child number %d, received shared memory name %s.\n", child_num, shm_name);

    // Open shared memory
    int shm_fd = shm_open(shm_name, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    struct CLASS *shm_ptr = mmap(0, sizeof(struct CLASS), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        exit(1);
    }

    // Open the named semaphore
    sem_t *mutex = sem_open("/mySem", 0); // Open existing semaphore
    if (mutex == SEM_FAILED) {
        perror("sem_open");
        munmap(shm_ptr, sizeof(struct CLASS));
        close(shm_fd);
        exit(1);
    }

    // Lock semaphore to access critical section
    if (sem_wait(mutex) == -1) {
        perror("sem_wait");
        sem_close(mutex);
        munmap(shm_ptr, sizeof(struct CLASS));
        close(shm_fd);
        exit(1);
    }

    // Critical section: write to shared memory
    int slot = shm_ptr->index;
    shm_ptr->report[slot] = child_num;
    shm_ptr->index++;
    printf("I have written my child number to slot %d and updated index to %d.\n", slot, shm_ptr->index);

    // Unlock semaphore
    if (sem_post(mutex) == -1) {
        perror("sem_post");
        sem_close(mutex);
        munmap(shm_ptr, sizeof(struct CLASS));
        close(shm_fd);
        exit(1);
    }

    // Close and clean up
    sem_close(mutex);
    munmap(shm_ptr, sizeof(struct CLASS));
    close(shm_fd);

    printf("Child %d closed access to shared memory and terminates.\n", child_num);

    return 0;
}
