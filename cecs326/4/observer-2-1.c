/* observer-3.c
   compile with gcc, link with -lrt -lpthread
   run with ./observer-3 /myShm /mySem
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <semaphore.h>
#include <errno.h>

/* 
/* The struct below may be placed in a separate .h file
*/

struct CLASS {
	sem_t mutex_sem; /* enforce mutual exclusion for 
				   accessing count */
	int count;		 /*shared variable, need mutual exclusion*/
};

int main (int argc, char* argv[]) {
    const char *shmName = argv[1];   /* shared memory name from commandline */
    const int SIZE = 4096;
    int shm_fd, i;
    char *shm_base; 		     /* pointer to shared memory segment*/

    printf("observer begins execution\n");

/* create a shared memory segment */
    shm_fd = shm_open(shmName, O_CREAT|O_RDWR, 0666);
    if (shm_fd == -1) {
        printf("observer: shared memory failed: %s\n", strerror(errno));
        exit(1);
    }

/* configure size of shared memory segment */
    ftruncate(shm_fd, SIZE);

/* map shared memory segment in the address space of the process */
    shm_base = mmap(0,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd,0);
    if (shm_base == MAP_FAILED) {
        printf("observer: map failed: %s\n", strerror(errno));
        exit(1);
    }

/* structure shared memory segment to struct CLASS */
    struct CLASS *count_ptr = (struct CLASS *) shm_base;	

/* initialize mutex_sem in shared memory to 1, and nanoset it to shared*/
    if (sem_init(&(count_ptr->mutex_sem),0, 1) == -1) {
        printf("observer: sem_init(count_ptr->mutex_sem) failed: %s/n", strerror(errno));
        exit(1);
    }

/* lock mutex_sem to initialize shared count */
    if (sem_wait(&(count_ptr->mutex_sem)) == -1) {
        printf("observer: sem_wait(count_ptr->mutex_sem) failed: %s/n", strerror(errno));
        exit(1);
    }

/* ready to access shared count */
    count_ptr->count = 10;

/* unlock mutex_sem */
    if (sem_post(&(count_ptr->mutex_sem)) == -1) {
        printf("observer: sem_post(count_ptr->mutex_sem) failed: %s\n", strerror(errno));
        exit(1);
    }

/* other stuff that this program needs to perform 
...
*/

/* lock mutex_sem to access count */
    if (sem_wait(&(count_ptr->mutex_sem)) == -1) {
        printf("observer: sem_wait(count_ptr->mutex_sem) failed: %s/n", strerror(errno));
        exit(1);
    }

/* critical section to access & increment count in shared memory */
    printf ("count before update = %d \n", count_ptr->count);
    (count_ptr->count)++;
    printf ("updated count = %d \n", count_ptr->count);

/* exit critical section, unlock mutex_sem */
     if (sem_post(&(count_ptr->mutex_sem)) == -1) {
        printf("observer: sem_post(count_ptr->mutex_sem) failed: %s\n", strerror(errno));
        exit(1);
    }

/* done with mutex_sem, destroy it & free up resources 
   allocated to it */
    if (sem_destroy(&(count_ptr->mutex_sem)) == -1) {
        printf("observer: sem_destroy(count_ptr->mutex_sem) failed: %s\n", strerror(errno));
        exit(1);
    }

/* remove mapped memory segment from the address space */
    if (munmap(count_ptr,SIZE) == -1) {
        printf("observer: unmap failed: %s\n", strerror(errno));
        exit(1);
    }

/* close shared memory segment */
    if (close(shm_fd) == -1) {
        printf("observer: close failed: %s\n", strerror(errno));
        exit(1);
    }

/* remove shared memory segment from the file system */
    if (shm_unlink(shmName) == -1) {
        printf("observer: Error removing %s: %s\n", shmName, strerror(errno));
        exit(1);
    }

    printf("observer has removed shared memory, ending execution\n");

    return 0;
}

