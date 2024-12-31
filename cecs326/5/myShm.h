#ifndef MYSHM_H
#define MYSHM_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

struct CLASS {
    int index;      
    int report[10];   
};

#endif
