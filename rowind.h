#ifndef RO_WIND
#define RO_WIND

#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

typedef struct _wind {
    double direction;
    double speed;
    int valid;
} Wind;

#endif
