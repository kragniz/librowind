#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int set_serial_options(int fd) {
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0) {
        return -1;
    }

    cfsetospeed (&tty, B4800);
    cfsetispeed (&tty, B4800);

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

    if (tcsetattr (fd, TCSANOW, &tty) != 0) {
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
    char* new_line = line;
    char c;
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
            new_line[i] = c;
            i++;
        }
    }
    tcflush(ro_fd, TCIFLUSH);
}

int main() {
    int ro_fd = get_rowind_fd("/dev/ttyUSB0");
    char* line = malloc(35);
    while (1) {
        get_line(ro_fd, "IIMWV", line);
        puts(line);
        sleep(1);
    }
    return 0;
}
