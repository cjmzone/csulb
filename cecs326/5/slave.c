#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include "myShm.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <child_number> <shared_memory_name>\n", argv[0]);
        exit(1);
    }

    int child_num = atoi(argv[1]);
    const char *shm_name = argv[2];

    printf("Slave begins execution\n");

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

    // Open unnamed semaphore for shared memory
    sem_t *mutex = sem_open("/mySem", 0);
    if (mutex == SEM_FAILED) {
        perror("sem_open");
        munmap(shm_ptr, sizeof(struct CLASS));
        close(shm_fd);
        exit(1);
    }

    // Lock semaphore for shared memory access
    sem_wait(mutex);
    int slot = shm_ptr->index;
    shm_ptr->report[slot] = child_num;
    shm_ptr->index++;
    sem_post(mutex);

    // Write to a unique file
    char filename[20];
    sprintf(filename, "child_%d.txt", child_num);
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("fopen");
        sem_close(mutex);
        munmap(shm_ptr, sizeof(struct CLASS));
        close(shm_fd);
        exit(1);
    }

    fprintf(file, "Child %d writing to slot %d in shared memory.\n", child_num, slot);
    fclose(file);

    // Open named semaphore for monitor access
    sem_t *io_mutex = sem_open("/ioSem", 0);
    if (io_mutex == SEM_FAILED) {
        perror("sem_open ioSem");
        sem_close(mutex);
        munmap(shm_ptr, sizeof(struct CLASS));
        close(shm_fd);
        exit(1);
    }

    // Acquire semaphore for monitor and display file
    sem_wait(io_mutex);
    file = fopen(filename, "r");
    if (file) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    }
    sem_post(io_mutex);

    // Clean up resources
    sem_close(io_mutex);
    sem_close(mutex);
    munmap(shm_ptr, sizeof(struct CLASS));
    close(shm_fd);

    printf("Child %d finished execution.\n", child_num);
    return 0;
}
