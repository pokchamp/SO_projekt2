#ifndef DATA_H_INCLUDED 
#define DATA_H_INCLUDED

#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <syslog.h>
#include <time.h>
#include <signal.h>
#include <dirent.h>
#include <assert.h>
#include <sys/mman.h>
#include <utime.h>
#include <pthread.h>
#include <limits.h>
#include "funkcje.h"

// A structure to represent a queue
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

#endif
