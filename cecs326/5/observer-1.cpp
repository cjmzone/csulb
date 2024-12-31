/* observer-1.cpp
   compile with g++, link with -lrt -lpthread
   run with ./observer-1 /mySem
*/

#include <iostream>
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

using namespace std;

int main (int argc, char* argv[]) {
    const char *semName = argv[1];   /* semaphore name from commandline */
    int count = 100;		     /* value to display */

/* create a named semaphore for displaying output */
    sem_t *display_sem = sem_open(semName, O_CREAT, 0660, 1);
    if (display_sem == SEM_FAILED) {
        printf("observer: sem_open failed: %s\n", strerror(errno));
        exit(1);
    }

/* ... work on other stuff */

/* ready for output; lock display_sem for using the output display */
    if (sem_wait(display_sem) == -1) {
        printf("observer: sem_wait(display_sem) failed: %s/n", strerror(errno));
        exit(1);
    }

/* critical section using monitor for output */
    cout << "content of count = " << count << endl;

/* unlock display_sem */
    if (sem_post(display_sem) == -1) {
        printf("observer: sem_post(display_sem) failed: %s\n", strerror(errno));
        exit(1);
    }

/* done using the display, close display_sem & and remove its name*/
    if (sem_close(display_sem) == -1) {
        printf("observer: sem_close(display_sem) failed: %s\n", strerror(errno));
        exit(1);
    }
    if (sem_unlink(semName) == -1) {
        printf("observer: sem_unlink(display_sem) failed: %s\n", strerror(errno));
        exit(1);
    }

    return 0;
}

