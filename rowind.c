#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define RW_DIRECTION_INDEX 1
#define RW_SPEED_INDEX 3
#define RW_VALID_INDEX 5

typedef struct _wind {
    double direction;
    double speed;
    int valid;
} Wind;

int set_serial_options(int fd) {
    struct termios tty;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(fd, &tty) != 0) {
        return -1;
    }

    cfsetospeed(&tty, B4800);
    cfsetispeed(&tty, B4800);

    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 50;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag |= B4800;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        return -2;
    }
    return 0;
}

int get_rowind_fd(char* portname) {
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        return -1;
    }
    set_serial_options(fd);
    return fd;
}

void get_line(int ro_fd, char* type, char* line) {
    memset(line, 0, strlen(line));

    char c = '\0';
    int type_length = strlen(type);
    int i = 0;
    int n = 1;
    int reading_line = 0;
    for (n = 1; n >= 1; n = read(ro_fd, &c, 1)) {
        if (c == '$') {
            reading_line = 1;
        } else if (c == '\n' && reading_line) {
            break;
        } else if (reading_line) {
            if (i < type_length) {
                if (type[i] != c) {
                    i = -1;
                    reading_line = 0;
                }
            }
            line[i] = c;
            i++;
        }
    }
    tcflush(ro_fd, TCIFLUSH);
}

int checksum(char* line) {
    puts(line);
    char* ptr = &line[0];
    char calculated_sum = 0;

    while (*ptr != '\0' && *ptr != '*') {
        calculated_sum ^= *ptr;
        ptr++;
    }

    char original_sum[3] = "";
    if (*ptr == '*') {
        ptr++;
        int i;
        for (i = 0; *ptr != '\0' && *ptr != '\r'; i++, ptr++) {
            original_sum[i] = *ptr;
        }
        original_sum[i+1] = '\0';
    }

    char calculated_sum_hex[3];
    sprintf(calculated_sum_hex, "%02X", calculated_sum);
    return !strcmp(original_sum, calculated_sum_hex);
}

void wind_from_iimwv(Wind* wind, char* line) {
    char str_direction[8] = "";
    char str_speed[8] = "";
    char str_valid = '\0';

    char c;
    int i_tok = 0;
    int i_str = 0;
    int end = 0;
    int j = 0;

    for (j = 0; j < strlen(line) && !end; j++) {
        c = line[j];

        if (c == ',') {
            i_tok++;
            i_str = 0;
        } else if (i_tok == RW_DIRECTION_INDEX) {
            str_direction[i_str] = c;
            i_str++;
        } else if (i_tok == RW_SPEED_INDEX) {
            str_speed[i_str] = c;
            i_str++;
        } else if (i_tok == RW_VALID_INDEX) {
            str_valid = c;
            end = 1;
        }
    }

    wind->valid = (str_valid == 'A');
    wind->direction = atof(str_direction);
    wind->speed = atof(str_speed);
}

Wind* get_wind(int ro_fd) {
    char line[32] = "";
    Wind* wind = malloc(sizeof(Wind));
    get_line(ro_fd, "IIMWV", line);

    if (checksum(line)) {
        wind_from_iimwv(wind, line);
    } else {
        wind->valid = 0;
        wind->direction = -1;
        wind->speed = -1;
    }
    return wind;
}

int main() {
    int ro_fd = get_rowind_fd("/dev/ttyUSB0");
    while (1) {
        Wind* wind = get_wind(ro_fd);
        printf("direction: %f speed: %f\n", wind->direction, wind->speed);
        free(wind);
        sleep(1);
    }
    return 0;
}
