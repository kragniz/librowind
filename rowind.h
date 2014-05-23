#ifndef RO_WIND_H
#define RO_WIND_H

#define RW_DIRECTION_INDEX 1
#define RW_SPEED_INDEX 3
#define RW_VALID_INDEX 5

typedef struct _wind {
    double direction;
    double speed;
    int valid;
} Wind;

Wind* get_wind(int ro_fd);
int get_rowind_fd(char* portname);
void get_line(int ro_fd, char* type, char* line);

#endif
