#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
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

    int shm_fd = shm_open(shm_name, O_RDWR, 0666);
    struct CLASS *shm_ptr = mmap(0, sizeof(struct CLASS), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

    int slot = shm_ptr->index;
    shm_ptr->report[slot] = child_num;
    shm_ptr->index++;
    printf("I have written my child number to slot %d and updated index to %d.\n", slot, shm_ptr->index);

    munmap(shm_ptr, sizeof(struct CLASS));
    printf("Child %d closed access to shared memory and terminates.\n", child_num);

    return 0;
}